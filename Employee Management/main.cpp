
#include <iostream>
#include "include/database.h"
#include "include/Employee.h"
#include "include/Engineer.h"
#include "include/Manager.h"
#include "include/Salary.h"
#include "include/department.h"


int main() {

	Database db("employee.db");

	if (!db.open()) {
		std::cerr << "Error opening database: " << db.getError() << std::endl;
		return 1;
	}

	bool flag = true;
	int choice;


	while (flag) {

		std::cout << "Welcome to the database management system!\n";
		std::cout << "Please select a table to perform an action:\n";
		std::cout << "1. Employee\n";
		std::cout << "2. Department\n";
		std::cout << "3. Salary\n";
		std::cout << "4. Engineer\n";
		std::cout << "5. Manager\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter your choice (1-6): ";


		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
		{
			Employee e1(db);
			e1.action();
		}
		break;
		case 2:
		{
			Department d1(db);
			d1.action();
		}
		break;
		case 3:
		{
			Salary s1(db);
			s1.action();
		}
		break;
		case 4:
		{
			Engineer en1(db);
			en1.action();
		}
		break;
		case 5:
		{
			Manager m1(db);
			m1.action();
		}
		break;
		case 6: 
			flag = false;
			break;
		default:
			std::cerr << "Invalid choice. Please enter a number between 1 and 6.\n";
			break;
		}
	}

	db.close();

	return 0;
}
