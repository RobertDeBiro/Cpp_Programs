#include <iostream>
#include <sqlite3.h> // SQLite3 header

int main()
{
    std::cout << "*****************************************************\n";

    sqlite3* db;

    //* Open database (create if not exists)
    int rc = sqlite3_open("Database/Sqlite3_Demo_data.sqlite", &db);

    if (rc)
    {
        sqlite3_close(db);
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Opened database successfully" << std::endl;
    }

    //* Create SQL statement to create a table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS COMPANY("
                                 "ID INT PRIMARY KEY     NOT NULL,"
                                 "NAME           TEXT    NOT NULL,"
                                 "AGE            INT     NOT NULL,"
                                 "ADDRESS        CHAR(50),"
                                 "SALARY         REAL );";

    //* Execute SQL statement
    //  - 'sqlite3_exec' is used if we already have fully prepared query
    char* errMsg = 0;
    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Table created successfully" << std::endl;
    }

    //* Insert data into the table
    const char* insertSQL = "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) "
                                "VALUES (1, 'Paul', 32, 'California', 20000); "
                            "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) "
                                "VALUES (2, 'Allen', 25, 'Texas', 15000); "
                            "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) "
                                "VALUES (3, 'Teddy', 23, 'Norway', 20000.00); "
                            "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) "
                                "VALUES (4, 'Mark', 25, 'Richmond', 65000.00);";

    rc = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Records inserted successfully" << std::endl;
    }

    //* Select data from the table
    const char* selectSQL = "SELECT * FROM COMPANY";

    // 'sqlite3_stmt' - data type that should contain prepared statement, i.e. statement ready for execution
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    //* Iterate over the result set
    std::cout << "Selected data from the table:" << std::endl;
    // 'sqlite3_step'
    //  - executes prepared statement
    //  - together with macro 'SQLITE_ROW' and 'SQLITE_DONE' it can be used to iterate until it reaches a stopping point
    //    - equal to 'SQLITE_ROW' = another row to iterate
    //    - equal to 'SQLITE_DONE' = no rows to iterate
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int age = sqlite3_column_int(stmt, 2);
        const unsigned char* address = sqlite3_column_text(stmt, 3);
        double salary = sqlite3_column_double(stmt, 4);

        std::cout << "ID = " << id << ", Name = " << name << ", Age = " << age
                  << ", Address = " << address << ", Salary = " << salary << std::endl;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////

    rc = sqlite3_prepare_v2(db, "SELECT NAME FROM COMPANY", -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::cout << "Selected data from the table:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char* name = sqlite3_column_text(stmt, 0);
        std::cout << "Name = " << name << std::endl;
    }

    //* Finalize the statement
    //  - release all resources associated with a prepared statement
    sqlite3_finalize(stmt);

    //* Close database
    sqlite3_close(db);

    std::cout << "*****************************************************\n";
    return 0;
}
