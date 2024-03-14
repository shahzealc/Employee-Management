#ifndef promptflag
#define promptflag

#include "Employee.h"
#include "Engineer.h"
#include "Manager.h"
#include "Department.h"
#include "Salary.h"

void askPromptTable() {


	bool flagTable = true;
	int choiceTable;


	while (flagTable) {

		system("cls");
		std::cout << "Please select a table to perform an action:\n";

		std::cout << "1. Department\n";
		std::cout << "2. Salary\n";
		std::cout << "3. Engineer\n";
		std::cout << "4. Manager\n";
		std::cout << "5. Exit\n";
		std::cout << "Enter your choice (1-5): ";

		std::cin >> choiceTable;

		std::cout << "\n";

		switch (choiceTable) {

		case 1:

		{
			Department d1;
			d1.action();
		}
		break;
		case 2:
		{
			Salary s1;
			s1.action();
		}
		break;
		case 3:
		{
			Engineer en1;
			en1.action();
		}
		break;
		case 4:
		{
			Manager m1;
			m1.action();
		}
		break;
		case 5:
			flagTable = false;
			break;
		default:
			system("cls");
			std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}

}

void askPromptMain() {


	bool flagMain = true;
	int choiceMain;


	while (flagMain) {

		std::cout << "Welcome to the Employee database management system!\n";
		std::cout << "Please select a action to perform : \n";

		std::cout << "1. Create Table\n";
		std::cout << "2. Delete Table\n";
		std::cout << "3. Show Tables \n";
		std::cout << "4. Manipulate data within the table\n";
		std::cout << "5. Run your own query\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter your choice (1-6): ";

		std::cin >> choiceMain;

		std::cout << "\n";

		switch (choiceMain) {

		case 1:

		{
			Database::getInstance().createTableQuery();
		}
		break;
		case 2:
		{
			Database::getInstance().deleteTableQuery();
		}
		break;
		case 3:
		{
			Database::getInstance().showTables();
		}
		break;
		case 4:
		{
			askPromptTable();
		}
		break;
		case 5:
		{
			Database::getInstance().userSqlQuery();
		}
		break;
		case 6:
			flagMain = false;
			break;
		default:
			system("cls");
			std::cerr << "Invalid choice. Please enter a number between 1 and 6.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}


}

#endif 

