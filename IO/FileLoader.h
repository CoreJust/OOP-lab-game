// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <string_view>

namespace io {
	// Loads file contents
	class FileLoader final {
		std::string m_directory;
		std::string m_extension;

	public:
		constexpr FileLoader(std::string directory, std::string extension = "") 
			: m_directory(std::move(directory)), m_extension(std::move(extension)) { }

		constexpr void setExtension(std::string extension) {
			m_extension = std::move(extension);
		}

		constexpr std::string getFullPath(std::string_view fileName) const {
			return m_directory + std::string(fileName) + m_extension;
		}

		std::string loadFile(std::string_view fileName) const;
	};
}