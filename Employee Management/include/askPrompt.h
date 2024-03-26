#ifndef promptflag
#define promptflag

#include "Employee.h"
#include "Engineer.h"
#include "Manager.h"
#include "Department.h"
#include "Salary.h"
#include <map>
#include <functional>
#include <string>

void askPromptTable() {
	std::map<int, std::pair<std::string, std::function<void()>>> tableOptions = {
		{1, {"Department", []() { Department d1; d1.action(); }}},
		{2, {"Salary", []() { Salary s1; s1.action(); }}},
		{3, {"Engineer", []() { Engineer en1; en1.action(); }}},
		{4, {"Manager", []() { Manager m1; m1.action(); }}},
		{5, {"Exit", []() {} }} 
	};

	bool flagTable = true;
	int choiceTable;

	while (flagTable) {
		system("cls");
		std::cout << "Please select a table to perform an action:\n";

		for (const auto& option : tableOptions) {
			std::cout << option.first << ". " << option.second.first << "\n";
		}
		std::cout << "Enter your choice (1-" << tableOptions.size() << "): ";

		std::cin >> choiceTable;
		std::cout << "\n";

		auto it = tableOptions.find(choiceTable);
		if (it != tableOptions.end()) {
			it->second.second(); 
		}
		else {
			system("cls");
			std::cerr << "Invalid choice. Please enter a number between 1 and " << tableOptions.size() << ".\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (choiceTable == 5) {
			flagTable = false; 
		}
	}
}

void askPromptMain() {
	std::map<int, std::pair<std::string, std::function<void()>>> menuOptions = {
	   {1, {"Create Table", []() { Database::getInstance().createTableQuery(); }}},
	   {2, {"Delete Table", []() { Database::getInstance().deleteTableQuery(); }}},
	   {3, {"Show Tables", []() { Database::getInstance().showTables(); }}},
	   {4, {"Manipulate Data within Table", askPromptTable}},
	   {5, {"Run Custom Query", []() { Database::getInstance().userSqlQuery(); }}},
	   //{6, {"Backup Database", &Database::backupDatabase}},
	   {7, {"Exit", nullptr}} 
	};

	bool flagMain = true;
	int choiceMain;

	while (flagMain) {
		
		std::cout << "Welcome to the Employee database management system!\n";
		std::cout << "Please select an action to perform:\n";

		for (const auto& option : menuOptions) {
			std::cout << option.first << ". " << option.second.first << "\n";
		}
		std::cout << "Enter your choice (1-" << menuOptions.size() << "): ";

		std::string input;
		std::cin >> input;

		try {
			choiceMain = std::stoi(input);
		}
		catch (const std::exception& e) {
			std::cerr << "Invalid input. Please enter a number.\n";
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			continue; 
		}

		auto it = menuOptions.find(choiceMain);
		if (it != menuOptions.end()) {
			if (it->second.second) {
				it->second.second();
			}
			else {
				flagMain = false;
			}
		}
		else {
			std::cerr << "Invalid choice. Please enter a number between 1 and " << menuOptions.size() << ".\n";
		}
	}
}

#endif 

