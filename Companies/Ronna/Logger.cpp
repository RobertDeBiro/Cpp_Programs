/*
Issues with the current approach:

Global state:
Using a static map means the logger state is global, which can make testing difficult and introduce potential threading issues (though you do have mutex protection).

Limited configurability:
As you noted, the logger configuration is fixed at initialization time with no easy way to reconfigure.

Tight coupling:
The Logger class handles too many responsibilities - directory creation, file management, logging configuration, and actual logging.

Not truly object-oriented:
Despite being a class, most methods are static, and the logger object itself has limited functionality beyond holding the spdlog instance.

Initialization approach is awkward:
Having separate Initialize methods for different logger types creates a fragmented API.

The main strange aspect is that you have a class, but it's used mostly through static methods rather than as an object with instance methods.
It seems like your colleague tried to combine an object-oriented approach with a procedural/static utility approach,
resulting in something that has aspects of both but the benefits of neither.
A more traditional OO approach would be to have Logger instances that you configure and use directly,
or a more traditional static utility approach would be to have all static methods without creating Logger objects at all.
The current hybrid approach is somewhat unusual.
*/

// Logger.h
#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <mutex>

namespace spdlog {
    class logger;
    namespace sinks {
        class sink;
    }
}

class PatternFormatter;

namespace rtkdata {

// Forward declaration
class LoggerFactory;

// Enum for log levels
enum class LogLevel {
    trace,
    debug,
    info,
    warn,
    error,
    critical,
    off
};

// Configuration class for loggers
class LoggerConfig {
public:
    std::string baseDir;
    std::string subDir;
    LogLevel level;
    bool enableConsole;
    int maxFileSizeMB;
    int maxFiles;
    int maxOldDirFiles;
    std::string pattern;

    LoggerConfig(
        std::string baseDir = "Logs",
        std::string subDir = "default_logs",
        LogLevel level = LogLevel::info,
        bool enableConsole = true,
        int maxFileSizeMB = 10,
        int maxFiles = 5,
        int maxOldDirFiles = 10,
        std::string pattern = "[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] [%n] [T%t] [%s:%#] %v"
    );

    // Fluent interface for configuration
    LoggerConfig& setBaseDir(std::string dir);
    LoggerConfig& setSubDir(std::string dir);
    LoggerConfig& setLevel(LogLevel lvl);
    LoggerConfig& enableConsoleOutput(bool enable);
    LoggerConfig& setMaxFileSize(int sizeMB);
    LoggerConfig& setMaxFiles(int count);
    LoggerConfig& setMaxOldFiles(int count);
    LoggerConfig& setPattern(std::string fmt);
};

// Main Logger class
class Logger {
private:
    std::string name;
    std::shared_ptr<spdlog::logger> logger;
    LoggerConfig config;
    
    // Constructor is private, created via LoggerFactory
    Logger(const std::string& name, const LoggerConfig& config);
    
    // Apply configuration
    void applyConfig();
    
    // Create sinks based on configuration
    std::vector<std::shared_ptr<spdlog::sinks::sink>> createSinks(const std::filesystem::path& logFilePath);
    
    // Create pattern formatter
    std::shared_ptr<PatternFormatter> createFormatter();
    
    // Friend class for creation
    friend class LoggerFactory;

public:
    // Destructor
    ~Logger();

    // Non-copyable
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    // Reconfigure logger at runtime
    void reconfigure(const LoggerConfig& newConfig);
    
    // Log methods
    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);
    
    // Template methods for formatted logging
    template<typename... Args>
    void trace(const std::string& fmt, const Args&... args);
    
    template<typename... Args>
    void debug(const std::string& fmt, const Args&... args);
    
    template<typename... Args>
    void info(const std::string& fmt, const Args&... args);
    
    template<typename... Args>
    void warn(const std::string& fmt, const Args&... args);
    
    template<typename... Args>
    void error(const std::string& fmt, const Args&... args);
    
    template<typename... Args>
    void critical(const std::string& fmt, const Args&... args);
    
