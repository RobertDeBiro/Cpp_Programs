#pragma once

#include "SQLException.h"
#include <optional>
#include <sqlite3.h>
#include <string>

namespace rtkplanning
{

class Database;
class SQLException;

/**
 * @brief Class representing an SQL statement.
 * 
 */
class Statement
{
public:

    /**
     * @brief Construct a new Statement object
     * 
     * @param db pointer to sqlite3 database object
     * @param query string representing a database query
     */
    Statement(sqlite3* db, const std::string& query);

    /**
     * @brief Destroy the Statement object
     * 
     */
    ~Statement();

public:
    // TODO: void beginTransaction();
    // TODO: void endTransaction();

    /**
     * @brief Prepare a statement.
     * 
     */
    void prepare();

    /**
     * @brief Bind a string value to a prepared statement.
     * Throws SQLException if statement is not prepared.
     * 
     * @param pos index of the SQL parameter to be set
     * @param value string value to be bound
     */
    void bind(int pos, const std::string& value);

    /**
     * @brief Bind an optional string value to a prepared statement. If optional contains a null value, do nothing.
     * Throws SQLException if statement is not prepared.
     * 
     * @param pos index of the SQL parameter to be set
     * @param value optional string value to be bound
     */
    void bind(int pos, const std::optional<std::string>& value);

    /**
     * @brief Bind a 64-bit integer value to a prepared statement.
     * Throws SQLException if statement is not prepared.
     * 
     * @param pos index of the SQL parameter to be set
     * @param value 64-bit integer value to be bound
     */
    void bind(int pos, long long value);

    /**
     * @brief Evaluate the statement, which means read the result of the SQL query. Method reads a row by row.
     * When no more rows to be read, method returns false.
     * 
     * Throws SQLException if statement is not prepared or if SQL statement is not evaluated properly.
     * 
     * @return true when more rows can be read
     * @return false when no more rows can be read
     */
    bool step();

    /**
     * @brief Get the text from the last read row.
     * 
     * @param pos index of the column from where the text is being read
     * @return std::optional<std::string> text being read wrapped in optional in case it's NULL
     */
    std::optional<std::string> getText(int pos);

    /**
     * @brief Get the 64-bit int from the last read row.
     * 
     * @param pos index of the column where the 64-bit int is being read
     * @return long long 64-bit int being read
     */
    long long getInt64(int pos);

private:
    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::string query;
    bool prepared;
};

}
