
#include "../include/Employee.h"

using logs::Log;

void Employee::setId() {
	setAttribute<int>("ID", id, validateNumeric);
}

void Employee::setFirstname() {
	setAttribute<std::string>("First Name", firstname, validateAlphabetic);
}

void Employee::setLastname() {
	setAttribute<std::string>("Last Name", lastname, validateAlphabetic);
}

void Employee::setDob() {
	setAttribute<std::string>("Date of Birth (DD-MM-YYYY)", dob, validateDateOfBirth);
}

void Employee::setMobile() {
	setAttribute<std::string>("Mobile number", mobile, validatePhoneNumber);
}

void Employee::setEmail() {
	setAttribute<std::string>("Email address", email, validateEmail);
}

void Employee::setAddress() {
	std::cout << "Address: ";
	std::cin.ignore();
	std::getline(std::cin, address);
}

void Employee::setGender() {
	setAttribute<std::string>("Gender (Male, Female, Other)", gender, [](const std::string& input) {
		return input == "Male" || input == "Female" || input == "Other";
		});
}

void Employee::setDoj() {
	setAttribute<std::string>("Date of Joining (DD-MM-YYYY)", doj, validateDateOfBirth);
}

void Employee::setWLocation() {
	setAttribute<std::string>("Work Location", w_location, validateAlphabetic);
}

void Employee::setManagerId() {
	setAttribute<int>("Manager ID (-1 for null)", manager_id, validateNumeric);
	if (manager_id == -1) {
		manager_id = NULL;
	}
}
 
void Employee::setDepartmentId() {
	setAttribute<int>("Department ID (-1 for null)", department_id, validateNumeric);
	if (department_id == -1) {
		department_id = NULL;
	}
}

bool Employee::insertEmployee() {
	system("cls");
	std::cout << "Enter Employee Details:\n";

	setId();

	if (Database::getInstance().checkExist("Employee", id)) {
		std::cout << "\033[33mEmployee already exist for id: " << id << "\033[0m\n\n";
		return false;
	}

	setFirstname();
	setLastname();
	setDob();
	setMobile();
	setEmail();
	setAddress();
	setGender();
	setDoj();
	setWLocation();
	setManagerId();
	setDepartmentId();

	std::string managerIdString = (manager_id != NULL) ? std::to_string(manager_id) : "NULL";
	std::string departmentIdString = (department_id != NULL) ? std::to_string(department_id) : "NULL";

	std::string insertQueryEmployee = "INSERT INTO Employee (id, firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, department_id) VALUES ("
		+ std::to_string(id) + ", '" +
		firstname + "', '" +
		lastname + "', '" +
		dob + "', '" +
		mobile + "', '" +
		email + "', '" +
		address + "', '" +
		gender + "', '" +
		doj + "', '" +
		w_location + "', " +
		managerIdString + ", " +
		departmentIdString + ");";
	if (Database::getInstance().executeQuery(insertQueryEmployee)) {
		return true;
	}
	else {
		std::cout << Database::getInstance().getError() << "\n\n";
		return false;
	}
}

bool Employee::deleteEmployeeById(int eid) {

	std::string deleteQuery{};

	std::string viewEmployee = "SELECT id,firstname,lastname,email FROM Employee WHERE id = " + std::to_string(eid);

	if (!Database::getInstance().executeQueryCallback(viewEmployee,false)) {
		std::cout << Database::getInstance().getError() << std::endl;
		return false;
	}

	std::cout << "\033[36mEnter Y: to delete this Employee\nEnter N: to exit\033[0m\n";
	char confirm;
	std::cin >> confirm;

	if (confirm == 'Y' || confirm == 'y') {

		deleteQuery = "DELETE FROM Employee WHERE id = " + std::to_string(eid);

		if (Database::getInstance().executeQuery(deleteQuery)) {

			int changes = sqlite3_changes(Database::getInstance().db);

			std::cout <<"\033[32m" << changes << " row affected \033[0m\n\n";
			if (changes != 0) {
				std::cout << "\033[32mEmployee Deleted Succesfully ! \033[0m\n\n";
				Log::getInstance().Info("Employee Deleted for id : ", eid);
				return true;
			}

		}
		else {
			std::string_view errmsg = "FOREIGN KEY constraint failed";
			if (Database::getInstance().getError() == errmsg) {
				std::string err = { "Selected Employee is managing different employees, so you can not directly delete this employee !!! " };
				Database::getInstance().setError(err);
				Log::getInstance().Warn("Selected Employee is managing different employees : can not delete for id : ", eid);
			}
			std::cout << Database::getInstance().getError() << "\n\n";
			return false;
		}
	}

};

