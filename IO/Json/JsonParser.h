// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string_view>

#include "JsonValue.h"
#include "Utils/Result.h"

/*
*	JsonParser(.h/.cpp) contains a base class for parsing some input.
*
*	It takes as input a string and parses it as a json
*/

namespace io {
	class JsonParser {
	private:
		std::string_view m_text;
		size_t m_pos = 0;

	public:
		constexpr JsonParser() noexcept : m_text() { }
		constexpr JsonParser(std::string_view view) noexcept : m_text(view) { }

		constexpr void setText(std::string_view view) {
			m_text = view;
			m_pos = 0;
		}

		utils::Result<JsonValue> parse();

	private:
		utils::Result<JsonValue> parseObject();
		utils::Result<JsonValue> parseArray();

		utils::Result<JsonValue> parseString();
		utils::Result<JsonValue> parseNumber();
		utils::Result<JsonValue> parseWord(); // true, false, null

		void skipWS(); // skipping all whitespaces
		bool match(char ch) ;
		char next();
		char peek(int32_t relPos = 0); // allows to peek into a char relatively to the current position
	};
}