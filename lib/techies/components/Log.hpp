#pragma once
#include "core/HAL.hpp"

#define L techies::components::Log

namespace techies::components
{

    class Logger;
    extern Logger* Log;

    enum class LogLevel : uint8_t
    {
        TRACE = 1,
        DEBUG = 2,
        INFO = 3,
        WARNING = 4,
        ERROR = 5,
        CRITICAL = 6
    };

    extern const char* LogLevelPrefix[];

    class Logger
    {
    public:
        virtual void Log(const LogLevel level, const char* message) = 0;
        virtual void Log(const LogLevel level, const String message) = 0;

        void Trace(const char* message);
        void Trace(const String message);
        void Debug(const char* message);
        void Debug(const String message);
        void Info(const char* message);
        void Info(const String message);
        void Warn(const char* message);
        void Warn(const String message);
        void Err(const char* message);
        void Err(const String message);
        void Crit(const char* message);
        void Crit(const String message);
    };

    class PrintLogger : public Logger
    {
    public:
        PrintLogger(Print* stream);

        void Log(const LogLevel level, const char* message);
        void Log(const LogLevel level, const String message);

    protected:
        Print* stream;
    };

} // namespace techies::components
