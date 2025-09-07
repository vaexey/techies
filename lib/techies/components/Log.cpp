#include "Log.hpp"
#include "components/Ethernet.hpp"

#define LOGLEVEL_TRACE 1
#define LOGLEVEL_DEBUG 2
#define LOGLEVEL_INFO 3
#define LOGLEVEL_WARNING 4
#define LOGLEVEL_ERROR 5
#define LOGLEVEL_CRITICAL 6

namespace techies::components
{
    Logger* Log;

    const char* LogLevelPrefix[] = {
        "[?????] ",
        "[TRACE] ",
        "[DEBUG] ",
        "[INFO]  ",
        "[WARN]  ",
        "[ERR]   ",
        "[CRIT]  "
    };

    void Logger::Log(const LogLevel level, const char* message)
    {
        Log(level, TCFG_C_LOG_DEFAULTTAG, message);
    }

    void Logger::Log(const LogLevel level, const String message)
    {
        Log(level, TCFG_C_LOG_DEFAULTTAG, message);
    }

    #define LogLevelFn(level, name) \
        void Logger::name(const char* message) \
        { Log(LogLevel::level, message); } \
        void Logger::name(const String message) \
        { Log(LogLevel::level, message); } \
        void Logger::name(const char* tag, const char* message) \
        { Log(LogLevel::level, tag, message); } \
        void Logger::name(const char* tag, const String message) \
        { Log(LogLevel::level, tag, message); }

    #define LogLevelFnPlaceholder(level, name) \
        void Logger::name(const char* message) {} \
        void Logger::name(const String message) {} \
        void Logger::name(const char* tag, const char* message) {} \
        void Logger::name(const char* tag, const String message) {}

    #if LOGLEVEL_TRACE >= TCFG_C_LOG_DEFAULTLEVEL
    LogLevelFn(TRACE, Trace);
    #else
    LogLevelFnPlaceholder(TRACE, Trace);
    #endif

    #if LOGLEVEL_DEBUG >= TCFG_C_LOG_DEFAULTLEVEL
    LogLevelFn(DEBUG, Debug);
    #else
    LogLevelFnPlaceholder(DEBUG, Debug);
    #endif

    #if LOGLEVEL_INFO >= TCFG_C_LOG_DEFAULTLEVEL
    LogLevelFn(INFO, Info);
    #else
    LogLevelFnPlaceholder(INFO, Info);
    #endif

    #if LOGLEVEL_WARNING >= TCFG_C_LOG_DEFAULTLEVEL
    LogLevelFn(WARNING, Warn);
    #else
    LogLevelFnPlaceholder(WARNING, Warn);
    #endif

    #if LOGLEVEL_ERROR >= TCFG_C_LOG_DEFAULTLEVEL
    LogLevelFn(ERROR, Err);
    #else
    LogLevelFnPlaceholder(ERROR, Err);
    #endif

    #if LOGLEVEL_CRITICAL >= TCFG_C_LOG_DEFAULTLEVEL
    LogLevelFn(CRITICAL, Crit);
    #else
    LogLevelFnPlaceholder(CRITICAL, Crit);
    #endif

    #undef LogLevelFn
    #undef LogLevelFnPlaceholder

    PrintLogger::PrintLogger(Print* _stream)
        : stream(_stream) {}

    void PrintLogger::Log(const LogLevel level, const char* tag, const char* message)
    {
        stream->print(LogLevelPrefix[(size_t)level]);
        stream->print(tag);

        for(int i = strlen(tag); i < TCFG_C_LOG_PRINT_TAG_INDENT; i++)
            stream->write(' ');

        stream->println(message);
    }

    void PrintLogger::Log(const LogLevel level, const char* tag, const String message)
    {
        stream->print(LogLevelPrefix[(size_t)level]);
        stream->print(tag);

        for(int i = strlen(tag); i < TCFG_C_LOG_PRINT_TAG_INDENT; i++)
            stream->write(' ');
        
        stream->println(message);
    }

    SpoonLogger::SpoonLogger() {}
    void SpoonLogger::Log(const LogLevel level, const char* tag, const char* message)
    {
        if(!techies::components::Ethernet::SpoonSocketActive)
            return;

        auto sock = techies::components::Ethernet::SpoonSocket;
        sock.beginPacket(
            IPAddress(TCFG_C_ETHERNET_SPOON_PEER_IP),
            TCFG_C_ETHERNET_SPOON_PEER_PORT
        );

        sock.write(LogLevelPrefix[(size_t)level]);
        sock.write(tag);

        for(int i = strlen(tag); i < TCFG_C_LOG_PRINT_TAG_INDENT; i++)
            sock.write(' ');

        sock.write(message);
        sock.write('\n');

        sock.endPacket();
    }

    void SpoonLogger::Log(const LogLevel level, const char* tag, const String message)
    {
        if(!techies::components::Ethernet::SpoonSocketActive)
            return;
        
        auto sock = techies::components::Ethernet::SpoonSocket;
        sock.beginPacket(
            IPAddress(TCFG_C_ETHERNET_SPOON_PEER_IP),
            TCFG_C_ETHERNET_SPOON_PEER_PORT
        );

        sock.write(LogLevelPrefix[(size_t)level]);
        sock.write(tag);

        for(int i = strlen(tag); i < TCFG_C_LOG_PRINT_TAG_INDENT; i++)
            sock.write(' ');
        
        sock.write(message.c_str());
        sock.write('\n');

        sock.endPacket();
    }

    FullLogger::FullLogger(Print* _stream)
        : PrintL(_stream) {}

    void FullLogger::Log(const LogLevel level, const char* tag, const char* message)
    {
        PrintL.Log(level, tag, message);
        SpoonL.Log(level, tag, message);
    }

    void FullLogger::Log(const LogLevel level, const char* tag, const String message)
    {
        PrintL.Log(level, tag, message);
        SpoonL.Log(level, tag, message);
    }

} // namespace techies::components
