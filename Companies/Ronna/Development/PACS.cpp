std::vector<std::thread> ping_threads; // Store threads here

for (int i = 0; i < _pacs_items_shared.size(); i++)
{
    // Create 'RtkDropdownObject' for each pacs_item (for every pacs server saved in config file)
    RtkDropdownObject* rtk_obj = create_rtkdropdown_object(i);

    // Assign pacs_item address to 'RtkDropdownObject::t_obj' parameter
    rtk_obj->t_obj = _pacs_items_shared[i].get();

    // Append 'RtkDropdownObject' to 'GListStore' Model object
    g_list_store_append(_pacs_list_store, rtk_obj);

    // Ping saved PACS servers using multiple threads
    ping_threads.push_back(std::thread(
        std::bind(&SettingsController::IsPacsAccessible, this, _pacs_items_shared[i]->called_ae_title, _pacs_items_shared[i]->ip_address)));
    ping_threads.back().detach();
}

void SettingsController::IsPacsAccessible(const std::string& ae_title, const std::string& ip_address)
{
	std::string command = "ping -c 1 " + ip_address + " > /dev/null 2>&1";
    int returnCode = std::system(command.c_str());

	if (returnCode == 0) // ping succeeded
		SPDLOG_LOGGER_TRACE(_logger_planning, "PACS Server [AETitle = {}; IP Address = {}] accessible.", ae_title, ip_address);
	else
		SPDLOG_LOGGER_TRACE(_logger_planning, "PACS Server [AETitle = {}; IP Address = {}] not accessible.", ae_title, ip_address);
}