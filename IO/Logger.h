// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string_view>
#include <source_location>
#include <ostream>

/*
*	Logger(.h/.cpp) contains a class that allows to log information and errors.
*
*	After initializing, it writes formatted messages into the given output.
*/

namespace io {
// Mostly consists of static interface
// Implements the singleton pattern
    class Logger final {
    public:
        struct Settings {
            bool printHeader = true; // [INFO] or [ERROR]
            bool printDate = false;
            bool printTime = true;
            bool printSourceLocation = false;
        };

    private:
        std::ostream& m_out;
        Settings m_settings;

    protected:
        Logger(std::ostream& out, Settings settings);

        void log(std::string_view header, std::string_view message, const std::source_location loc);

    public:
        static void initInfoLogger(std::ostream& infoStream, Settings settings);
        static void initErrorLogger(std::ostream& errorStream, Settings settings);
        static void destroyLoggers();

        static void logInfo(std::string_view message, const std::source_location loc = std::source_location::current());
        static void logError(std::string_view message, const std::source_location loc = std::source_location::current());

    private:
        inline constinit static Logger* s_infoLogger = nullptr;
        inline constinit static Logger* s_errorLogger = nullptr;
    };
}