#include "Database.h"
#include "Application.h"

#include <gio/gio.h>
#include <exception>
#include <iostream>
#include <sstream>

using namespace rtkplanning;

namespace fs = std::filesystem;

Database& Database::getInstance()
{
    static Database instance;
    return instance;
}

Database::Database()
{
    fs::path dbDirPath = getDatabasePath();
    fs::create_directories(dbDirPath);

    // TODO: test if someone can delete the file after this constructor gets called
    // Beware its a lazy loading, so maybe call getInstance in main before testing
    fs::path dbPath = fs::path(dbDirPath / "dcm.db");
    if (sqlite3_open(dbPath.c_str(), &db))
    {
        sqlite3_close(db);
        throw SQLException("Cannot open database");
    }

    createTables();
}

Database::~Database()
{
    sqlite3_close(db);
}

void Database::createTables()
{
    GError *error;
    GBytes *data;
    gsize size;
    gconstpointer data_ptr;
    GResourceLookupFlags flags;
    
    data = g_resources_lookup_data ("/com/ronna-medical/rtkplanning/db/schema.sql", flags, &error);
    data_ptr = g_bytes_get_data (data, &size);
    
    // TODO: zasto uopce kreirati string, kada sam u sqlite3_exec mogao proslijediti cont char
    std::string schema_str ((const char *)data_ptr, size);
    g_bytes_unref (data);

    int rc;
    char *errMsg;
    rc = sqlite3_exec(db, schema_str.c_str(), nullptr, nullptr, &errMsg);
    if(rc != SQLITE_OK)
    {
        std::cerr << "Database error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

std::shared_ptr<Statement> Database::createStatement(const std::string& query)
{
    return std::make_shared<Statement>(db, query);
}

long long Database::getLastInsertedRowID()
{
    return (long long) sqlite3_last_insert_rowid(db);
}

std::filesystem::path Database::getDatabasePath()
{
    auto appStoragePath = Application::getStoragePath();

    return std::filesystem::path(appStoragePath / fs::path("dcm"));
}