// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <chrono>
#include <source_location>

#include "LogLevel.h"
#include "LogTarget.h"

/*
*	Logger(.h/.cpp) contains a class that allows to log information and errors.
*
*	After initializing, it writes formatted messages into the given output.
*   The general interface is static (first we statically initialize the
*   logger, then use it, and in the end we destroy it).
* 
*   A logger can directly accept logged strings with their log level or
*   more high-level messages (which are not guaranteed to be logged immediately).
*/

namespace io {
    class Message;

    // Mostly consists of static interface
    // Implements a modified singleton pattern
    class Logger final {
    public:
        struct Settings {
            LogLevel logDateFrom = LogLevel::ERROR;
            LogLevel logTimeFrom = LogLevel::TRACE;
            LogLevel logSourceLocationFrom = LogLevel::WARNING;

            LogLevel loggingLevel = LogLevel::TRACE; // Messages with lower priority would be ignored
        };

    private:
        Settings m_settings;
        std::vector<LogTarget> m_targets;

    private:
        inline constinit static Logger* s_logger = nullptr;

    protected:
        Logger(Settings settings, std::vector<LogTarget> targets);

        void set(Settings settings, std::vector<LogTarget> targets);

        void log(LogLevel level, std::string_view message, const std::source_location& loc);
        void log(const Message& msg);

        std::string getLogString(LogLevel level, const std::source_location& loc, const std::chrono::system_clock::time_point& time);

    public:
        static void initLogger();
        static void destroyLogger();

        static void trace(std::string_view message, const std::source_location& loc = std::source_location::current());
        static void debug(std::string_view message, const std::source_location& loc = std::source_location::current());
        static void info(std::string_view message, const std::source_location& loc = std::source_location::current());
        static void warning(std::string_view message, const std::source_location& loc = std::source_location::current());
        static void error(std::string_view message, const std::source_location& loc = std::source_location::current());
        static void fatal(std::string_view message, const std::source_location& loc = std::source_location::current());

        static void message(const Message& msg);
    };
}