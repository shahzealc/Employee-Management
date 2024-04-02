#include "../include/Department.h"

using logs::Log;

bool Department::setId() {
	return setAttribute("Enter Department Id", id, validateNumeric);
}

bool Department::setName() {
	return setAttribute("Enter Department Name", name, validateAlphabetic);
}

bool Department::setManagerId() {
	auto res = setAttribute<int>("Enter Department Manager ID (-1 for null)", manager_id, validateNumeric);
	if (manager_id == -1) {
		manager_id = NULL;
	}
	return res;
}

bool Department::setDescription() {
	std::cout << "Description: ";
	std::cin.ignore();
	std::getline(std::cin, description);
	return true;
}

bool Department::insertDepartment() {
	//takes the detail for department entity
	system("cls");
	std::cout << "Insert Department Details:\n";
	if (!setId()) {
		return false;
	}

	if (Database::getInstance().checkExist("Department", getId())) { //checks existance for department
		std::cout << "\033[33mDepartment already exist for id: " << getId() << "\033[0m\n\n";
		return false;
	}

	if (setName() && setManagerId() && setDescription()) {
		if (DepartmentController::insertDepartmentController(*this)) //passes to controller for inserting department
			return true;
	}
	
	return false;

}

bool Department::deleteDepartment() {
	//takes input for deleting department 
	int choice;
	bool controllerResult{};
	system("cls");
	bool flag = true;
	while (flag) {
		flag = false;
		std::cout << "Please select a column to delete an Department:\n";
		std::cout << "1. ID\n";
		std::cout << "2. Deptartment Name\n";
		std::cout << "3. Go Back\n";

		std::cout << "Enter your choice (1-3): ";


		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			if (!setId())
				return false;
			controllerResult = DepartmentController::deleteDepartmentController(*this, "id"); //passes to controller for deleting department
			break;
		case 2:
			system("cls");			
			if (!setName())
				return false;
			controllerResult = DepartmentController::deleteDepartmentController(*this, "name"); //passes to controller for deleting department
			break;
		case 3:
			system("cls");
			return true;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			flag = true;
			break;
		}
	}
	return controllerResult;

};

bool Department::updateDepartment() {
	//takes input for updating department 
	int choice;

	bool controllerResult;
	system("cls");
	bool flag = true;

	while (flag) {

		flag = false;

		if (!setId()) {
			return false;
		}

		if (!Database::getInstance().checkExist("Department", id)) {
			std::cout << "\033[33mDepartment Not exist for id: " << id << "\033[0m\n\n";
			return false;
		}

		std::cout << "Please select an attribute to update:\n";
		std::cout << "1. Department Name\n";
		std::cout << "2. Department Manager ID\n";
		std::cout << "3. Description\n";
		std::cout << "4. Go Back\n";
		std::cout << "Enter your choice (1-4): ";

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			if (!setName()) {
				return false;
			}
			controllerResult = DepartmentController::updateDepartmentController(*this, "name"); //passes to controller for updating dept
			break;
		case 2:
			system("cls");
			if (!setManagerId()) {
				return false;
			}
			controllerResult = DepartmentController::updateDepartmentController(*this, "manager_id"); //passes to controller for updating dept
			break;
		case 3:
			system("cls");
			if (!setDescription()) {
				return false;
			}
			controllerResult = DepartmentController::updateDepartmentController(*this, "description"); //passes to controller for updating dept
			break;
		case 4:
			system("cls");
			return true;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			flag = true;
			break;
		}
	}

	return controllerResult;
}

bool Department::viewDepartment() {
	//takes input for viewing department 
	int choice;
	bool controllerResult;

	system("cls");
	bool flag = true;
	while (flag) {
		flag = false;
		std::cout << "Please select a column to view a Department:\n";
		std::cout << "1. ALL\n";
		std::cout << "2. Deptartment Id\n";
		std::cout << "3. Deptartment Name\n";
		std::cout << "4. Go Back\n";

		std::cout << "Enter your choice (1-4): ";
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			controllerResult = DepartmentController::viewDepartmentController(*this, "all"); //passes to controller for viewing dept
			break;
		case 2:
			system("cls");
			setId();
			controllerResult = DepartmentController::viewDepartmentController(*this, "id"); //passes to controller for viewing dept
			break;
		case 3:
			system("cls");
			setName();
			controllerResult = DepartmentController::viewDepartmentController(*this, "name"); //passes to controller for viewing dept
			break;
		case 4:
			system("cls");
			return true;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			flag = true;
			break;
		}
	}
	return controllerResult;

}

void Department::describeDepartment() const{
	//describes dept
	if (!Database::getInstance().executeQueryCallback("pragma table_info('Department');")) {
		std::cout << Database::getInstance().getError();
	}
	else {
		Log::getInstance().Info("Department Described.");
	}

}

void Department::action() {
	//takes user input for different action
	bool flag = true;

	while (flag) {

		std::cout << "Department Table\n";
		std::cout << "Please select a value to perform actions:\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Delete\n";
		std::cout << "3. Update\n";
		std::cout << "4. View\n";
		std::cout << "5. Describe\n";
		std::cout << "6. Go Back\n";
		std::cout << "Enter your choice (1-6): ";

		int choice;
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			insertDepartment();
			break;
		case 2:
			system("cls");
			deleteDepartment();
			break;
		case 3:
			system("cls");
			updateDepartment();
			break;
		case 4:
			system("cls");
			viewDepartment();
			break;
		case 5:
			system("cls");
			describeDepartment();
			break;
		case 6:
			system("cls");
			flag = false;
			break;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}
