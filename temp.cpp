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


PlanContext::PlanContext() :
    rtkcommon::Controller{"/com/ronna-medical/rtkplanning/ui/PlanView.ui","planning_window"}
{
    InitializeLoggers();
    SPDLOG_LOGGER_TRACE(logger_planning, "Application started.");

    //* GTK window and boxes that goes throughout whole rtkplanning app
    planning_window = GTK_WINDOW (gtk_builder_get_object(m_builder, "planning_window"));
    horizontal_planning_box = GTK_BOX(gtk_builder_get_object(m_builder, "horizontal_planning_box"));
    vertical_planning_box = GTK_BOX(gtk_builder_get_object(m_builder, "vertical_planning_box"));

	//* System info content
    status_bar_box = GTK_BOX(gtk_builder_get_object(m_builder, "status_bar_box"));
    settings_icon = GTK_IMAGE (gtk_builder_get_object(m_builder, "settings_icon"));
    battery_overlay = GTK_OVERLAY(gtk_builder_get_object(m_builder, "battery_overlay"));
    battery_icon = GTK_IMAGE (gtk_builder_get_object(m_builder, "battery_icon"));
    charging_icon = GTK_IMAGE (gtk_builder_get_object(m_builder, "charging_icon"));
    battery_percentage = GTK_LABEL(gtk_builder_get_object(m_builder, "battery_percentage"));
    wifi_icon = GTK_IMAGE (gtk_builder_get_object(m_builder, "wifi_icon"));
    connection_status_icon = GTK_IMAGE (gtk_builder_get_object(m_builder, "connection_status_icon"));

    settings_button = GTK_BUTTON (gtk_builder_get_object(m_builder, "settings_button"));
    g_signal_connect(settings_button, "clicked", G_CALLBACK (OnSettingsButtonClicked), this);

    // Initialize the system info context variables
    charging_state = false;
    battery_level = 0;
    connection_status = false;
    signal_quality = 0;

    //* Source selector content
    source_selector_box = GTK_BOX(gtk_builder_get_object(m_builder, "source_selector_box"));

    PACS_button = GTK_BUTTON (gtk_builder_get_object(m_builder, "PACS_button"));
    local_button = GTK_BUTTON (gtk_builder_get_object(m_builder, "local_button"));
    USB_button = GTK_BUTTON (gtk_builder_get_object(m_builder, "USB_button"));
    g_signal_connect(PACS_button, "toggled", G_CALLBACK (OnPACSButtonToggled), this);
    g_signal_connect(local_button, "toggled", G_CALLBACK (OnLocalButtonToggled), this);
    g_signal_connect(USB_button, "toggled", G_CALLBACK (OnUSBButtonToggled), this);

    //* State selector content
    state_selector_box = GTK_BOX(gtk_builder_get_object(m_builder,"state_selector_box"));
    plans_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"plans_tab_toggle_button"));
    markers_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"markers_tab_toggle_button"));    
    trajectories_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"trajectories_tab_toggle_button"));    
    sync_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"sync_tab_toggle_button"));

    //* Operation planning boxes
    operation_planning_box = GTK_BOX(gtk_builder_get_object(m_builder, "operation_planning_box"));
    image_viewer_box = GTK_BOX(gtk_builder_get_object(m_builder, "image_viewer_box"));
    state_content_box = GTK_BOX(gtk_builder_get_object(m_builder, "state_content_box"));

    gtk_box_append(image_viewer_box, viewer->getGobj());
    gtk_widget_set_visible(viewer->getGobj(), false);
    // gtk_widget_set_visible(GTK_WIDGET(image_viewer_box), true);

    //* Navigation buttons content
    navigation_buttons_box = GTK_BOX(gtk_builder_get_object(m_builder, "navigation_buttons_box"));
    back_button = GTK_BUTTON(gtk_builder_get_object(m_builder, "back_button"));
    next_button = GTK_BUTTON(gtk_builder_get_object(m_builder, "next_button"));

    //* New/edit/delete buttons content
    new_edit_delete_buttons_box = GTK_BOX(gtk_builder_get_object(m_builder, "new_edit_delete_buttons_box"));
    new_button = GTK_BUTTON(gtk_builder_get_object(m_builder, "new_button"));
    edit_button = GTK_BUTTON(gtk_builder_get_object(m_builder, "edit_button"));
    delete_button = GTK_BUTTON(gtk_builder_get_object(m_builder, "delete_button"));

    //* Report content
    exit_report_button_box = GTK_BOX(gtk_builder_get_object(m_builder, "exit_report_button_box"));
    exit_report_button = GTK_BUTTON(gtk_builder_get_object(m_builder, "exit_report_button"));

    report_state_selector_box = GTK_BOX(gtk_builder_get_object(m_builder,"report_state_selector_box"));
    report_list_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"report_list_tab_toggle_button"));
    g_signal_connect(report_list_tab_toggle_button, "toggled", G_CALLBACK(OnReportListTabButtonToggled), this);
    
    report_markers_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"report_markers_tab_toggle_button"));
    g_signal_connect(report_markers_tab_toggle_button, "toggled", G_CALLBACK(OnReportMarkersTabButtonToggled), this);

    report_trajectories_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"report_trajectories_tab_toggle_button"));
    g_signal_connect(report_trajectories_tab_toggle_button, "toggled", G_CALLBACK(OnReportTrajectoriesTabButtonToggled), this);

    report_preview_tab_toggle_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_builder,"report_preview_tab_toggle_button"));
    g_signal_connect(report_preview_tab_toggle_button, "toggled", G_CALLBACK(OnReportPreviewTabButtonToggled), this);

    //* DatabaseState content
    transfer_button = GTK_BUTTON (gtk_builder_get_object(m_builder, "transfer_button"));
    series_select_popup_window = GTK_WINDOW(gtk_builder_get_object(m_builder, "series_select_popup_window"));

    //* Patient/Series/Studies content
    patient_series_studies_box = GTK_BOX(gtk_builder_get_object(m_builder, "patient_series_studies_box"));
    name_of_series_dropdown = GTK_DROP_DOWN(gtk_builder_get_object(m_builder, "name_of_series_dropdown"));
    patient_name_label = GTK_LABEL(gtk_builder_get_object(m_builder, "patient_name_label"));

    // operation_planning_box is appended here, even though it is not needed yet (hence visibility set to false),
    // in order to properly handle Viewer widget that will be added later to operation_planning_box
    gtk_box_append(vertical_planning_box, GTK_WIDGET(operation_planning_box));
    gtk_widget_set_visible(GTK_WIDGET(operation_planning_box), false);

	viewer = new rtkcommon::Viewer();
	imageViewer = new rtkcommon::ImageViewer();
    dicomIO = itk::GDCMImageIO::New();

    //* Open thread for continuously listening USB ports
    if(UsbManager::Init())
    {
        SPDLOG_LOGGER_TRACE(logger_planning, "Openning thread for continuously listening USB ports!");
        std::thread worker_listen_usb(&UsbManager::StartListening);
        worker_listen_usb.detach();
    }
    else
    {
        SPDLOG_LOGGER_ERROR(logger_planning, "Error: USB device couldn't be initialized!");
        // TODO: Pop up some error message to GUI
        // TODO: Clarify which actions should we maybe take in addition
    }

    //* Configure CSS
    GtkCssProvider *css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_resource(css_provider, "/com/ronna-medical/rtkplanning/styles/style.css");
	gtk_style_context_add_provider_for_display(gtk_widget_get_display(m_gobj), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    //* Enter SearchState
    SetState(SearchState::GetInstance());

    SPDLOG_LOGGER_TRACE(logger_planning, "PlanContext constructed");
}