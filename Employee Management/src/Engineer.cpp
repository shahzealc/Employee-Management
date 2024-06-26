#include "../include/Engineer.h"


using logs::Log;

bool Engineer::setProgrammingLanguage()
{
	std::cout << "Enter Programming Language (seperated by space if multiple) : ";
	std::cin.ignore();
	std::getline(std::cin, programming_language);
	return true;
}

bool Engineer::setSpecialization()
{
	std::cout << "Enter Specialization : ";
	std::cin >> specialization;
	return true;
}

bool Engineer::insertEngineer() {
	//first inserts employee and then inserts extra details of engineer and salary.

	if (!insertEmployee()) {
		return false;
	}

	if (setProgrammingLanguage() && setSpecialization()) {
		Salary s1;
		if (s1.insertSalaryById(getId())) 
			return EngineerController::insertEngineerController(*this, s1); //passes to controller for inserting engineer
	}
	EmployeeController::deleteEmployeeController(*this, "id"); //deletes employee if error occured while inserting engineer or salary
	return false;
};

bool Engineer::deleteEngineer() {
	
	if (!setId())
		return false;

	if (!Database::getInstance().checkExist("Engineer", getId())) { //check existance of engineer
		std::cout << "\033[33mEngineer Not exist\033[0m" << "\n\n";
		Log::getInstance().Warn("Engineer not exist for id : ", getId());
		return false;
	}

	//lets user see the detail of employee he/she trying to delete
	std::string viewEmployee = "SELECT id,firstname,lastname,email FROM Employee WHERE id = " + std::to_string(getId());
	if (!Database::getInstance().executeQueryCallback(viewEmployee, false)) {
		std::cout << Database::getInstance().getError() << std::endl;
		return false;
	}

	//asks user to confirm the delete.
	std::cout << "\033[36mEnter Y: to delete this Employee\nEnter N: to exit\033[0m\n";
	char confirm;
	std::cin >> confirm;

	if (confirm == 'Y' || confirm == 'y') {
		return EngineerController::deleteEngineerController(*this, "id");
	}

};

bool Engineer::updateEngineer() {

	int choice;
	bool controllerResult{};

	std::string updateQuery = "UPDATE Engineer SET";
	std::string  checkExistance;
	bool flag = true;
	int eid{};

	std::cout << "1. To update Employee Table related details\n";
	std::cout << "2. To update Engineer Table related details\n";

	std::cout << "Select from above given choices:";
	std::cin >> choice;
	switch (choice) {
	case 1:
		system("cls");
		return updateEmployee(); //for updating employee related data
		break;
	case 2: //for updating Engineer related data
		system("cls");

		while (flag) {
			flag = false;
			std::cout << "Enter Employee id to update: \n";
			std::cin >> eid;

			if (!Database::getInstance().checkExist("Engineer", eid)) { //check existance for engineer
				std::cout << "\033[33mEngineer Not exist for id: " << eid << "\033[0m\n\n";
				return false;
			}
			std::cout << "Please select an attribute to update:\n";
			std::cout << "1. Programming Language \n";
			std::cout << "2. Specialization \n";
			std::cout << "3. Go Back \n";
			std::cout << "Enter your choice (1-3): ";

			std::cin >> choice;
			std::cout << "\n";

			switch (choice) {
			case 1:
				if (!setProgrammingLanguage())
					return false;
				controllerResult = EngineerController::updateEngineerController(*this, "programming_language"); //passes to controller for updating engineer
				break;
			case 2:
				if (!setSpecialization())
					return false;
				controllerResult = EngineerController::updateEngineerController(*this, "specialization"); //passes to controller for updating engineer
				break;
			case 3:
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

		break;
	default:
		system("cls");
		std::cout << "Invalid choice Please Enter a number 1 or 2 only\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}
	return controllerResult;
};

bool Engineer::viewEngineer() {
	std::string selectQuery{};

	int choice;
	bool flag = true;
	while (flag) {
		flag = false;
		std::cout << "Please select a column to view an Engineer:\n";
		std::cout << "1. ALL\n";
		std::cout << "2. Employee Id\n";
		std::cout << "3. Order by column\n";
		std::cout << "4. Go Back\n";

		std::cout << "Enter your choice (1-4): ";

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Engineer WHERE Employee.id==Engineer.id ";
			break;
		case 2:
			system("cls");
			setId();
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Engineer WHERE Employee.id==Engineer.id AND Employee.id =" + std::to_string(getId());
			break;
		case 3:
		{
			selectQuery = "SELECT * FROM Employee NATURAL JOIN Engineer WHERE Employee.id==Engineer.id";
			system("cls");
			int choice2;
			std::cout << "Select column to order by:\n";
			std::cout << "1. Firstname\n";
			std::cout << "2. Lastname\n";
			std::cout << "3. Date of Joining\n";

			std::cin >> choice2;

			std::string orderByColumnName;
			switch (choice2) {
			case 1:
				orderByColumnName = "firstname";
				break;
			case 2:
				orderByColumnName = "lastname";
				break;
			case 3:
				orderByColumnName = "doj";
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
	return EngineerController::viewEngineerController(selectQuery);
}

void Engineer::describeEngineer() const
{

	if (!Database::getInstance().executeQueryCallback("pragma table_info('Engineer');")) {
		std::cout << Database::getInstance().getError();
	}

}

void Engineer::action() {
	bool flag = true;
	int choice;


	while (flag) {

		std::cout << "Engineer Table\n";
		std::cout << "Please select a value to perform actions:\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Delete\n";
		std::cout << "3. Update\n";
		std::cout << "4. View\n";
		std::cout << "5. Describe\n";
		std::cout << "6. Go Back\n";
		std::cout << "Enter your choice (1-6): ";

		std::cin >> choice;

		switch (choice) {
		case 1:
			system("cls");
			insertEngineer();
			break;
		case 2:
			system("cls");
			deleteEngineer();
			break;
		case 3:
			system("cls");
			updateEngineer();
			break;
		case 4:
			system("cls");
			viewEngineer();
			break;
		case 5:
			system("cls");
			describeEngineer();
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
