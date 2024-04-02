#include "../include/database.h"


using logs::Log;

int Database::rows = 0;

bool Database::open(std::filesystem::path dbPath) {

	if (sqlite3_open(dbPath.string().c_str(), &db) == SQLITE_OK) {

		if (!createTables()) { 
			return false;
		}

		std::string pragmaQuery = { "PRAGMA foreign_keys = ON;" }; //to turn on foriegn key use
		executeQuery(pragmaQuery);

		return true;
	}
	else {
		std::string err = { "Failed to open database" };
		setError(err);
		Log::getInstance().Error("Failed to open database.");
		return false;
	}
}

bool Database::createTables() {

	const char* EMP = "CREATE TABLE IF NOT EXISTS Employee ("
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

	if (!executeQuery(EMP))
	{
		return false;
	}

	const char* DEPT = "CREATE TABLE IF NOT EXISTS Department ("
		"id INTEGER PRIMARY KEY,"
		"name VARCHAR,"
		"manager_id INTEGER,"
		"description VARCHAR,"
		"FOREIGN KEY (manager_id) REFERENCES Employee(id) )";


	if (!executeQuery(DEPT))
	{
		return false;
	}

	const char* ENG = "CREATE TABLE IF NOT EXISTS Engineer ("
		"id INTEGER PRIMARY KEY,"
		"programming_language VARCHAR,"
		"specialization VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(id) ON DELETE CASCADE )";

	if (!executeQuery(ENG))
	{
		return false;
	}

	const char* MANAGER = "CREATE TABLE IF NOT EXISTS Manager ("
		"id INTEGER PRIMARY KEY,"
		"management_experience INTEGER,"
		"project_title VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(id) ON DELETE CASCADE)";


	if (!executeQuery(MANAGER))
	{
		return false;
	}

	const char* SALARY = "CREATE TABLE IF NOT EXISTS Salary ("
		"id INTEGER PRIMARY KEY,"
		"base_salary REAL,"
		"bonus REAL,"
		"amount REAL AS (base_salary + bonus),"
		"FOREIGN KEY (id) REFERENCES Employee(id) ON DELETE CASCADE)";

	if (!executeQuery(SALARY))
	{
		return false;
	}

	return true;
}

void Database::close() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
		Log::getInstance().Info("Database Closed.");
	}
}

bool Database::executeQuery(const std::string& query) {
	//executes query expect select

	char* errMsg = nullptr;

	int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::string err = { errMsg };
		setError(err);
		Log::getInstance().Error(errMsg);
		sqlite3_free(errMsg);
		return false;
	}

	return true;
}

[[nodiscard]] std::string Database::getError() const  {
	return Error;
}

bool Database::executeQueryCallback(const std::string& query,bool csv) {
	//executes select queries

	char* errMsg = nullptr;
	rows = 0;

	int rc = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);

	std::cout <<"\033[32m" << rows << " rows returned\033[0m \n\n"; 

	if (rc != SQLITE_OK) {
		std::string err = { errMsg };
		setError(err);
		Log::getInstance().Error(errMsg);
		sqlite3_free(errMsg);
		return false;
	}

	//for generating CSV of result
	if (csv && rows>0) {

		char input;
		std::cout << "Need this data in csv format? Press Y for Yes or N for No: ";
		std::cin >> input;
		if (input == 'Y' || input == 'y') {
			std::string path = "exports/";
			std::string userFileName;
			std::cout << "Enter Filename : ";
			std::cin >> userFileName;
			path = path + userFileName + ".csv";
			if (Database::getInstance().export_to_csv(query, path)) {
				system("cls");
				std::cout << "File Exported at " << path << "\n\n";
			}
		}
		else {
			system("cls");
		}
	}
	return true;
}

int Database::callback(void* data, int argc, char** argv, char** azColName) {
	//prints the result of select query
	++rows;
	int colWidth = 22;
	size_t length;

	// all this for printing it nicely on console
	std::cout << "|------------------------------------------------------------------------------------------------------------|" << "\n";
	for (int i = 0; i < argc; ++i) {
		length = strlen(azColName[i]) - 2;
		std::cout << "|" << azColName[i] << std::setw(colWidth - length) << "| " << (argv[i] ? argv[i] : "NULL") << std::setw(86 - strlen(argv[i] ? argv[i] : "NULL"))<< "|\n";
	}
	std::cout << "|------------------------------------------------------------------------------------------------------------|" << "\n";
	return 0;
}