    // Getters
    std::string getName() const { return name; }
    LoggerConfig getConfig() const { return config; }
    std::shared_ptr<spdlog::logger> getSpdLogger() const { return logger; }
};

// Factory class for creating and managing loggers
class LoggerFactory {
private:
    static std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
    static std::mutex loggerMutex;
    
    // File and path utilities
    static std::filesystem::path generateLogFilePath(const std::string& baseDir, const std::string& subDir);
    static std::string trimSlashes(const std::string& dirName);
    static void sortAndCleanupLogFiles(const std::filesystem::path& logsDirPath, int maxOldFiles);
    static std::filesystem::path getBuildDirPath();

public:
    // Get or create a logger
    static std::shared_ptr<Logger> getLogger(const std::string& name, const LoggerConfig& config = LoggerConfig());
    
    // Get an existing logger (throws if not found)
    static std::shared_ptr<Logger> getExistingLogger(const std::string& name);
    
    // Check if logger exists
    static bool hasLogger(const std::string& name);
    
    // Create multiple loggers with the same config
    static std::vector<std::shared_ptr<Logger>> createLoggers(
        const std::vector<std::string>& names, 
        const LoggerConfig& config = LoggerConfig()
    );
    
    // Special loggers
    static std::shared_ptr<Logger> createStdoutLogger(const LoggerConfig& config = LoggerConfig("Logs", "std_logs"));
    static std::shared_ptr<Logger> createStderrLogger(const LoggerConfig& config = LoggerConfig("Logs", "std_logs"));
    static std::shared_ptr<Logger> createGtkLogger(const LoggerConfig& config = LoggerConfig("Logs", "gtk_logs"));
    
    // Reset all loggers (mainly for testing)
    static void resetAll();
};

// StreamBuffer implementation for std::cout and std::cerr redirection
class StreamBuffer : public std::streambuf {
private:
    std::shared_ptr<spdlog::logger> logger;
    LogLevel level;
    std::string buffer;

public:
    StreamBuffer(std::shared_ptr<spdlog::logger> logger, LogLevel level);
    
    // Implementation of overflow for streambuf
    int_type overflow(int_type ch) override;
    
    // Implementation of sync for streambuf
    int sync() override;
};

// GTK log handler
void handleGtkLog(const gchar* logDomain, GLogLevelFlags level, const gchar* message, gpointer userData);

} // namespace rtkdata

// Logger.cpp implementation
#include "Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/pattern_formatter.h>

