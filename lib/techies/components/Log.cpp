#include "Log.hpp"

#define LOGLEVEL_TRACE 1
#define LOGLEVEL_DEBUG 2
#define LOGLEVEL_INFO 3
#define LOGLEVEL_WARNING 4
#define LOGLEVEL_ERROR 5
#define LOGLEVEL_CRITICAL 6

#define MIN_LOGLEVEL LOGLEVEL_INFO

namespace techies::components
{
    Logger* Log;

    const char* LogLevelPrefix[] = {
        "[?????] ",
        "[TRACE] ",
        "[DEBUG] ",
        "[INFO ] ",
        "[WARN ] ",
        "[ ERR ] ",
        "[CRIT ] "
    };

    #define LogLevelFn(level, name) \
        void Logger::name(const char* message) \
        { Log(LogLevel::level, message); } \
        void Logger::name(const String message) \
        { Log(LogLevel::level, message); }

    #define LogLevelFnPlaceholder(level, name) \
        void Logger::name(const char* message) {} \
        void Logger::name(const String message) {}

    #if LOGLEVEL_TRACE >= MIN_LOGLEVEL
    LogLevelFn(TRACE, Trace);
    #else
    LogLevelFnPlaceholder(TRACE, Trace);
    #endif

    #if LOGLEVEL_DEBUG >= MIN_LOGLEVEL
    LogLevelFn(DEBUG, Debug);
    #else
    LogLevelFnPlaceholder(DEBUG, Debug);
    #endif

    #if LOGLEVEL_INFO >= MIN_LOGLEVEL
    LogLevelFn(INFO, Info);
    #else
    LogLevelFnPlaceholder(INFO, Info);
    #endif

    #if LOGLEVEL_WARNING >= MIN_LOGLEVEL
    LogLevelFn(WARNING, Warn);
    #else
    LogLevelFnPlaceholder(WARNING, Warn);
    #endif

    #if LOGLEVEL_ERROR >= MIN_LOGLEVEL
    LogLevelFn(ERROR, Err);
    #else
    LogLevelFnPlaceholder(ERROR, Err);
    #endif

    #if LOGLEVEL_CRITICAL >= MIN_LOGLEVEL
    LogLevelFn(CRITICAL, Crit);
    #else
    LogLevelFnPlaceholder(CRITICAL, Crit);
    #endif

    #undef LogLevelFn
    #undef LogLevelFnPlaceholder

    PrintLogger::PrintLogger(Print* _stream)
        : stream(_stream) {}

    void PrintLogger::Log(const LogLevel level, const char* message)
    {
        stream->print(LogLevelPrefix[(size_t)level]);
        stream->println(message);
    }

    void PrintLogger::Log(const LogLevel level, const String message)
    {
        stream->print(LogLevelPrefix[(size_t)level]);
        stream->println(message);
    }

} // namespace techies::components
