#include "../include/database.h"
#include<string>
#include <vector>

bool Database::open() {
    if (sqlite3_open(dbName.c_str(), &db) == SQLITE_OK) {
        return true;
    }
    else {
        setError("Failed to open database");
        return false;
    }
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::executeQuery(const std::string& query) {
    char* errMsg = nullptr;


    int rc = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        setError(errMsg);
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

std::string Database::getError() const {
    return Error;
}

int Database::callback(void* data, int argc, char** argv, char** azColName) {
    auto* results = static_cast<std::vector<std::vector<std::string>>*>(data);
    std::vector<std::string> row;

    for (int i = 0; i < argc; ++i) {
        if (argv[i]) {
            row.push_back(argv[i]);
        }
        else {
            row.push_back("NULL");
        }
    }

    results->push_back(row);
    return 0;
}

void Database::setError(const std::string& errorMessage) {
    Error = errorMessage;
}