// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>

#include "Utils/Tribool.h"

/*
*	JsonValue.h contains a class that represents some json value.
*
*	JsonValue can have some subobjects, thus creating a tree structure.
*	Uses an auxiliary enumeration JsonValueType.
* 
*	Json values are:
*		1) Object:
*			{ } or { string: value, ... }
* 
*		2) Array:
*			[ ] or [ value, ... ]
*
*		3) String:
*			"..."
* 
*		4) Number (has 2 subtypes - floating point and integral):
*			-?(0-9)+(.(0-9)+)?((eE)(0-9)+)?
* 
*		5) Boolean:
*			true or false
* 
*		6) Null:
*			null
*/

namespace io {
	enum JsonValueType : uint8_t {
		OBJECT = 0, // { key: value, ... }
		ARRAY, // [ value, ... ]

		STRING, // "..."
		NUMBER, // self-explanatory, but: -? integer = (0-9)+, [optional: fraction = .integer] [optional: exponent = (Ee)integer]
		FP_NUMBER, // just a continuation of the previous one

		BOOL,
		NULL_VALUE, // must have been null, but NULL is a macro of the language, thus the _VALUE part

		UNKNOWN // error type
	};

	class JsonValue final {
	public:
		using ObjectTy = std::vector<std::pair<std::string, JsonValue>>;
		using ArrayTy = std::vector<JsonValue>;

		using StringTy = std::string;
		using FPTy = double;
		using IntegerTy = intmax_t;

		using BoolTy = bool;

	private:
		JsonValueType m_type;
		
		union { // The possible data
			StringTy m_str;
			FPTy m_fpNumber;
			IntegerTy m_iNumber; // also used for bool

			ArrayTy m_array;
			ObjectTy m_object;
		};

	public:
		///  CONSTRUCTORS AND DESTRUCTOR  ///

		constexpr JsonValue() noexcept : m_type(io::UNKNOWN) { }

		inline JsonValue(const JsonValue& other) : m_type(other.getType()) {
			switch (m_type) {
				case io::OBJECT: ::new(&m_object) ObjectTy(other.asObject()); break;
				case io::ARRAY: ::new(&m_array) ArrayTy(other.asArray()); break;
				case io::STRING: ::new(&m_str) StringTy(other.asString()); break;
				case io::NUMBER: m_iNumber = other.asINumber(); break;
				case io::FP_NUMBER: m_fpNumber = other.asFPNumber(); break;
				case io::BOOL: m_iNumber = other.asBool(); break;
				case io::NULL_VALUE: break;
				case io::UNKNOWN: break;
			default: break;
			}
		}

		inline JsonValue(JsonValue&& other) noexcept : m_type(other.getType()) {
			switch (m_type) {
				case io::OBJECT: ::new(&m_object) ObjectTy(std::move(other.m_object)); break;
				case io::ARRAY: ::new(&m_array) ArrayTy(std::move(other.m_array)); break;
				case io::STRING: ::new(&m_str) StringTy(std::move(other.m_str)); break;
				case io::NUMBER: m_iNumber = other.asINumber(); break;
				case io::FP_NUMBER: m_fpNumber = other.asFPNumber(); break;
				case io::BOOL: m_iNumber = other.asBool(); break;
				case io::NULL_VALUE: break;
				case io::UNKNOWN: break;
			default: break;
			}

			other.setAsUnknown();
		}

		inline JsonValue(ObjectTy value) : JsonValue() {
			setAsObject(std::move(value));
		}

		inline JsonValue(ArrayTy value) : JsonValue() {
			setAsArray(std::move(value));
		}

		inline JsonValue(StringTy value) : JsonValue() {
			setAsString(std::move(value));
		}

		inline JsonValue(FPTy value) : JsonValue() {
			setAsFPNumber(value);
		}

		inline JsonValue(IntegerTy value) : JsonValue() {
			setAsINumber(value);
		}

		inline JsonValue(utils::Tribool value) : JsonValue() {
			if (value.isNone()) {
				setAsNull();
			} else {
				setAsBool(value);
			}
		}

		inline ~JsonValue() {
			if (m_type != io::UNKNOWN) {
				switch (m_type) {
					case io::OBJECT: m_object.~ObjectTy(); break;
					case io::ARRAY: m_array.~ArrayTy(); break;
					case io::STRING: m_str.~StringTy(); break;
				default: break;
				}

				m_type = io::UNKNOWN;
			}
		}


		///  OPERATORS  ///

		inline JsonValue& operator=(const JsonValue& other) {
			if (this == &other) {
				return *this;
			}
			
			this->~JsonValue();
			::new(this) JsonValue(other);

			return *this;
		}

