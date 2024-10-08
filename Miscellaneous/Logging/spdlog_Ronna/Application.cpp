#include <string>
#include <unistd.h>
#include <limits.h>

#include "Application.h"

using namespace rtkplanning;

Application::Application(const std::string& app_id, const GApplicationFlags& flags)
{
	m_adwApp = adw_application_new(app_id.c_str(), flags);

	g_signal_connect(m_adwApp, "activate", G_CALLBACK(+[](GtkApplication* const application, gpointer data) {
		static_cast<Application*>(data)->onActivate();
	}), this);

    InitializeLoggers();
}

Application::~Application()
{
    g_object_unref(m_adwApp);
}

int Application::run(int argc, char* argv[])
{
    SPDLOG_LOGGER_TRACE(spdlog::get("rtkplanning"), "Starting application.");
    return g_application_run(G_APPLICATION(m_adwApp), argc, argv);
}

void Application::onActivate()
{
    SPDLOG_LOGGER_TRACE(spdlog::get("rtkplanning"), "Activating application.");

	adw_style_manager_set_color_scheme(adw_style_manager_get_default(), ADW_COLOR_SCHEME_DEFAULT);
	m_mainView = std::make_shared<PlanContext>();

	gtk_application_add_window(GTK_APPLICATION(m_adwApp), GTK_WINDOW(m_mainView->getGobj()));
	m_mainView->show();
}

std::filesystem::path Application::getStoragePath()
{
    const char *homeDir = getenv("HOME");
    if(homeDir == NULL)
    {
        throw "HOME environment variable needs to be set to home path";
    }

    return std::filesystem::path(homeDir / std::filesystem::path(".ronna-medical/rtkplanning"));
}

void Application::InitializeLoggers()
{
    //* Lambda object for generating and managing directories in which logs will be saved
    auto manage_dirs =
        [](std::string logs_dir, std::string file_dir)
        {
            std::filesystem::path logs_dir_path(logs_dir);
            std::filesystem::path file_dir_path(file_dir);

            if (!std::filesystem::exists(logs_dir_path.parent_path()))
                std::filesystem::create_directories(logs_dir_path.parent_path());
            std::filesystem::create_directory(logs_dir_path);

            std::filesystem::create_directory(file_dir_path);

            // Restrict the size of main directories to 10 child directories
            std::vector<std::filesystem::directory_entry> log_dirs;
            for (const auto& entry : std::filesystem::directory_iterator(logs_dir_path))
            {
                if (entry.is_directory())
                    log_dirs.push_back(entry);
            }

            // Sort directories by creation time
            std::sort(log_dirs.begin(), log_dirs.end(), [](const auto& a, const auto& b){
                return std::filesystem::last_write_time(a) < std::filesystem::last_write_time(b);
            });

            // If more than 10 directories exist, delete the oldest ones
            while (log_dirs.size() > 10)
            {
                std::filesystem::remove_all(log_dirs.front().path());
                log_dirs.erase(log_dirs.begin());
            }
        };

    //* Get current time in string type that will be used for logs dirs and files creation
    using Clock = std::chrono::system_clock;
    std::chrono::time_point<Clock> time_clock = Clock::now();

    // Convert the 'time_point' object a 'time_t' object,
    // which is a type suitable for representing the system time as a simple integer
    std::time_t time_t = Clock::to_time_t(time_clock);

    // Convert the 'time_t' object into a 'std::tm' structure representing the local time
    // as years, months, days, hours...
    std::tm* time_tm = std::localtime(&time_t);

    // Convert 'std::tm' structure into string with particular format
    std::stringstream time_string;
    time_string << std::put_time(time_tm, "%d_%m_%Y-%H_%M_%S");

    //* Create and configure management for directories in which logs will be saved
    // Obtain path to executable file
    std::filesystem::path exec_file_path{};
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        exec_file_path = std::filesystem::path(buffer);
    }
    std::string build_dir_path = exec_file_path.parent_path().parent_path().string();

    // Manage "Standard" logs directories and files
    std::string logs_dir_std_rel = "/Logs/Standard";
    std::string logs_dir_std = build_dir_path + logs_dir_std_rel;
    std::string file_name_std = "rtkplanning_std_log-" + time_string.str();
    std::string file_dir_std = logs_dir_std + "/" + file_name_std;
    manage_dirs(logs_dir_std, file_dir_std);

    // Manage "Database" logs directories and files
    std::string logs_dir_db_rel = "/Logs/Database";
    std::string logs_dir_db = build_dir_path + logs_dir_db_rel;
    std::string file_name_db = "rtkplanning_db_log-" + time_string.str();
    std::string file_dir_db = logs_dir_db + "/" + file_name_db;
    manage_dirs(logs_dir_db, file_dir_db);

    // Manage "Snapshot" logs directories and files
    std::string logs_dir_snp_rel = "/Logs/Snapshot";
    std::string logs_dir_snp = build_dir_path + logs_dir_snp_rel;
    std::string file_name_snp = "rtkplanning_snp_log-" + time_string.str();
    std::string file_dir_snp = logs_dir_snp + "/" + file_name_snp;
    manage_dirs(logs_dir_snp, file_dir_snp);

    // Manage "DicomDir parsing" logs directories and files
    std::string logs_dir_dcm_rel = "/Logs/DcmDirParse";
    std::string logs_dir_dcm = build_dir_path + logs_dir_dcm_rel;
    std::string file_name_dcm = "rtkplanning_dcm_log-" + time_string.str();
    std::string file_dir_dcm = logs_dir_dcm + "/" + file_name_dcm;
    manage_dirs(logs_dir_dcm, file_dir_dcm);

    //* Initialize loggers for each module
    std::shared_ptr<spdlog::logger> logger_planning = std::make_shared<spdlog::logger>("rtkplanning");
    std::shared_ptr<spdlog::logger> logger_database = std::make_shared<spdlog::logger>("rtkplanning_db");
    std::shared_ptr<spdlog::logger> logger_snapshot = std::make_shared<spdlog::logger>("rtkplanning_snapshot");
    std::shared_ptr<spdlog::logger> logger_dcmdir = std::make_shared<spdlog::logger>("rtkplanning_dcmdirparse");
    std::shared_ptr<spdlog::logger> logger_common = std::make_shared<spdlog::logger>("rtkcommon");
    std::shared_ptr<spdlog::logger> logger_communication = std::make_shared<spdlog::logger>("rtkcommunication");

    logger_planning->set_level(spdlog::level::trace);
    logger_database->set_level(spdlog::level::trace);
    logger_snapshot->set_level(spdlog::level::debug);
    logger_dcmdir->set_level(spdlog::level::debug);
    logger_common->set_level(spdlog::level::trace);
    logger_communication->set_level(spdlog::level::trace);

    //* Set logger sink for writing to console