bool Database::executeQueryRows(const std::string& query) {
	//for only getting the number of rows executed by query
	char* errMsg = nullptr;
	rows = 0;
	int rc = sqlite3_exec(db, query.c_str(), callbackRows, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::string err = { errMsg };
		setError(err);
		Log::getInstance().Error(errMsg);
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}

int Database::callbackRows(void* data, int argc, char** argv, char** azColName) {
	//just increments rows for executeQueryRows
	++rows;
	return 0;
}

[[nodiscard]] int Database::getRow() const {
	return rows;
}

void Database::setError(std::string& errorMessage) {
	Error = std::string("\033[31m") + errorMessage + "\033[0m";
}

void Database::createTableQuery() {
	//creates table 
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

		std::cout << "Enter column constraints (e.g., PRIMARY KEY, UNIQUE, NOT NULL, etc.): ";
		std::cin.ignore();
		std::getline(std::cin, constraints);

		columns.push_back(columnName + " " + columnType + " " + constraints);

		std::cout << "Add another column? (y/n): ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	char fkChoice;
	do {
		std::string columnName, refTable, refColumn;
		std::cout << "Enter column name for foreign key: ";
		std::cin >> columnName;
		std::cout << "Enter referenced table name: ";
		std::cin >> refTable;
		std::cout << "Enter referenced column name: ";
		std::cin >> refColumn;

		std::string fkConstraint = "FOREIGN KEY (" + columnName + ") REFERENCES " + refTable + "(" + refColumn + ")";
		columns.push_back(fkConstraint);

		std::cout << "Add another foreign key? (y/n): ";
		std::cin >> fkChoice;
	} while (fkChoice == 'y' || fkChoice == 'Y');

	for (int i = 0; i < columns.size(); ++i) {
		sql += columns[i];
		if (i < columns.size() - 1) {
			sql += ",";
		}
	}
	sql += ");";

	if (executeQuery(sql)) {
		Log::getInstance().Info(tableName + " created.");
	}
}

void Database::showTables(){
	//shows all the available table in existing DB
	std::string showQuery = " SELECT name FROM sqlite_schema ;";
	if (!executeQueryCallback(showQuery))
		std::cout << getError() << "\n\n";
	else
		Log::getInstance().Info("Show table Query Fetched.");

}

void Database::deleteTableQuery() {
	//Delete or Truncate table 
	system("cls");
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

		if (executeQuery(deleteQuery)) {
			std::cout << "Table Dropped Succesfully ! \n\n";
			Log::getInstance().Info(tableName, " Dropped.");

		}
		else
			std::cout << Database::getInstance().getError() << "\n\n";

		break;

	case 2:
		std::cout << "Enter Table Name to Delete: ";
		std::cin >> tableName;
		deleteQuery = "DELETE FROM " + tableName + ";";

		if (executeQuery(deleteQuery)) {
			std::cout << "Table Deleted Succesfully ! \n\n";
			Log::getInstance().Info(tableName, " Deleted.");
		}
		else
			std::cout << Database::getInstance().getError() << "\n\n";

		break;

	default:
		std::cout << "Wrong Input..!\n\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}

}

void Database::userSqlQuery(){
	//custom user sql query executor
	std::string sqlQuery;

	std::cout << "Enter sql query : ";
	std::cin.ignore();
	std::getline(std::cin, sqlQuery);

	for (int i = 0; i < sqlQuery.size(); i++) {
		sqlQuery[i] = std::tolower(sqlQuery[i]);
	}

	size_t pos = sqlQuery.find("select");


	if (pos == 0) {
		if (executeQueryCallback(sqlQuery)) {
			std::cout << "SQL Query Completed Successfully ! \n\n";
			Log::getInstance().Info(sqlQuery, " : Executed.");
		}
		else
			std::cout << getError() << "\n";
	}
	else {
		if (executeQuery(sqlQuery)) {
			std::cout << "SQL Query Completed Successfully ! \n\n";
			Log::getInstance().Info(sqlQuery, " : Executed.");
		}
		else
			std::cout << getError() << "\n";
	}

}

bool Database::exportDatabase() {
	//exports all the existing DB tables to backup folder
	std::string showQuery = " SELECT name FROM sqlite_schema ;";
	std::string table = "SELECT * FROM ";
	std::string path="backup/";
	sqlite3_stmt* stmt = nullptr;
	int rc = sqlite3_prepare_v2(db, showQuery.c_str(), -1, &stmt, nullptr);

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		table += reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		path = path + reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) + ".csv";
		
		if (!Database::getInstance().export_to_csv(table, path)) {
			std::cout << getError() << "\n\n";
			return false;
		}
		table = "SELECT * FROM ";
		path = "backup/";
	}
	
	return true;
}

bool Database::export_to_csv(const std::string& query, const std::filesystem::path& filename) {
	//exports all the result from the specified query 
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return false;
	}

	if (!Database::getInstance().executeQuery(query)) {
		std::cerr << "Failed to execute query." << std::endl;
		return false;
	}

	sqlite3_stmt* stmt = nullptr;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	int columns = sqlite3_column_count(stmt);
	for (int i = 0; i < columns; ++i) {
		file << sqlite3_column_name(stmt, i);
		if (i < columns - 1)
			file << ",";
	}
	file << "\n";

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < columns; ++i) {
			if (sqlite3_column_text(stmt, i)) {
				file << sqlite3_column_text(stmt, i);
			}
			if (i < columns - 1)
				file << ",";
		}
		file << "\n";
	}

	if (rc != SQLITE_DONE) {
		std::cout << getError() << "\n\n";
		return false;
	}
	else {
		//Log::getInstance().Info(table,"Exported.");
	}
	sqlite3_finalize(stmt);
	return true;
}

bool Database::checkExist(std::string table, int id) {
	//check existance of an entity in table
	std::string  checkExistance = "SELECT id FROM "+table +" WHERE id = " + std::to_string(id);
	Database::getInstance().executeQueryRows(checkExistance);
	if (int rows = Database::getInstance().getRow(); rows == 0) {
		return false;
	}
	return true;
}