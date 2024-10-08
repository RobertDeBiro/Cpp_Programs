#include "Statement.h"
#include "Database.h"
#include "SQLException.h"
#include <iostream>

using namespace rtkplanning;

Statement::Statement(sqlite3* db, const std::string& query) :
    db(db),
    query(query)
{
}

Statement::~Statement()
{
    sqlite3_finalize(stmt);
}

void Statement::prepare()
{
    int result = sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, NULL);
    if(result != SQLITE_OK)
    {
        throw SQLException("Statement prepare failed with code: " + std::to_string(result));
    }

    prepared = true;
}

void Statement::bind(int pos, const std::string& value)
{
    if(!prepared)
    {
        throw SQLException("Statement not prepared");
    }

    // The leftmost SQL parameter in bind function has an index of 1, but the leftmost parameter in
    // this function that is being exposed to the user will have an index of 0; therefore a (pos + 1)
    if(SQLITE_OK != sqlite3_bind_text(stmt, pos + 1, value.c_str(), value.length(), SQLITE_TRANSIENT))
    {
        throw SQLException("Statement bind failed");
    }
}

void Statement::bind(int pos, const std::optional<std::string>& value)
{
    if(!value) return;

    if(!prepared)
    {
        throw SQLException("Statement not prepared");
    }

    // The leftmost SQL parameter in bind function has an index of 1, but the leftmost parameter in
    // this function that is being exposed to the user will have an index of 0; therefore a (pos + 1)
    if(SQLITE_OK != sqlite3_bind_text(stmt, pos + 1, value.value().c_str(), value.value().length(), SQLITE_TRANSIENT))
    {
        throw SQLException("Statement bind failed");
    }
}

void Statement::bind(int pos, long long value)
{
    if(!prepared)
    {
        throw SQLException("Statement not prepared");
    }

    // The leftmost SQL parameter in bind function has an index of 1, but the leftmost parameter in
    // this function that is being exposed to the user will have an index of 0; therefore a (pos + 1)
    if(SQLITE_OK != sqlite3_bind_int64(stmt, pos + 1, value))
    {
        throw SQLException("Statement bind failed");
    }
}

bool Statement::step()
{
    if(!prepared)
    {
        throw SQLException("Statement not prepared");
    }

    int rc = sqlite3_step(stmt);

    if(rc == SQLITE_ROW)
    {
        return true;
    }
    else if(rc == SQLITE_DONE)
    {
        return false;
    }
    else
    {
        throw SQLException("Statement step failed");
    }
}

std::optional<std::string> Statement::getText(int pos)
{
    auto text = sqlite3_column_text(stmt, pos);

    return text == NULL ? 
        std::nullopt : 
        std::make_optional<std::string>((const char*)text);
}

long long Statement::getInt64(int pos)
{
    return (long long) sqlite3_column_int64(stmt, pos);
}
