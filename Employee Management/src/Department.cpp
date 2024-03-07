#include "../include/Department.h"
//#include "../include/validate.h"
void Department::setId() {
	std::cout << "Enter Department Id: ";
	std::cin >> id;
}
void Department::setName() {
	std::cout << "Enter Department Name: ";
	std::cin >> name;
}
void Department::setManagerId() {
	std::cout << "Enter Department ManagerId: ";
	std::cin >> manager_id;
}
void Department::setDescription() {
	std::cout << "Enter Department Description: ";
	std::cin.ignore();
	std::getline(std::cin, description);

}

void Department::insertDepartment() {

	system("cls");

	std::cout << "Insert Department Details:\n";
	setId();
	setName();
	setManagerId();
	setDescription();

	std::string insertQuery = "INSERT INTO Department (id, name, manager_id, description) VALUES ("
		+ std::to_string(id) + ", '" +
		name + "', '" +
		std::to_string(manager_id) + "', '" +
		description + "');";

	//std::string insertQuery = "INSERT INTO Department (id, name, manager_id, description) VALUES (1, 'Engineering', 1, 'Responsible for technical development'),(2, 'Human Resources', 2, 'Responsible for managing personnel'),(3, 'Marketing', 3, 'Responsible for promoting products'); ";

	if (Database::getInstance().executeQuery(insertQuery))
		std::cout << "Inserted Department Succesfully ! \n\n";
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
		deleteDepartment();
		break;
	}

	if (Database::getInstance().executeQuery(deleteQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << changes << " row affected \n\n";
		if (changes != 0) {
			std::cout << "Department Deleted Succesfully ! \n\n";
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
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		updateDepartment();
		break;
	}

	if (Database::getInstance().executeQuery(updateQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << changes << " row affected \n\n";
		if (changes != 0) {
			std::cout << "Department Updated Succesfully ! \n\n";
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
		selectQuery = "SELECT * FROM Department";
		break;
	case 2:
		setId();
		selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(getId());
		break;
	case 3:
		setName();
		selectQuery = "SELECT * FROM Department WHERE name = '" + getName() + "'";
		break;
	case 4:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		viewDepartment();
		break;
	}

	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
		std::cout << Database::getInstance().getError() << std::endl;
	}

};


void Department::action() {
	bool flag = true;

	while (flag) {

		std::cout << "Department Table\n";
		std::cout << "Please select a value to perform actions:\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Delete\n";
		std::cout << "3. Update\n";
		std::cout << "4. View\n";
		std::cout << "5. Exit\n";
		std::cout << "Enter your choice (1-5): ";

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
			flag = false;
			break;
		default:
			std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
			break;
		}
	}
}
