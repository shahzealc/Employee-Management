
#include "../include/Employee.h"


using logs::Log;

bool Employee::setId() {
	return setAttribute<int>("ID", id, validateNumeric);
}

bool Employee::setFirstname() {
	return setAttribute<std::string>("First Name", firstname, validateAlphabetic);
}

bool Employee::setLastname() {
	return setAttribute<std::string>("Last Name", lastname, validateAlphabetic);
}

bool Employee::setDob() {
	return setAttribute<std::string>("Date of Birth (DD-MM-YYYY)", dob, validateDateOfBirth);
}

bool Employee::setMobile() {
	return setAttribute<std::string>("Mobile number", mobile, validatePhoneNumber);
}

bool Employee::setEmail() {
	return setAttribute<std::string>("Email address", email, validateEmail);
}

bool Employee::setAddress() {
	std::cout << "Address: ";
	std::cin.ignore();
	std::getline(std::cin, address);
	return true;
}

bool Employee::setGender() {
	return setAttribute<std::string>("Gender (Male, Female, Other)", gender, [](const std::string& input) {
		return input == "Male" || input == "Female" || input == "Other";
		});
}

bool Employee::setDoj() {
	return setAttribute<std::string>("Date of Joining (DD-MM-YYYY)", doj, validateDateOfBirth);
}

bool Employee::setWLocation() {
	return setAttribute<std::string>("Work Location", w_location, validateAlphabetic);
}

bool Employee::setManagerId() {
	auto res = setAttribute<int>("Manager ID (-1 for null)", manager_id, validateNumeric);
	if (manager_id == -1) {
		manager_id = NULL;
	}
	return res;
}

bool Employee::setDepartmentId() {
	auto res = setAttribute<int>("Department ID (-1 for null)", department_id, validateNumeric);
	if (department_id == -1) {
		department_id = NULL;
	}
	return res;
}

bool Employee::insertEmployee() {
	system("cls");

	std::cout << "Enter Employee Details:\n";

	if (!setId()) {
		return false;
	}

	if (Database::getInstance().checkExist("Employee", id)) {
		std::cout << "\033[33mEmployee already exist for id: " << id << "\033[0m\n\n";
		return false;
	}

	if (setFirstname() && setLastname() && setDob() && setMobile() && setEmail() && setAddress() && setGender() && setDoj() && setWLocation() && setManagerId() && setDepartmentId())
		return EmployeeController::insertEmployeeController(*this);
	return false;
}

bool Employee::deleteEmployeeById(int eid) {

	id = eid;

	std::string deleteQuery{};

	std::string viewEmployee = "SELECT id,firstname,lastname,email FROM Employee WHERE id = " + std::to_string(id);

	if (!Database::getInstance().executeQueryCallback(viewEmployee, false)) {
		std::cout << Database::getInstance().getError() << std::endl;
		return false;
	}

	std::cout << "\033[36mEnter Y: to delete this Employee\nEnter N: to exit\033[0m\n";
	char confirm;
	std::cin >> confirm;

	if (confirm == 'Y' || confirm == 'y') {
		if (EmployeeController::deleteEmployeeController(*this, "id"))
			return true;
	}
	return false;
};