bool Employee::updateEmployee() {
	std::string updateQuery = "UPDATE Employee SET ";
	int choice;

	system("cls");

	setId();

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
			setFirstname();
			updateQuery = updateQuery + "firstname = '" + getFirstname();
			break;
		case 2:
			setLastname();
			updateQuery = updateQuery + "lastname = '" + getLastname();
			break;
		case 3:
			setDob();
			updateQuery = updateQuery + "dob = '" + getDob();
			break;
		case 4:
			setMobile();
			updateQuery = updateQuery + "mobile = '" + getMobile();
			break;
		case 5:
			setEmail();
			updateQuery = updateQuery + "email = '" + getEmail();
			break;
		case 6:
			setAddress();
			updateQuery = updateQuery + "address = '" + getAddress();
			break;
		case 7:
			setGender();
			updateQuery = updateQuery + "gender = '" + getGender();
			break;
		case 8:
			setDoj();
			updateQuery = updateQuery + "doj = '" + getDoj();
			break;
		case 9:
			setWLocation();
			updateQuery = updateQuery + "w_location = '" + getWLocation();
			break;
		case 10:
			setManagerId();
			updateQuery = updateQuery + "manager_id = " + std::to_string(manager_id);
			break;
		case 11:
			setDepartmentId();
			updateQuery = updateQuery + "department_id = " + std::to_string(department_id);
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


	updateQuery = updateQuery + "' WHERE id = " + std::to_string(id) + ";";

	if (Database::getInstance().executeQuery(updateQuery)) {
		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			std::cout << "\033[32mEmployee Updated Succesfully ! \033[0m\n\n";
			Log::getInstance().Info("Employee Updated for id : ", getId());
			return true;
		}
	}
	else
		std::cout << Database::getInstance().getError() << "\n";
	return false;
}

//void Employee::viewEmployee() {
//
//
//	std::string selectQuery{};
//	int choice;
//	system("cls");
//	bool flag = true;
//	while (flag) {
//		flag = false;
//		std::cout << "Please select a column to view an employee:\n";
//		std::cout << "1. ALL\n";
//		std::cout << "2. ID\n";
//		std::cout << "3. Firstname\n";
//		std::cout << "4. Gmail\n";
//		std::cout << "5. Go Back\n";
//
//		std::cout << "Enter your choice (1-5): ";
//
//
//		std::cin >> choice;
//		std::cout << "\n";
//
//		switch (choice) {
//		case 1:
//			system("cls");
//			selectQuery = "SELECT * FROM Employee";
//			break;
//		case 2:
//			system("cls");
//			setId();
//			selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(getId());
//			break;
//		case 3:
//			system("cls");
//			setFirstname();
//			selectQuery = "SELECT * FROM Employee WHERE firstname = '" + getFirstname() + "'";
//			break;
//		case 4:
//			system("cls");
//			setEmail();
//			selectQuery = "SELECT * FROM Employee WHERE email = '" + getEmail() + "'";
//			break;
//		case 5:
//			system("cls");
//			return;
//		default:
//			system("cls");
//			std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
//			flag = true;
//			break;
//		}
//	}
//
//	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
//		std::cout << Database::getInstance().getError() << std::endl;
//	}
//	else {
//		Log::getInstance().Info(selectQuery, " : Executed.");
//	}
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
