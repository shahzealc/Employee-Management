
#include <conio.h>
#include <iostream>
#include "include/database.h"
#include "include/Employee.h"
#include "include/Engineer.h"
#include "include/Manager.h"
#include "include/Department.h"
#include "include/Salary.h"


int main() {


	if (!Database::getInstance().open("employee.db")) {
		std::cerr << "Error opening database: " << Database::getInstance().getError() << std::endl;
		return 1;
	}

	bool flag = true;
	int choice;


	while (flag) {

		std::cout << "Welcome to the database management system!\n";
		std::cout << "Please select a table to perform an action:\n";

		std::cout << "1. Department\n";
		std::cout << "2. Salary\n";
		std::cout << "3. Engineer\n";
		std::cout << "4. Manager\n";
		std::cout << "5. Exit\n";
		std::cout << "Enter your choice (1-5): ";

		std::cin >> choice;

		std::cout << "\n";

		switch (choice) {

		case 1:

		{
			Department d1;
			d1.action();
			system("cls");
		}
		break;
		case 2:
		{
			Salary s1;
			s1.action();
			system("cls");
		}
		break;
		case 3:
		{
			Engineer en1;
			en1.action();
			system("cls");
		}
		break;
		case 4:
		{
			Manager m1;
			m1.action();
			system("cls");
		}
		break;
		case 5:
			flag = false;
			break;
		default:
			system("cls");
			std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
			break;
		}
	}

	Database::getInstance().close();

	return 0;
}
