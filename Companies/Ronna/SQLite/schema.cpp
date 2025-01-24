#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <sstream>

int main() {
    sqlite3* db;
    int rc = sqlite3_open("schema.sqlite", &db);
    if (rc) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::ifstream scriptFile("schema.sql");
    if (!scriptFile.is_open()) {
        std::cerr << "Error opening SQL script file" << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::stringstream buffer;
    buffer << scriptFile.rdbuf();
    std::string scriptContent = buffer.str();

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, scriptContent.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}