namespace rtkdata {

// Initialize static members
std::unordered_map<std::string, std::shared_ptr<Logger>> LoggerFactory::loggers;
std::mutex LoggerFactory::loggerMutex;

// LoggerConfig implementation
LoggerConfig::LoggerConfig(
    std::string baseDir,
    std::string subDir,
    LogLevel level,
    bool enableConsole,
    int maxFileSizeMB,
    int maxFiles,
    int maxOldDirFiles,
    std::string pattern
) : baseDir(std::move(baseDir)),
    subDir(std::move(subDir)),
    level(level),
    enableConsole(enableConsole),
    maxFileSizeMB(maxFileSizeMB),
    maxFiles(maxFiles),
    maxOldDirFiles(maxOldDirFiles),
    pattern(std::move(pattern)) {}

// Fluent interface for LoggerConfig
LoggerConfig& LoggerConfig::setBaseDir(std::string dir) { baseDir = std::move(dir); return *this; }
LoggerConfig& LoggerConfig::setSubDir(std::string dir) { subDir = std::move(dir); return *this; }
LoggerConfig& LoggerConfig::setLevel(LogLevel lvl) { level = lvl; return *this; }
LoggerConfig& LoggerConfig::enableConsoleOutput(bool enable) { enableConsole = enable; return *this; }
LoggerConfig& LoggerConfig::setMaxFileSize(int sizeMB) { maxFileSizeMB = sizeMB; return *this; }
LoggerConfig& LoggerConfig::setMaxFiles(int count) { maxFiles = count; return *this; } 
LoggerConfig& LoggerConfig::setMaxOldFiles(int count) { maxOldDirFiles = count; return *this; }
LoggerConfig& LoggerConfig::setPattern(std::string fmt) { pattern = std::move(fmt); return *this; }

// Logger implementation
Logger::Logger(const std::string& name, const LoggerConfig& config)
    : name(name), config(config) {
    logger = std::make_shared<spdlog::logger>(name);
    applyConfig();
}

Logger::~Logger() {
    // Ensure all logs are flushed when logger is destroyed
    if (logger) {
        logger->flush();
    }
}

void Logger::applyConfig() {
    // Convert LogLevel to spdlog level
    spdlog::level::level_enum spdLogLevel;
    switch(config.level) {
        case LogLevel::trace: spdLogLevel = spdlog::level::trace; break;
        case LogLevel::debug: spdLogLevel = spdlog::level::debug; break;
        case LogLevel::info: spdLogLevel = spdlog::level::info; break;
        case LogLevel::warn: spdLogLevel = spdlog::level::warn; break;
        case LogLevel::error: spdLogLevel = spdlog::level::err; break;
        case LogLevel::critical: spdLogLevel = spdlog::level::critical; break;
        case LogLevel::off: spdLogLevel = spdlog::level::off; break;
        default: spdLogLevel = spdlog::level::info;
    }
    
    logger->set_level(spdLogLevel);
    
    // Generate log file path
    std::filesystem::path logFilePath = LoggerFactory::generateLogFilePath(config.baseDir, config.subDir);
    
    // Clear existing sinks and create new ones
    logger->sinks().clear();
    
    // Add new sinks
    auto sinks = createSinks(logFilePath);
    for (const auto& sink : sinks) {
        logger->sinks().push_back(sink);
    }
    
    // Register logger with spdlog and set flush interval
    spdlog::register_logger(logger);
    spdlog::flush_every(std::chrono::seconds(1));
}

std::vector<std::shared_ptr<spdlog::sinks::sink>> Logger::createSinks(const std::filesystem::path& logFilePath) {
    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;
    
    // Create file sink
    const int KB = 1024;
    const int MB = 1024 * KB;
    int maxSize = config.maxFileSizeMB * MB;
    
    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        logFilePath.string(), maxSize, config.maxFiles, false);
    
    // Set formatter
    auto formatter = createFormatter();
    fileSink->set_formatter(formatter->clone());
    
    // Set level
    spdlog::level::level_enum spdLogLevel;
    switch(config.level) {
        case LogLevel::trace: spdLogLevel = spdlog::level::trace; break;
        case LogLevel::debug: spdLogLevel = spdlog::level::debug; break;
        case LogLevel::info: spdLogLevel = spdlog::level::info; break;
        case LogLevel::warn: spdLogLevel = spdlog::level::warn; break;
        case LogLevel::error: spdLogLevel = spdlog::level::err; break;
        case LogLevel::critical: spdLogLevel = spdlog::level::critical; break;
        case LogLevel::off: spdLogLevel = spdlog::level::off; break;
        default: spdLogLevel = spdlog::level::info;
    }
    fileSink->set_level(spdLogLevel);
    
    sinks.push_back(fileSink);
    
    // Add console sink if enabled
    if (config.enableConsole) {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_formatter(formatter->clone());
        consoleSink->set_level(spdLogLevel);
        sinks.push_back(consoleSink);
    }
    
    return sinks;
}

std::shared_ptr<PatternFormatter> Logger::createFormatter() {
    return std::make_shared<PatternFormatter>(config.pattern, spdlog::pattern_time_type::local);
}

void Logger::reconfigure(const LoggerConfig& newConfig) {
    config = newConfig;
    applyConfig();
}

// Basic logging methods
void Logger::trace(const std::string& message) { logger->trace(message); }
void Logger::debug(const std::string& message) { logger->debug(message); }
void Logger::info(const std::string& message) { logger->info(message); }
void Logger::warn(const std::string& message) { logger->warn(message); }
void Logger::error(const std::string& message) { logger->error(message); }
void Logger::critical(const std::string& message) { logger->critical(message); }

// Template methods implementation
template<typename... Args>
void Logger::trace(const std::string& fmt, const Args&... args) {
    logger->trace(fmt, args...);
}