#ifdef DEBUG
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(spdlog::level::trace);
    consoleSink->set_pattern("[%T] %-16n %-20!s [%^%L%$] %v");
    logger_planning->sinks().push_back(consoleSink);
    logger_database->sinks().push_back(consoleSink);
    logger_common->sinks().push_back(consoleSink);
    logger_communication->sinks().push_back(consoleSink);
#endif

    //* Set logger sinks for writing to files
    // Define configuration for files rotation
    std::size_t mb = 1024 * 1024;
    std::size_t max_file_size = 10 * mb; // Rotate file every 10 MB
    std::size_t max_files_count = 5; // Create a maximum of 5 files

    // Set sink for standard logs
    std::string file_std = file_dir_std + "/" + file_name_std + ".log";
    auto rot_file_sink_std = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_std, max_file_size, max_files_count, false);
    rot_file_sink_std->set_level(spdlog::level::trace);
    rot_file_sink_std->set_pattern("[%Y-%m-%d %T] [%n] [%s:%# %!] [%t] [%^%l%$] %v");
    logger_planning->sinks().push_back(rot_file_sink_std);
    logger_common->sinks().push_back(rot_file_sink_std);
    logger_communication->sinks().push_back(rot_file_sink_std);

    // Set sink for database logs
    std::string file_db = file_dir_db + "/" + file_name_db + ".log";
    auto rot_file_sink_db = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_db, max_file_size, max_files_count, false);
    rot_file_sink_db->set_level(spdlog::level::trace);
    rot_file_sink_db->set_pattern("[%Y-%m-%d %T] [%n] [%s:%# %!] [%t] [%^%l%$] %v");
    logger_database->sinks().push_back(rot_file_sink_db);

    // Set sink for snapshot logs
    std::string file_snp = file_dir_snp + "/" + file_name_snp + ".log";
    auto rot_file_sink_snp = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_snp, max_file_size, max_files_count, false);
    rot_file_sink_snp->set_level(spdlog::level::debug);
    rot_file_sink_snp->set_pattern("[%Y-%m-%d %T] [%n] [%s:%# %!] [%t] [%^%l%$] %v");
    logger_snapshot->sinks().push_back(rot_file_sink_snp);

    // Set sink for dicomdir parse logs
    std::string file_dcm = file_dir_dcm + "/" + file_name_dcm + ".log";
    auto rot_file_sink_dcm = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_dcm, max_file_size, max_files_count, false);
    rot_file_sink_dcm->set_level(spdlog::level::debug);
    rot_file_sink_dcm->set_pattern("[%Y-%m-%d %T] [%n] [%s:%# %!] [%t] [%^%l%$] %v");
    logger_dcmdir->sinks().push_back(rot_file_sink_dcm);

    //* Register loggers
    spdlog::register_logger(logger_planning);
    spdlog::register_logger(logger_database);
    spdlog::register_logger(logger_snapshot);
    spdlog::register_logger(logger_dcmdir);
    spdlog::register_logger(logger_common);
    spdlog::register_logger(logger_communication);

    spdlog::flush_every(std::chrono::seconds(1));
}
