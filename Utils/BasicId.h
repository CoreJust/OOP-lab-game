// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include "EnumWrap.h"

/*
*	BasicId.h contains a base class for all the Id classes.
* 
*	All of the Id classes are wrappers over an enumeration.
*	It allows for a type that is generally used as an enumeration
*	to have own operators and, most importantly, methods.
* 
*	Despite being in the Utils module, the BasicId is not a part 
*	of the utils namespace since it doesn't logically belong to the
*	module - it is more of a compromise with no better alternative.
*/

using id_t = uint32_t;

// Basic class for all the Ids
class BasicId : public utils::EnumWrap<id_t> {
public:
	constexpr BasicId() = delete;
	constexpr BasicId(const id_t value) noexcept : utils::EnumWrap<id_t>(value) { }

	constexpr BasicId& operator=(const BasicId other) noexcept {
		m_value = other;

		return *this;
	}

	inline virtual std::string_view toString() const override {
		assert(false && "unreachable; BasicId::toString() not expected to be called");
		return "";
	}
};