template<typename... Args>
void Logger::debug(const std::string& fmt, const Args&... args) {
    logger->debug(fmt, args...);
}

template<typename... Args>
void Logger::info(const std::string& fmt, const Args&... args) {
    logger->info(fmt, args...);
}

template<typename... Args>
void Logger::warn(const std::string& fmt, const Args&... args) {
    logger->warn(fmt, args...);
}

template<typename... Args>
void Logger::error(const std::string& fmt, const Args&... args) {
    logger->error(fmt, args...);
}

template<typename... Args>
void Logger::critical(const std::string& fmt, const Args&... args) {
    logger->critical(fmt, args...);
}

// LoggerFactory implementation
std::shared_ptr<Logger> LoggerFactory::getLogger(const std::string& name, const LoggerConfig& config) {
    std::lock_guard<std::mutex> lock(loggerMutex);
    
    auto it = loggers.find(name);
    if (it != loggers.end()) {
        return it->second;
    }
    
    auto logger = std::make_shared<Logger>(name, config);
    loggers[name] = logger;
    return logger;
}

std::shared_ptr<Logger> LoggerFactory::getExistingLogger(const std::string& name) {
    std::lock_guard<std::mutex> lock(loggerMutex);
    
    auto it = loggers.find(name);
    if (it != loggers.end()) {
        return it->second;
    }
    
    throw std::runtime_error("Logger not found: " + name);
}

bool LoggerFactory::hasLogger(const std::string& name) {
    std::lock_guard<std::mutex> lock(loggerMutex);
    return loggers.find(name) != loggers.end();
}

std::vector<std::shared_ptr<Logger>> LoggerFactory::createLoggers(
    const std::vector<std::string>& names, 
    const LoggerConfig& config) {
    
    std::vector<std::shared_ptr<Logger>> result;
    for (const auto& name : names) {
        result.push_back(getLogger(name, config));
    }
    return result;
}

std::shared_ptr<Logger> LoggerFactory::createStdoutLogger(const LoggerConfig& config) {
    auto logger = getLogger("stdout", config);
    
    // Create and set stream buffer for std::cout
    static StreamBuffer stdoutBuffer(logger->getSpdLogger(), config.level);
    std::cout.rdbuf(&stdoutBuffer);
    
    return logger;
}

std::shared_ptr<Logger> LoggerFactory::createStderrLogger(const LoggerConfig& config) {
    auto logger = getLogger("stderr", config);
    
    // Create and set stream buffer for std::cerr
    static StreamBuffer stderrBuffer(logger->getSpdLogger(), config.level);
    std::cerr.rdbuf(&stderrBuffer);
    
    return logger;
}

std::shared_ptr<Logger> LoggerFactory::createGtkLogger(const LoggerConfig& config) {
    auto logger = getLogger("gtk", config);
    
    // Set GTK log handler
    g_log_set_default_handler(handleGtkLog, logger.get());
    
    return logger;
}

void LoggerFactory::resetAll() {
    std::lock_guard<std::mutex> lock(loggerMutex);
    loggers.clear();
}

std::filesystem::path LoggerFactory::generateLogFilePath(const std::string& baseDir, const std::string& subDir) {
    std::string validBaseDir = trimSlashes(baseDir);
    std::string validSubDir = trimSlashes(subDir);
    
    std::filesystem::path logsDirPath = getBuildDirPath() / validBaseDir / validSubDir;
    
    // Create directory if it doesn't exist
    if (!std::filesystem::exists(logsDirPath)) {
        std::filesystem::create_directories(logsDirPath);
    } else {
        sortAndCleanupLogFiles(logsDirPath, 10); // Use a default of 10 here, could use a parameter
    }
    
    // Generate filename with timestamp
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_r(&now, &localTime);
    
    char timestamp[30];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", &localTime);
    
    std::string logFileName = validSubDir + "_" + timestamp + ".log";
    return logsDirPath / logFileName;
}

