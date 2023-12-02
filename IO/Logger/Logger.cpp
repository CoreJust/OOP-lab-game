// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Logger.h"
#include <format>

#include "IO/File/LoggerSettingsLoader.h"
#include "IO/Message/Message.h"

io::Logger::Logger(Settings settings, std::vector<LogTarget> targets)
    : m_settings(std::move(settings)), m_targets(std::move(targets)) {

}

void io::Logger::set(Settings settings, std::vector<LogTarget> targets) {
    m_settings = std::move(settings);
    m_targets = std::move(targets);
}

void io::Logger::log(LogLevel level, std::string_view message, const std::source_location& loc) {
    if (!m_settings.loggingLevel.allowsLoggingOf(level)) {
        return; // Doesn't log anything
    }

    std::string logStr = getLogString(level, loc, std::chrono::system_clock::now());
    for (auto& target : m_targets) {
        target.target() << logStr << message << std::endl;
    }
}

void io::Logger::log(const Message& msg) {
    if (!m_settings.loggingLevel.allowsLoggingOf(msg.getLogLevel())) {
        return; // Doesn't log anything
    }

    std::string logStr = getLogString(msg.getLogLevel(), msg.getLocation(), msg.getCreationTime());
    for (auto& target : m_targets) {
        target.target() << logStr << "MESSAGE: " << msg << std::endl;
    }
}

std::string io::Logger::getLogString(LogLevel level, const std::source_location& loc, const std::chrono::system_clock::time_point& time) {
    static const char* const FORMAT_STRS[2][2] = { // [printDate][printTime]
        { "[{0}]: ", "[{0} : {1:%T}]: " },
        { "[{0} : {1:%F}]: ", "[{0} : {1:%F} : {1:%T}]: " }
    };

    std::string logStr = std::vformat(
        FORMAT_STRS[m_settings.logDateFrom.allowsLoggingOf(level)][m_settings.logTimeFrom.allowsLoggingOf(level)],
        std::make_format_args(std::string(level.toString()), time)
    );

    if (m_settings.logSourceLocationFrom.allowsLoggingOf(level)) {
        logStr += std::format(
            "\nSource location: file {0}({1}:{2})\nFunction: {3}\n",
            loc.file_name(),
            loc.line(),
            loc.column(),
            loc.function_name()
        );
    }

    return logStr;
}

void io::Logger::initLogger() {
    assert(s_logger == nullptr);

    {
        // Default initialization (in case of errors during loading the actual logger
        Settings settings;
        std::vector<LogTarget> targets;

        LoggerSettingsLoader(settings, targets).loadDefault();
        s_logger = new Logger(std::move(settings), std::move(targets));
    }

    // Trying to load the logger settings from a file
    Settings settings;
    std::vector<LogTarget> targets;

    auto result = LoggerSettingsLoader(settings, targets).load();
    s_logger->set(std::move(settings), std::move(targets));

    if (!result.isOk()) {
        error("Logger: failed to load logger settings from a file, got: " + result.error());
    }
}

void io::Logger::destroyLogger() {
    assert(s_logger != nullptr);

    delete s_logger;
    s_logger = nullptr;
}

void io::Logger::trace(std::string_view message, const std::source_location& loc) {
    assert(s_logger != nullptr);

    s_logger->log(LogLevel::TRACE, message, loc);
}

void io::Logger::debug(std::string_view message, const std::source_location& loc) {
    assert(s_logger != nullptr);

    s_logger->log(LogLevel::DEBUG, message, loc);
}

void io::Logger::info(std::string_view message, const std::source_location& loc) {
    assert(s_logger != nullptr);

    s_logger->log(LogLevel::INFO, message, loc);
}

void io::Logger::warning(std::string_view message, const std::source_location& loc) {
    assert(s_logger != nullptr);

    s_logger->log(LogLevel::WARNING, message, loc);
}

void io::Logger::error(std::string_view message, const std::source_location& loc) {
    assert(s_logger != nullptr);

    s_logger->log(LogLevel::ERROR, message, loc);
}

void io::Logger::fatal(std::string_view message, const std::source_location& loc) {
    assert(s_logger != nullptr);

    s_logger->log(LogLevel::FATAL, message, loc);
}

void io::Logger::message(const Message& msg) {
    assert(s_logger != nullptr);

    s_logger->log(msg);
}
