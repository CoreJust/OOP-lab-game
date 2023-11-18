// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <string_view>

/*
*	FileLoader(.h/.cpp) contains a class that allows to load files comfortably.
*
*	We first create a loader for some directory and file extension,
*	then load files by their name completely into a string.
* 
*	Usage:
*		io::FileLoader loader("some_dir/", ".extension");
*		std::string contents = loader.loadFile("file_name");
* 
*		// contents now contain the contents of file some_dir/file_name.extension
*/

namespace io {
	// Loads file contents
	class FileLoader final {
		std::string m_directory;
		std::string m_extension;

	public:
		constexpr FileLoader(std::string directory = "", std::string extension = "")
			: m_directory(std::move(directory)), m_extension(std::move(extension)) { }

		constexpr void setExtension(std::string extension) {
			m_extension = std::move(extension);
		}

		constexpr void setDirectory(std::string directory) {
			m_directory = std::move(directory);
		}

		constexpr std::string getFullPath(std::string_view fileName) const {
			return m_directory + std::string(fileName) + m_extension;
		}

		std::string loadFile(std::string_view fileName) const;
	};
}