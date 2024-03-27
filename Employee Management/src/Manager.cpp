#include "../include/Manager.h"

using logs::Log;

void Manager::setManagementExperience() {
	setAttribute("Enter Manager Experience in years", management_experience, validateNumeric);
}

void Manager::setProjectTitle() {
	std::cout << "Enter Manager's Project Title: ";
	std::cin.ignore();
	std::getline(std::cin, project_title);
}

void Manager::insertManager() {

	std::string insertQueryEmployee = insertEmployee();

	if (insertQueryEmployee == "Employee already exist") {
		return;
	}

	setManagementExperience();
	setProjectTitle();

	std::string insertQueryManager = "INSERT INTO Manager(id, management_experience , project_title) VALUES ("
		+ std::to_string(Employee::getId()) + ","
		+ std::to_string(management_experience) + ",'"
		+ project_title + "');";

	auto s1 = std::make_unique<Salary>();
	std::string insertQuerySalary = s1->insertSalaryById(Employee::getId());

	if (Database::getInstance().executeQuery(insertQueryEmployee) && Database::getInstance().executeQuery(insertQueryManager) &&
			Database::getInstance().executeQuery(insertQuerySalary)) {
		std::cout << "Inserted Manager Succesfully ! \n\n";
		Log::getInstance().Info("Manager Inserted for id : ", getId());
	}
	else
		std::cout << Database::getInstance().getError() << "\n\n";

};

void Manager::deleteManager() {

	setId();
	std::string checkManager = "SELECT id FROM Manager WHERE id = " + std::to_string(getId());

	if (!Database::getInstance().executeQueryRows(checkManager)) {
		std::cout << Database::getInstance().getError() << std::endl;
	}

	if (int rows = Database::getInstance().getRow(); rows > 0) {
		deleteEmployeeById(getId());
		Log::getInstance().Info("Manager Deleted for id : ", getId());
	}
	else {
		std::cout << "Manager Not exist" << "\n\n";
		Log::getInstance().Warn("Manager Not exist for id : ", getId());
	}

};

void Manager::updateManager() {
	int choice;
	std::string updateQuery = "UPDATE Manager SET";

	bool flag = true;
	std::cout << "1. To update Employee Table related details\n";
	std::cout << "2. To update Manager Table related details\n";

	std::cout << "Select from above given choices:";
	std::cin >> choice;
	switch (choice) {
	case 1:
		system("cls");
		updateEmployee();
		break;
	case 2:
		system("cls");
		int id;

		while (flag) {
			flag = false;
			std::cout << "Enter Employee id to update: \n";
			std::cin >> id;

			if (!Database::getInstance().checkExist("Manager", id)) {
				std::cout << "Manager Not exist for id: " << id << "\n\n";
				return;
			}

			std::cout << "Please select an attribute to update:\n";
			std::cout << "1. Manager's Experience\n";
			std::cout << "2. Project Title\n";
			std::cout << "3. Go Back\n";
			std::cout << "Enter your choice (1-3): ";

			std::cin >> choice;
			std::cout << "\n";

			switch (choice) {
			case 1:
				setManagementExperience();
				updateQuery += " management_experience = '" + std::to_string(getManagementExperience()) + "'";
				break;
			case 2:
				setProjectTitle();
				updateQuery += " project_title= '" + getProjectTitle() + "'";
				break;
			case 3:
				return;
			default:
				system("cls");
				std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				flag = true;
				break;
			}
		}
		updateQuery += " WHERE id = " + std::to_string(id) + ";";
		if (Database::getInstance().executeQuery(updateQuery)) {

			int changes = sqlite3_changes(Database::getInstance().db);

			std::cout << changes << " row affected \n\n";
			if (changes != 0) {
				std::cout << "Manager Updated Succesfully ! \n\n";
				Log::getInstance().Info("Manager Updated for id : ", getId());
			}

		}
		else
			std::cout << Database::getInstance().getError() << "\n";
		break;
	default:
		system("cls");
		std::cout << "Invalid choice Please Enter a number 1 or 2 only\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}

};

void Manager::viewManager() {
	std::string selectQuery{};
	bool flag = true;
	int choice;
	while (flag) {
		std::cout << "Please select a column to view a Manager:\n";
		std::cout << "1. ALL\n";
		std::cout << "2. Employee Id\n";
		std::cout << "3. Employees under Manager\n";
		std::cout << "4. Order by column\n";
		std::cout << "5. Go Back\n";

		std::cout << "Enter your choice (1-5): ";

		flag = false;
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Manager WHERE Employee.id==Manager.id ";
			break;
		case 2:
			system("cls");
			setId();
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Manager WHERE Employee.id==Manager.id AND Employee.id =" + std::to_string(getId());
			break;
		case 3:
			system("cls");
			setId();
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Engineer WHERE Employee.id = Engineer.id AND manager_id =" + std::to_string(getId());
			break;
		case 4:
		{
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Manager WHERE Employee.id==Manager.id";
			system("cls");
			int choice;
			std::cout << "Select column to order by:\n";
			std::cout << "1. Firstname\n";
			std::cout << "2. Lastname\n";
			std::cout << "3. Date of Joining\n";
			std::cout << "4. Experience\n";


			std::cin >> choice;

			std::string orderByColumnName;
			switch (choice) {
			case 1:
				orderByColumnName = "firstname";
				break;
			case 2:
				orderByColumnName = "lastname";
				break;
			case 3:
				orderByColumnName = "doj";
				break;
			case 4:
				orderByColumnName = "management_experience";
				break;
			default:
				std::cout << "Invalid input!\n";
				break;
			}

			if (!orderByColumnName.empty()) {
				int orderDirection;
				std::cout << "Select order direction:\n";
				std::cout << "1. Ascending\n";
				std::cout << "2. Descending\n";
				std::cin >> orderDirection;

				std::string orderDirectionStr = (orderDirection == 1) ? "ASC" : "DESC";
				selectQuery += " ORDER BY " + orderByColumnName + " " + orderDirectionStr;
			}
			break;
		}
		case 5:
			system("cls");
			return;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			flag = true;
			break;
		}
	}
		if (!Database::getInstance().executeQueryCallback(selectQuery)) {
			std::cout << Database::getInstance().getError() << std::endl;
		}
		else {
			Log::getInstance().Info(selectQuery, " : Executed.");
		}
	
};

void Manager::describeManager() const
{

	if (!Database::getInstance().executeQueryCallback("pragma table_info('Manager');")) {
		std::cout << Database::getInstance().getError();
	}
	else {
		Log::getInstance().Info("Manager Described.");
	}

}

void Manager::action() {
	bool flag = true;

	while (flag) {
		std::cout << "Manager Table\n";
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


		switch (choice) {
		case 1:
			system("cls");
			insertManager();
			break;
		case 2:
			system("cls");
			deleteManager();
			break;
		case 3:
			system("cls");
			updateManager();
			break;
		case 4:
			system("cls");
			viewManager();
			break;
		case 5:
			system("cls");
			describeManager();
			break;
		case 6:
			system("cls");
			flag = false;
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