std::string LoggerFactory::trimSlashes(const std::string& dirName) {
    auto first_it = std::ranges::find_if(dirName, [](char c) { return c != '/'; });
    auto last_it = std::ranges::find_if(dirName | std::views::reverse, [](char c) { return c != '/'; }).base();
    
    return (first_it < last_it) ? std::string(first_it, last_it) : "";
}

void LoggerFactory::sortAndCleanupLogFiles(const std::filesystem::path& logsDirPath, int maxOldFiles) {
    std::vector<std::filesystem::directory_entry> oldFiles;
    for (const auto& entry : std::filesystem::directory_iterator(logsDirPath)) {
        if (entry.is_regular_file()) {
            oldFiles.push_back(entry);
        }
    }
    
    // Sort by last write time (newest first)
    std::ranges::sort(oldFiles, [](const auto& a, const auto& b) {
        return std::filesystem::last_write_time(a) > std::filesystem::last_write_time(b);
    });
    
    // Remove excess files
    while (oldFiles.size() > static_cast<size_t>(maxOldFiles)) {
        std::filesystem::remove(oldFiles.back().path());
        oldFiles.pop_back();
    }
}

std::filesystem::path LoggerFactory::getBuildDirPath() {
    std::string fileBuffer(PATH_MAX, '\0');
    ssize_t fileLen = readlink("/proc/self/exe", fileBuffer.data(), fileBuffer.size() - 1);
    
    std::filesystem::path executablePath;
    if (fileLen != -1) {
        fileBuffer.resize(fileLen);
        executablePath = std::filesystem::path(fileBuffer);
    }
    
    return executablePath.parent_path();
}

// StreamBuffer implementation
StreamBuffer::StreamBuffer(std::shared_ptr<spdlog::logger> logger, LogLevel level)
    : logger(std::move(logger)), level(level) {}

StreamBuffer::int_type StreamBuffer::overflow(int_type ch) {
    if (ch != traits_type::eof()) {
        if (ch == '\n') {
            // Log the current buffer
            switch (level) {
                case LogLevel::trace: logger->trace(buffer); break;
                case LogLevel::debug: logger->debug(buffer); break;
                case LogLevel::info: logger->info(buffer); break;
                case LogLevel::warn: logger->warn(buffer); break;
                case LogLevel::error: logger->error(buffer); break;
                case LogLevel::critical: logger->critical(buffer); break;
                default: logger->info(buffer);
            }
            buffer.clear();
        } else {
            buffer.push_back(static_cast<char>(ch));
        }
    }
    return ch;
}

int StreamBuffer::sync() {
    if (!buffer.empty()) {
        // Log any remaining content
        switch (level) {
            case LogLevel::trace: logger->trace(buffer); break;
            case LogLevel::debug: logger->debug(buffer); break;
            case LogLevel::info: logger->info(buffer); break;
            case LogLevel::warn: logger->warn(buffer); break;
            case LogLevel::error: logger->error(buffer); break;
            case LogLevel::critical: logger->critical(buffer); break;
            default: logger->info(buffer);
        }
        buffer.clear();
    }
    return 0;
}

// GTK log handler implementation
void handleGtkLog(const gchar* logDomain, GLogLevelFlags level, const gchar* message, gpointer userData) {
    auto logger = static_cast<Logger*>(userData);
    if (!logger) return;
    
    std::string domain = logDomain ? logDomain : "GTK";
    std::string formattedMsg = "[" + domain + "] " + message;
    
    switch (level & G_LOG_LEVEL_MASK) {
        case G_LOG_LEVEL_ERROR:
            logger->error(formattedMsg);
            break;
        case G_LOG_LEVEL_CRITICAL:
            logger->critical(formattedMsg);
            break;
        case G_LOG_LEVEL_WARNING:
            logger->warn(formattedMsg);
            break;
        case G_LOG_LEVEL_MESSAGE:
        case G_LOG_LEVEL_INFO:
            logger->info(formattedMsg);
            break;
        case G_LOG_LEVEL_DEBUG:
            logger->debug(formattedMsg);
            break;
        default:
            logger->trace(formattedMsg);
            break;
    }
}

} // namespace rtkdata