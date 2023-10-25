// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "JsonParser.h"
#include "IO/File/FileLoader.h"

/*
*	JsonFileParser.h contains a class that allows to parse a json file.
*	It is based on the parent class JsonParser.
* 
*	This class is base for some more specific parsers.
*
*	Usage:
*		io::JsonFileParser parser("res/jsons/");
*		auto result = parser.parse("data"); // data.json
*		if (result.isOk()) {
*			// Do something with the result here
*		}
*/

namespace io {
	class JsonFileParser : public JsonParser {
	private:
		io::FileLoader m_loader;

	public:
		constexpr JsonFileParser(std::string directory) : m_loader(std::move(directory), ".json") { }

		inline utils::Result<io::JsonValue> parse(std::string_view fileName) {
			std::string jsonText = m_loader.loadFile(fileName);
			if (jsonText.empty()) {
				return utils::Failure("Failed to retrieve json file contents");
			}

			JsonParser::setText(jsonText);
			return JsonParser::parse();
		}
	};
}