bool Employee::updateEmployee() {

	int choice;
	bool controllerResult;

	system("cls");

	if (!setId()) {
		return false;
	}

	if (!Database::getInstance().checkExist("Employee", id)) {
		std::cout << "\033[33mEmployee Not exist for id: " << id << "\033[0m\n\n";
		return false;
	}

	bool flag = true;
	while (flag) {
		flag = false;
		std::cout << "Please select an attribute to update:\n";
		std::cout << "1. Firstname\n";
		std::cout << "2. Lastname\n";
		std::cout << "3. Date of Birth\n";
		std::cout << "4. Mobile number\n";
		std::cout << "5. Email address\n";
		std::cout << "6. Address\n";
		std::cout << "7. Gender\n";
		std::cout << "8. Date of Joining\n";
		std::cout << "9. Work Location\n";
		std::cout << "10. Manager ID\n";
		std::cout << "11. Department ID\n";
		std::cout << "12. Go Back\n";
		std::cout << "Enter your choice (1-12): ";

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			if (!setFirstname()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "firstname");
			break;
		case 2:
			if (!setLastname()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "lastname");
			break;
		case 3:
			if (!setDob()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "dob");
			break;
		case 4:
			if (!setMobile()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "mobile");
			break;
		case 5:
			if (!setEmail()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "email");
			break;
		case 6:
			if (!setAddress()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "address");
			break;
		case 7:
			if (!setGender()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "gender");
			break;
		case 8:
			if (!setDoj()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "doj");
			break;
		case 9:
			if (!setWLocation()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "w_location");
			break;
		case 10:
			if (!setManagerId()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "manager_id");
			break;
		case 11:
			if (!setDepartmentId()) {
				return false;
			}
			controllerResult = EmployeeController::updateEmployeeController(*this, "department_id");
			break;
		case 12:
			return true;

		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 12.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			flag = true;
			break;
		}
	}
	return controllerResult;
}

//void Employee::viewEmployee() {
//
//    int choice;
//    bool controllerResult;
//    system("cls");
//    bool flag = true;
//    while (flag) {
//        flag = false;
//        std::cout << "Please select a column to view an employee:\n";
//        std::cout << "1. ALL\n";
//        std::cout << "2. ID\n";
//        std::cout << "3. Firstname\n";
//        std::cout << "4. Gmail\n";
//        std::cout << "5. Go Back\n";
//
//        std::cout << "Enter your choice (1-5): ";
//
//        std::cin >> choice;
//        std::cout << "\n";
//
//        switch (choice) {
//        case 1:
//            system("cls");
//            controllerResult = EmployeeController::viewEmployeeController(*this, "ALL");
//            break;
//        case 2:
//            system("cls");
//            setId();
//            controllerResult = EmployeeController::viewEmployeeController(*this, "ID");
//            break;
//        case 3:
//            system("cls");
//            setFirstname();
//            controllerResult = EmployeeController::viewEmployeeController(*this, "Firstname");
//            break;
//        case 4:
//            system("cls");
//            setEmail();
//            controllerResult = EmployeeController::viewEmployeeController(*this, "Email");
//            break;
//        case 5:
//            system("cls");
//            return;
//        default:
//            system("cls");
//            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
//            flag = true;
//            break;
//        }
//    }
//
//};

void Employee::describeEmployee() const
{

	if (!Database::getInstance().executeQueryCallback("pragma table_info('Employee');")) {
		std::cout << Database::getInstance().getError();
	}
	else {
		Log::getInstance().Info("Employee Described.");
	}

}

//void Employee::action() {
//	bool flag = true;
//
//	int choice;
//
//
//	while (flag) {
//
//
//		std::cout << "Employee Table\n";
//		std::cout << "Please select a value to perform actions:\n";
//		std::cout << "1. Insert\n";
//		std::cout << "2. Delete\n";
//		std::cout << "3. Update\n";
//		std::cout << "4. View\n";
//		std::cout << "5. Describe\n";
//		std::cout << "6. Go back\n";
//		std::cout << "Enter your choice (1-6): ";
//
//		std::cin >> choice;
//		std::cout << "\n";
//
//		switch (choice) {
//		case 1:
//			system("cls");
//			insertEmployee();
//			break;
//		case 2:
//			system("cls");
//			setId();
//			deleteEmployeeById(getId());
//			break;
//		case 3:
//			system("cls");
//			updateEmployee();
//			break;
//		case 4:
//			system("cls");
//			viewEmployee();
//			break;
//		case 5:
//			system("cls");
//			describeEmployee();
//			break;
//		case 6:
//			system("cls");
//			flag = false;
//			break;
//		default:
//			system("cls");
//			std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			break;
//		}
//	}
//}
