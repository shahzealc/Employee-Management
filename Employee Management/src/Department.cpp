#include "../include/Department.h"
#include "../include/log.h"
#include "../include/validate.h"

using logs::Log;

void Department::setId() {
	std::cout << "Enter Department Id: ";
	std::string inputValidate;
	std::cin >> inputValidate;
	if (validateNumeric(inputValidate)) {
		id = std::stoi(inputValidate);
	}
	else {
		std::cout << "Wrong Input!\n";
		setId();
	}
}
void Department::setName() {
	std::cout << "Enter Department Name: ";

	std::string inputValidate;
	std::cin.ignore();
	std::getline(std::cin, inputValidate);
	if (validateAlphabetic(inputValidate)) {
		name = inputValidate;
	}
	else {
		std::cout << "Wrong Input!\n";
		setName();
	}
}
void Department::setManagerId() {
	std::cout << "Enter Department ManagerId (-1 for NULL): ";
	std::string input;
	std::cin >> input;
	int tempId;
	if (validateNumeric(input)) {
		tempId = std::stoi(input);
		manager_id = (tempId == -1) ? NULL : tempId;
	}
	else {
		std::cout << "Wrong Input!\n";
		setManagerId();
	}
}
void Department::setDescription() {
	std::cout << "Enter Department Description: ";
	std::string inputValidate;

	std::cin.ignore();
	std::getline(std::cin, inputValidate);

	if (validateAlphabetic(inputValidate)) {
		description = inputValidate;
	}
	else {
		std::cout << "Wrong Input!\n";
		setDescription();
	}
}



void Department::insertDepartment() {
	system("cls");
	std::cout << "Insert Department Details:\n";
	setId();
	setName();
	setManagerId();
	setDescription();

	std::string managerIdString = (manager_id != NULL) ? std::to_string(manager_id) : "NULL";

	std::string insertQuery = "INSERT INTO Department (id, name, manager_id, description) VALUES ("
		+ std::to_string(id) + ", '" +
		name + "', " +
		managerIdString + ", '" +
		description + "');";

	if (Database::getInstance().executeQuery(insertQuery)) {
		std::cout << "Inserted Department Successfully! \n\n";
		Log::getInstance().Info("Department Inserted for id : ", id);
	}
	else
		std::cout << Database::getInstance().getError() << "\n";
};
void Department::deleteDepartment() {
	std::string deleteQuery{};

	int choice;

	system("cls");
	std::cout << "Please select a column to delete an Department:\n";
	std::cout << "1. ID\n";
	std::cout << "2. Deptartment Name\n";
	std::cout << "3. Exit\n";

	std::cout << "Enter your choice (1-3): ";


	std::cin >> choice;
	std::cout << "\n";

	switch (choice) {
	case 1:
		setId();
		deleteQuery = "DELETE FROM Department WHERE id = " + std::to_string(getId());
		break;
	case 2:
		setName();
		deleteQuery = "DELETE FROM Department WHERE name = '" + getName() + "'";
		break;

	case 3:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		deleteDepartment();
		break;
	}

	if (Database::getInstance().executeQuery(deleteQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << changes << " row affected \n\n";
		if (changes != 0) {
			std::cout << "Department Deleted Succesfully ! \n\n";
			Log::getInstance().Info("Department Deleted for id : ", id);
		}

	}
	else
		std::cout << Database::getInstance().getError() << "\n";

};
void Department::updateDepartment() {
	std::string updateQuery{};
	int choice;

	system("cls");
	std::cout << "Enter Department id to update: \n";
	std::cin >> id;

	system("cls");
	std::cout << "Please select an attribute to update:\n";
	std::cout << "1. Deptartment Name\n";
	std::cout << "2. Deptartment Manager_Id\n";
	std::cout << "3. Description\n";
	std::cout << "4. Exit\n";
	std::cout << "Enter your choice (1-4): ";

	std::cin >> choice;
	std::cout << "\n";

	switch (choice) {
	case 1:
		setName();
		updateQuery = "UPDATE Department SET name = '" + getName() + "' WHERE id = " + std::to_string(id);
		break;
	case 2:
		setManagerId();
		updateQuery = "UPDATE Department SET manager_id= '" + std::to_string(getManagerId()) + "' WHERE id = " + std::to_string(id);
		break;
	case 3:
		setDescription();
		updateQuery = "UPDATE Department SET description = '" + getDescription() + "' WHERE id = " + std::to_string(id);
		break;
	case 4:
		break;
	
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		updateDepartment();
		break;
	}

	if (Database::getInstance().executeQuery(updateQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << changes << " row affected \n\n";
		if (changes != 0) {
			std::cout << "Department Updated Succesfully ! \n\n";
			Log::getInstance().Info("Department Updated for id : ", id);
		}

	}
	else
		std::cout << Database::getInstance().getError() << "\n";

};
void Department::viewDepartment() {
	std::string selectQuery{};

	int choice;
	system("cls");
	std::cout << "Please select a column to view a Department:\n";
	std::cout << "1. ALL\n";
	std::cout << "2. Deptartment Id\n";
	std::cout << "3. Deptartment Name\n";
	std::cout << "4. Exit\n";

	std::cout << "Enter your choice (1-4): ";


	std::cin >> choice;
	std::cout << "\n";

	switch (choice) {
	case 1:
		selectQuery = "SELECT department.id,name,description,firstname as manager_name from Department LEFT JOIN Employee where Department.manager_id=Employee.id;";
		break;
	case 2:
		setId();
		selectQuery = "SELECT department.id,name,description,firstname as manager_name from Department LEFT JOIN Employee where Department.manager_id=Employee.id AND Department.id = " + std::to_string(getId());
		break;
	case 3:
		setName();
		selectQuery = "SELECT department.id,name,description,firstname as manager_name from Department LEFT JOIN Employee where Department.manager_id=Employee.id AND name = '" + getName() + "'";
		break;
	case 4:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		viewDepartment();
		break;
	}

	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
		std::cout << Database::getInstance().getError() << std::endl;
	}
	else {
		Log::getInstance().Info(selectQuery, " : Executed.");
	}

};

void Department::describeDepartment()
{

	if (!Database::getInstance().executeQueryCallback("pragma table_info('Department');")) {
		std::cout << Database::getInstance().getError();
	}
	else {
		Log::getInstance().Info("Department Described.");
	}

}

void Department::action() {
	bool flag = true;

	while (flag) {

		std::cout << "Department Table\n";
		std::cout << "Please select a value to perform actions:\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Delete\n";
		std::cout << "3. Update\n";
		std::cout << "4. View\n";
		std::cout << "5. Describe\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter your choice (1-6): ";

		int choice;
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			insertDepartment();
			break;
		case 2:
			deleteDepartment();
			break;
		case 3:
			updateDepartment();
			break;
		case 4:
			viewDepartment();
			break;
		case 5:
			describeDepartment();
			break;
		case 6:
			flag = false;
			break;
		default:
			std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}
