// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Logger.h"

#include <cassert>

#include <format>
#include <chrono>

io::Logger::Logger(std::ostream& out, Settings settings)
	: m_out(out), m_settings(std::move(settings)) {

}

void io::Logger::log(std::string_view header, std::string_view message, const std::source_location loc) {
    static const char* const FORMAT_STRS[2][2] = { // [printDate][printTime]
        { "[{0}]: ", "[{0} : {1:%T}]: " },
        { "[{0} : {1:%F}]: ", "[{0} : {1:%F} : {1:%T}]: " }
    };

    if (m_settings.printHeader) {
        auto time = std::chrono::system_clock::now();
        m_out << std::vformat(FORMAT_STRS[m_settings.printDate][m_settings.printTime], std::make_format_args(header, time));
    }

    m_out << message;

    if (m_settings.printSourceLocation) {
        m_out << std::format(
            "\nSource location: file {0}({1}:{2})\nFunction: {3}\n", 
            loc.file_name(), 
            loc.line(), 
            loc.column(), 
            loc.function_name()
        );
    }

    m_out << std::endl; // for flushing
}

void io::Logger::initInfoLogger(std::ostream& infoStream, Settings settings) {
    assert(s_infoLogger == nullptr);

    s_infoLogger = new Logger(infoStream, std::move(settings));
}

void io::Logger::initErrorLogger(std::ostream& errorStream, Settings settings) {
    assert(s_errorLogger == nullptr);

    s_errorLogger = new Logger(errorStream, std::move(settings));
}

void io::Logger::destroyLoggers() {
    assert(s_infoLogger != nullptr && s_errorLogger != nullptr);

    delete s_infoLogger;
    delete s_errorLogger;
    
    s_infoLogger = s_errorLogger = nullptr;
}

void io::Logger::logInfo(std::string_view message, const std::source_location loc) {
    assert(s_infoLogger != nullptr);

    s_infoLogger->log("INFO", message, loc);
}

void io::Logger::logError(std::string_view message, const std::source_location loc) {
    assert(s_errorLogger != nullptr);

    s_errorLogger->log("ERROR", message, loc);
}
