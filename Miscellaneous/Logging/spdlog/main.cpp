#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

int main() 
{
    std::cout << "*****************************************************\n";

    //********** Log level **********
    //  - default logger insert of spdlog is configured to only show INFO messages
    //    and messages of higher severity, i.e. of a higher log level
    spdlog::default_logger()->set_level(spdlog::level::trace);

    // Shorthand versions (the one that should be used)
    spdlog::trace("TRACE"); // LogLevel: TRACE
    spdlog::debug("DEBUG"); // LogLevel: DEBUG
    spdlog::info("INFO"); // LogLevel: INFO
    spdlog::warn("WARN"); // LogLevel: WARN

    // Longer versions of function calls
    // - calling functions by using 'spdlog::default_logger()' object
    spdlog::default_logger()->error("ERROR"); // LogLevel: ERROR
    spdlog::default_logger()->log(spdlog::level::critical, "CRITICAL"); // LogLevel: CRITICAL

    std::cout << "-------------------------------------------------------\n";
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    //********** Custom logger and sinks **********
    //  - custom logger will be named "myLogger"
    std::shared_ptr<spdlog::logger> myLogger = std::make_shared<spdlog::logger>("mainLogger");

    //* Set targets to which logger will print logs (i.e. set sinks)
    // Setting stdout sink safe for multithreading
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // Setting basic file sinks safe for multithreading
    auto errorLogFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("../Files/error.log");
    errorLogFileSink->set_level(spdlog::level::err); // Set level for the sink

    auto debugLogFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("../Files/debug.log");
    debugLogFileSink->set_level(spdlog::level::debug); // Set level for the sink

    // Push created sinks to the 'myLogger' sinks
    myLogger->sinks().push_back(consoleSink);
    myLogger->sinks().push_back(errorLogFileSink);
    myLogger->sinks().push_back(debugLogFileSink);

    // Calling functions by using custom logger object 
    myLogger->set_level(spdlog::level::trace);
    myLogger->trace("TRACE");
    myLogger->log(spdlog::level::debug, "DEBUG");
    myLogger->log(spdlog::level::info, "INFO");
    myLogger->log(spdlog::level::warn, "WARN");
    myLogger->log(spdlog::level::err, "ERROR");
    myLogger->log(spdlog::level::critical, "CRITICAL");

    // Sink is not able to push to target levels lower than the one set for logger
    //  - in this case, even though 'debugLogFileSink' is set to 'debug'
    //    logs are saved from the 'warn' level
    myLogger->set_level(spdlog::level::warn);
    myLogger->log(spdlog::level::trace, "TRACE");
    myLogger->log(spdlog::level::debug, "DEBUG");
    myLogger->log(spdlog::level::info, "INFO");
    myLogger->log(spdlog::level::warn, "WARN");
    myLogger->log(spdlog::level::err, "ERROR");
    myLogger->log(spdlog::level::critical, "CRITICAL");

    std::cout << "-------------------------------------------------------\n";
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    //********** Custom formatting **********
    myLogger->set_level(spdlog::level::trace);
    myLogger->set_pattern("%d.%m.%Y %T: [%^%L%$] [%n] %v");

    myLogger->log(spdlog::level::trace, "TRACE");
    myLogger->log(spdlog::level::debug, "DEBUG");
    myLogger->log(spdlog::level::info, "INFO");
    myLogger->log(spdlog::level::warn, "WARN");
    myLogger->log(spdlog::level::err, "ERROR");
    myLogger->log(spdlog::level::critical, "CRITICAL");

    std::cout << "-------------------------------------------------------\n";
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    //********** Register logger **********
    // Set 'myLogger' as default
    spdlog::set_default_logger(myLogger);
    spdlog::log(spdlog::level::trace, "TRACE");
    spdlog::log(spdlog::level::debug, "DEBUG");
    spdlog::log(spdlog::level::info, "INFO");
    spdlog::log(spdlog::level::warn, "WARN");
    spdlog::log(spdlog::level::err, "ERROR");
    spdlog::log(spdlog::level::critical, "CRITICAL");

    // Register dbgLogger
    std::shared_ptr<spdlog::logger> dbgLogger = std::make_shared<spdlog::logger>("debugLogger");
    dbgLogger->sinks().push_back(consoleSink);
    dbgLogger->set_level(spdlog::level::debug);
    dbgLogger->set_pattern("%d.%m.%Y %T: [%^%L%$] [%n] %v");
    spdlog::register_logger(dbgLogger);

    spdlog::get("debugLogger")->log(spdlog::level::info, "INFO from debugLogger");
    spdlog::get("debugLogger")->warn("WARN from debugLogger");

    std::cout << "*****************************************************\n";
    return 0;
}
