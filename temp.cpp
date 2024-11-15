#pragma once

#include <adwaita.h>
#include <filesystem>
#include <memory>
#include <string>

#include "PlanContext.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace rtkplanning
{

/**
 * @brief Gtk application wrapper
 * 
 */
class Application
{
public:
    /**
     * @brief Constructs a new Application object
     * 
     * @param app_id 
     * @param flags 
     */
    Application(const std::string& app_id, const GApplicationFlags& flags = G_APPLICATION_FLAGS_NONE);
    
    /**
     * @brief Destroys the Application object
     * 
     */
    ~Application();

    /**
     * @brief Runs the application
     * 
     * @param argc Number of arguments
     * @param argv Array of arguments
     * @return int Exit status from g_application_run
     */
    int Run (int argc, char* argv[]);

private:
    void OnActivate();
    /// @brief Set default application storage paths
    void SetApplicationStoragePaths();
    void InitializeLoggers() const;

    AdwApplication* m_adwApp;
    std::shared_ptr<rtkplanning::PlanContext> m_mainView;
    static std::filesystem::path _app_storage_path;
    static std::filesystem::path _local_dicoms_dir_path;
    static std::filesystem::path _database_dir_path;
};

inline std::filesystem::path _app_storage_path{""};
inline std::filesystem::path _local_dicoms_dir_path{""};
inline std::filesystem::path _database_dir_path{""};

}
