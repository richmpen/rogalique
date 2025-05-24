#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <sstream>

enum class LogLevel { Info, Warning, Error };

class LogSink {
public:
    virtual void log(LogLevel level, const std::string& message) = 0;
    virtual ~LogSink() = default;
};

class ConsoleSink : public LogSink {
private:
    std::string lastMessage;
public:
    void log(LogLevel level, const std::string& message) override {
        if (message != lastMessage) {
            std::cout << logLevelToString(level) << " " << message << std::endl;
            lastMessage = message;
        }
    }

private:
    std::string logLevelToString(LogLevel level) {
        switch (level) {
        case LogLevel::Info: return "[\033[32mInfo\033[0m]";
        case LogLevel::Warning: return "[\033[33mWarning\033[0m]";
        case LogLevel::Error: return "[\033[31mERROR\033[0m]";
        default: return "[UNKNOWN]";
        }
    }
};

class FileSink : public LogSink {
private:
    std::ofstream logFile;
    std::string lastMessage;
public:
    FileSink(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }

    void log(LogLevel level, const std::string& message) override {
        if (logFile && message != lastMessage) {
            logFile << logLevelToString(level) << " " << message << std::endl;
            lastMessage = message;
        }
    }

    ~FileSink() {
        if (logFile.is_open()) logFile.close();
    }

private:
    std::string logLevelToString(LogLevel level) {
        switch (level) {
        case LogLevel::Info: return "[INFO]";
        case LogLevel::Warning: return "[WARNING]";
        case LogLevel::Error: return "[ERROR]";
        default: return "[UNKNOWN]";
        }
    }
};

class Logger {
private:
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::mutex logMutex;
    std::string lastMessage;

public:
    void addSink(std::shared_ptr<LogSink> sink) {
        sinks.push_back(sink);
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        
        if (message == lastMessage) {
            return;
        }
        
        lastMessage = message;
        
        for (auto& sink : sinks) {
            sink->log(level, message);
        }
    }

    void info(const std::string& message) { log(LogLevel::Info, message); }
    void warn(const std::string& message) { log(LogLevel::Warning, message); }
    void error(const std::string& message) { log(LogLevel::Error, message); }
};

class LoggerRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
    std::shared_ptr<Logger> defaultLogger;
    std::mutex registryMutex;

public:
    static LoggerRegistry& getInstance() {
        static LoggerRegistry instance;
        return instance;
    }

    std::shared_ptr<Logger> getLogger(const std::string& name) {
        std::lock_guard<std::mutex> lock(registryMutex);
        if (loggers.find(name) != loggers.end()) {
            return loggers[name];
        }
        return defaultLogger;
    }

    void setDefaultLogger(std::shared_ptr<Logger> logger) {
        defaultLogger = logger;
    }

    void registerLogger(const std::string& name, std::shared_ptr<Logger> logger) {
        std::lock_guard<std::mutex> lock(registryMutex);
        loggers[name] = logger;
    }
};

#define LOG_INFO(message) { \
std::ostringstream _oss; \
_oss << message; \
LoggerRegistry::getInstance().getLogger("global")->info(_oss.str()); \
}

#define LOG_WARN(message) { \
std::ostringstream _oss; \
_oss << message; \
LoggerRegistry::getInstance().getLogger("global")->warn(_oss.str()); \
}

#define LOG_ERROR(message) { \
std::ostringstream _oss; \
_oss << message; \
LoggerRegistry::getInstance().getLogger("global")->error(_oss.str()); \
}