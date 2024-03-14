#include "../include/database.h"
#include<string>
#include <vector>
#include <iostream>
#include <iomanip>

int Database::rows = 0;
bool Database::open(std::filesystem::path dbPath) {
	
	if (sqlite3_open(dbPath.string().c_str(), &db) == SQLITE_OK) {

		if (!createTables()) {
			return false;
		}

		std::string pragmaQuery = { "PRAGMA foreign_keys = ON;" };
		executeQuery(pragmaQuery);

		return true;
	}
	else {
		std::string_view err = { "Failed to open database" };
		setError(err);
		return false;
	}
}

bool Database::createTables() {

	const char* sql = "CREATE TABLE IF NOT EXISTS Employee ("
		"id INTEGER PRIMARY KEY,"
		"firstname VARCHAR,"
		"lastname VARCHAR,"
		"dob DATE,"
		"mobile VARCHAR,"
		"email VARCHAR,"
		"address VARCHAR,"
		"gender VARCHAR CHECK (gender IN ('Male', 'Female', 'Other')),"
		"doj DATE,"
		"w_location VARCHAR,"
		"manager_id INTEGER,"
		"department_id INTEGER,"
		"FOREIGN KEY (department_id) REFERENCES Department(id),"
		"FOREIGN KEY (manager_id) REFERENCES Employee(id));";

	if (!executeQuery(sql))
	{
		return false;
	}

	const char* sql2 = "CREATE TABLE IF NOT EXISTS Department ("
		"id INTEGER PRIMARY KEY,"
		"name VARCHAR,"
		"manager_id INTEGER,"
		"description VARCHAR,"
		"FOREIGN KEY (manager_id) REFERENCES Employee(id) )";


	if (!executeQuery(sql2))
	{
		return false;
	}



	const char* sql3 = "CREATE TABLE IF NOT EXISTS Engineer ("
		"id INTEGER PRIMARY KEY,"
		"programming_language VARCHAR,"
		"specialization VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(id) ON DELETE CASCADE )";

	if (!executeQuery(sql3))
	{
		return false;
	}


	const char* sql4 = "CREATE TABLE IF NOT EXISTS Manager ("
		"id INTEGER PRIMARY KEY,"
		"management_experience INTEGER,"
		"project_title VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(id) ON DELETE CASCADE)";


	if (!executeQuery(sql4))
	{
		return false;
	}


	const char* sql5 = "CREATE TABLE IF NOT EXISTS Salary ("
		"id INTEGER PRIMARY KEY,"
		"amount REAL,"
		"base_salary REAL,"
		"bonus REAL,"
		"FOREIGN KEY (id) REFERENCES Employee(id) ON DELETE CASCADE)";

	if (!executeQuery(sql5))
	{
		return false;
	}


	return true;
}

void Database::close() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

bool Database::executeQuery(const std::string& query) {
	char* errMsg = nullptr;


	int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::string_view err = { errMsg };
		setError(err);
		//sqlite3_free(errMsg);
		return false;
	}

	return true;
}

std::string_view Database::getError() const {
	return Error;
}

bool Database::executeQueryCallback(const std::string& query) {
	char* errMsg = nullptr;
	rows = 0;
	int rc = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
	std::cout << rows << " rows returned \n\n";

	if (rc != SQLITE_OK) {
		std::string_view err = { errMsg };
		setError(err);
		//sqlite3_free(errMsg);
		return false;
	}
	return true;
}

int Database::callback(void* data, int argc, char** argv, char** azColName) {
	++rows;
	int colWidth = 22;
	int length;
	std::cout << "----------------------------------------" << "\n";
	for (int i = 0; i < argc; ++i) {
		length = strlen(azColName[i]) - 2;
		std::cout << " " << azColName[i] << std::setw(colWidth - length) << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	std::cout << "----------------------------------------" << "\n";
	return 0;
}


bool Database::executeQueryRows(const std::string& query) {
	char* errMsg = nullptr;
	rows = 0;
	int rc = sqlite3_exec(db, query.c_str(), callbackRows, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::string_view err = { errMsg };
		setError(err);
		//sqlite3_free(errMsg);
		return false;
	}
	return true;
}

int Database::callbackRows(void* data, int argc, char** argv, char** azColName) {
	++rows;
	return 0;
}


int Database::getRow() {
	return rows;
}

void Database::setError(std::string_view& errorMessage) {
	Error = errorMessage;
}


void Database::createTableQuery() {

	std::string tableName;
	std::cout << "Enter table name: ";
	std::cin >> tableName;

	std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
	std::vector<std::string> columns;

	char choice;
	do {
		std::string columnName, columnType, constraints;
		std::cout << "Enter column name: ";
		std::cin >> columnName;
		std::cout << "Enter column type: ";
		std::cin >> columnType;

		std::cout << "Enter column constraints : ";
		std::cin.ignore();
		std::getline(std::cin, constraints);

		columns.push_back(columnName + " " + columnType + " " + constraints);

		std::cout << "Add another column? (y/n): ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	for (int i = 0; i < columns.size(); ++i) {
		sql += columns[i];
		if (i < columns.size() - 1) {
			sql += ",";
		}
	}
	sql += ");";

	executeQuery(sql);

	std::cout << sql << "\n\n";
}

void Database::showTables() {

	std::string showQuery = " SELECT name FROM sqlite_schema ;";
	if (!executeQueryCallback(showQuery))
		std::cout << getError() << "\n\n";

}

void Database::deleteTableQuery() {

	int input;
	std::cout << "Enter 1 to Drop table or Enter 2 to Delete data within the table:";
	std::cin >> input;

	std::string deleteQuery;
	std::string tableName;

	switch (input) {
	case 1:
		std::cout << "Enter Table Name to Drop: ";
		std::cin >> tableName;

		deleteQuery = "DROP TABLE " + tableName + ";";
		std::cout << deleteQuery << '\n\n';

		if (executeQuery(deleteQuery))
			std::cout << "Table Droped Succesfully ! \n\n";
		else
			std::cout << Database::getInstance().getError() << "\n\n";

		break;

	case 2:
		std::cout << "Enter Table Name to Delete: ";
		std::cin >> tableName;
		deleteQuery = "DELETE FROM " + tableName + ";";
		std::cout << deleteQuery << '\n\n';

		if (executeQuery(deleteQuery))
			std::cout << "Table Deleted Succesfully ! \n\n";
		else
			std::cout << Database::getInstance().getError() << "\n\n";

		break;

	default:
		std::cout << "Wrong Input..!\n\n";
		break;
	}

}

void Database::userSqlQuery()
{

	std::string sqlQuery;

	std::cout << "Enter sql query : ";
	std::cin.ignore();
	std::getline(std::cin, sqlQuery);
	
	for (int i = 0; i < sqlQuery.size(); i++) {
		sqlQuery[i] = std::tolower(sqlQuery[i]);
	}

	int pos = sqlQuery.find("select");


	if (pos == 0) {
		if (executeQueryCallback(sqlQuery))
			std::cout << "SQL Query Completed Successfully ! \n\n";
		else
			std::cout << getError() << "\n";
	}
	else{
		if (executeQuery(sqlQuery))
			std::cout << "SQL Query Completed Successfully ! \n\n";
		else
			std::cout << getError() << "\n";
	}

}

