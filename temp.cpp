    std::string logs_dir_path = "../Logs";
    std::string file_name = "rtkplanning_log_" + time_string.str();
    std::string file_dir_path = logs_dir_path + "/" + file_name;
    std::string file_path = file_dir_path + "/" + file_name;
    std::filesystem::create_directories(std::filesystem::path(logs_dir_path));
    std::filesystem::create_directory(std::filesystem::path(file_dir_path));

SPDLOG_LOGGER_TRACE(some_logger, "trace message");
SPDLOG_LOGGER_DEBUG(some_logger, "debug message");
SPDLOG_LOGGER_INFO(some_logger, "info message");
SPDLOG_LOGGER_WARN(some_logger, "warn message");
SPDLOG_LOGGER_ERROR(some_logger, "error message");
SPDLOG_LOGGER_CRITICAL(some_logger, "critical message");

    //* Set logger sinks for writing to files
    // Define configuration for files rotation
    std::size_t mb = 1024 * 1024;
    std::size_t max_file_size = 10 * mb; // Rotate file every 10 MB
    std::size_t max_files_count = 5; // Create a maximum of 5 files

    // Set sink for standard logs
    auto rot_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_path, max_file_size, max_files_count, false);
    rot_file_sink->set_level(spdlog::level::trace);
    rot_file_sink->set_pattern("[%Y-%m-%d %T] [%n] [%s:%# %!] [%^%l%$] %v");
    logger_planning->sinks().push_back(rot_file_sink);
    logger_common_temp->sinks().push_back(rot_file_sink);
    logger_communication_temp->sinks().push_back(rot_file_sink);

    // Set sink for snapshot logs
    auto rot_file_sink_snapshot = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_path, max_file_size, max_files_count, false);
    rot_file_sink_snapshot->set_level(spdlog::level::debug);
    rot_file_sink_snapshot->set_pattern("[%Y-%m-%d %T] [%n] [%s:%# %!] [%^%l%$] %v");
    logger_snapshot_temp->sinks().push_back(rot_file_sink_snapshot);