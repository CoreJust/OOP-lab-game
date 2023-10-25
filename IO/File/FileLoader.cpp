// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "FileLoader.h"

#include <fstream>
#include <sstream>

#include "IO/Logger.h"

std::string io::FileLoader::loadFile(std::string_view fileName) const {
    std::ifstream file(getFullPath(fileName));
    if (!file.is_open()) {
        io::Logger::logError("Failed to load file: " + getFullPath(fileName));
        return "";
    }

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