		inline JsonValue& operator=(JsonValue&& other) noexcept {
			if (this == &other) {
				return *this;
			}

			this->~JsonValue();
			::new(this) JsonValue(std::move(other));

			return *this;
		}

		friend std::ostream& operator<<(std::ostream& out, const JsonValue& value) {
			switch (value.getType()) {
				case io::OBJECT:
					if (value.asObject().empty()) {
						out << "{ }";
					} else {
						out << "{ ";
						for (const auto& [key, val] : value.asObject()) {
							out << "\"" << key << "\" : " << val << ", ";
						}

						out << " }";
					} break;
				case io::ARRAY:
					if (value.asArray().empty()) {
						out << "[ ]";
					} else {
						out << "[ ";
						for (auto& val : value.asArray()) {
							out << val << ", ";
						}

						out << " ]";
					} break;
				case io::STRING: out << "\"" << value.asString() << "\""; break;
				case io::NUMBER: out << value.asINumber(); break;
				case io::FP_NUMBER: out << value.asFPNumber(); break;
				case io::BOOL: out << (value.asBool() ? "true\0" : "false"); break;
				case io::NULL_VALUE: out << "null"; break;
				case io::UNKNOWN: out << "unknown"; break;
			default: break;
			}

			return out;
		}


		///  METHODS  ///

		constexpr bool isObject() const noexcept {
			return m_type == io::OBJECT;
		}

		constexpr bool isArray() const noexcept {
			return m_type == io::ARRAY;
		}

		constexpr bool isString() const noexcept {
			return m_type == io::STRING;
		}

		constexpr bool isFPNumber() const noexcept {
			return m_type == io::FP_NUMBER;
		}

		constexpr bool isINumber() const noexcept {
			return m_type == io::NUMBER;
		}

		constexpr bool isBool() const noexcept {
			return m_type == io::BOOL;
		}

		constexpr bool isTrue() const noexcept {
			return isBool() && asBool();
		}

		constexpr bool isFalse() const noexcept {
			return isBool() && !asBool();
		}

		constexpr bool isNull() const noexcept {
			return m_type == io::NULL_VALUE;
		}

		constexpr bool isUnknown() const noexcept {
			return m_type == io::UNKNOWN;
		}

		std::string toString() const {
			std::stringstream ss;
			ss << *this;

			return ss.str();
		}
		

		///  GETTERS AND SETTERS  ///

		inline void setAsObject(ObjectTy value) noexcept {
			this->~JsonValue();

			m_type = io::OBJECT;
			::new(&m_object) ObjectTy(std::move(value));
		}

		inline void setAsArray(ArrayTy value) noexcept {
			this->~JsonValue();

			m_type = io::ARRAY;
			::new(&m_array) ArrayTy(std::move(value));
		}

		inline void setAsString(StringTy value) noexcept {
			this->~JsonValue();

			m_type = io::STRING;
			::new(&m_str) StringTy(std::move(value));
		}

		inline void setAsFPNumber(FPTy value) noexcept {
			this->~JsonValue();

			m_fpNumber = value;
			m_type = io::FP_NUMBER;
		}

		inline void setAsINumber(IntegerTy value) noexcept {
			this->~JsonValue();

			m_iNumber = value;
			m_type = io::NUMBER;
		}

		inline void setAsBool(BoolTy value) noexcept {
			this->~JsonValue();

			m_iNumber = value;
			m_type = io::BOOL;
		}

		inline void setAsNull() noexcept {
			this->~JsonValue();
			m_type = io::NULL_VALUE;
		}

		inline void setAsUnknown() noexcept {
			this->~JsonValue();
			m_type = io::UNKNOWN;
		}


		constexpr const ObjectTy& asObject() const noexcept {
			assert(m_type == io::OBJECT);

			return m_object;
		}

		constexpr const ArrayTy& asArray() const noexcept {
			assert(m_type == io::ARRAY);

			return m_array;
		}

		constexpr const StringTy& asString() const noexcept {
			assert(m_type == io::STRING);

			return m_str;
		}

		constexpr FPTy asFPNumber() const noexcept {
			assert(m_type == io::FP_NUMBER);

			return m_fpNumber;
		}

		constexpr IntegerTy asINumber() const noexcept {
			assert(m_type == io::NUMBER);

			return m_iNumber;
		}

		constexpr BoolTy asBool() const noexcept {
			assert(m_type == io::BOOL);

			return bool(m_iNumber);
		}

		constexpr JsonValueType getType() const noexcept {
			return m_type;
		}
	};
}