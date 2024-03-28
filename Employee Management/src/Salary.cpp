#include "../include/Salary.h"

using logs::Log;

void Salary::setId() {
	setAttribute("Enter Employee Id", id, validateNumeric);
}

void Salary::setBaseSalary() {
	setAttribute("Enter Base", base_salary, validateFloatNumeric);
}

void Salary::setBonus() {
	setAttribute("Enter Bonus", bonus, validateFloatNumeric);
}

void Salary::setPercentage() {
	setAttribute("Enter Increment Percentage", percentage, validateNumeric);
	percentage = (percentage / 100) + 1;
}

bool Salary::insertSalaryById(int eid) {

	setBaseSalary();
	setBonus();

	std::string insertQuery = "INSERT INTO Salary (id, base_salary, bonus) VALUES ("
		+ std::to_string(eid) + ", '" +
		std::to_string(base_salary) + "', '" +
		std::to_string(bonus) + "');";

	if (Database::getInstance().executeQuery(insertQuery)) {
		return true;
	}
	else {
		std::cout << Database::getInstance().getError() << "\n\n";
		return false;
	}

};

bool Salary::deleteSalary() {

	system("cls");

	setId();
	std::string deleteQuery = "DELETE FROM Salary WHERE id = " + std::to_string(getId());

	if (Database::getInstance().executeQuery(deleteQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout <<"\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			std::cout << "\033[32mSalary Deleted Succesfully ! \033[0m\n\n";
			Log::getInstance().Info("Salary Deleted for id : ", id);
			return true;
		}

	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
	}
	return false;

};

bool Salary::updateSalary() {

	std::string updateQuery = "UPDATE Salary SET";
	int choice;
	system("cls");

	std::cout << "Enter Salary id to update: \n";
	std::cin >> id;

	if (!Database::getInstance().checkExist("Employee", id)) {
		std::cout << "\033[33mEmployee Not exist for id: " << id << "\033[0m\n\n";
		return false;
	}

	bool flag = true;
	while (flag) {
		flag = false;

		std::cout << "Please select an attribute to update:\n";
		std::cout << "1. Base Salary\n";
		std::cout << "2. Bonus\n";
		std::cout << "3. Go Back\n";
		std::cout << "Enter your choice (1-3): ";

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			setBaseSalary();
			updateQuery += " base_salary= '" + std::to_string(getBaseSalary()) + "'";
			break;
		case 2:
			setBonus();
			updateQuery += " bonus = '" + std::to_string(getBonus()) + "'";
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
	updateQuery += " WHERE id = " + std::to_string(id) + ";";
	if (Database::getInstance().executeQuery(updateQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
		if (changes != 0) {
			std::cout << "\033[32mSalary Updated Succesfully ! \033[0m\n\n";
			Log::getInstance().Info("Salary Updated for id : ", id);
			return true;
		}

	}
	else {
		std::cout << Database::getInstance().getError() << "\n";
	}
	return false;

};

bool Salary::incrementSalary() {

	setId();
	std::string checkExistance = "SELECT id FROM Employee WHERE id = " + std::to_string(id);

	if (!Database::getInstance().checkExist("Employee", id)) {
		std::cout << "\033[33mEmployee Not exist for id: " << id << "\033[0m\n\n";
		return false;
	}
	setPercentage();

	std::string updateSalary = "UPDATE Salary SET base_salary = base_salary * " + std::to_string(getPercentage()) + " WHERE id = " + std::to_string(getId()) + "; ";

	if (!Database::getInstance().executeQuery(updateSalary)) {
		std::cout << Database::getInstance().getError();
		return false;
	}
	else {
		std::cout << "\033[32mSalary Incremented for id : " << id << "\033[0m\n\n";
		Log::getInstance().Info("Salary Incremented for id : ", id);
		return true;
	}
	return false;
}

bool Salary::viewSalary() {
	std::string selectQuery = "SELECT id,firstname,lastname,email,amount,base_salary,bonus From Employee NATURAL JOIN Salary";

	int choice;
	bool flag = true;
	while (flag) {
		system("cls");
		flag = false;
		std::cout << "Please select a column to view a Salary:\n";
		std::cout << "1. ALL\n";
		std::cout << "2. Employee Id\n";
		std::cout << "3. Order By column name\n";
		std::cout << "4. Go Back\n";

		std::cout << "Enter your choice (1-4): ";

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			break;
		case 2:
			system("cls");
			setId();
			selectQuery += " WHERE id = " + std::to_string(getId());
			break;
		case 3:
		{
			system("cls");
			int choice2;
			std::cout << "Select column to order by:\n";
			std::cout << "1. Base Salary\n";
			std::cout << "2. Amount\n";
			std::cin >> choice2;

			std::string orderByColumnName;
			switch (choice2) {
			case 1:
				orderByColumnName = "base_salary";
				break;
			case 2:
				orderByColumnName = "amount";
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
	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
		std::cout << Database::getInstance().getError() << std::endl;
		return false;
	}
	else {
		Log::getInstance().Info(selectQuery, " : Executed.");
		return true;
	}

};

void Salary::describeSalary() const
{

	if (!Database::getInstance().executeQueryCallback("pragma table_info('Salary');")) {
		std::cout << Database::getInstance().getError();
	}
	else {
		Log::getInstance().Info("Salary Described.");
	}
}

void Salary::action() {
	bool flag = true;

	while (flag) {
		std::cout << "Salary Table\n";
		std::cout << "Please select a value to perform actions:\n";
		std::cout << "1. Update\n";
		std::cout << "2. View\n";
		std::cout << "3. Describe\n";
		std::cout << "4. Increment Salary\n";
		std::cout << "5. Go Back\n";
		std::cout << "Enter your choice (1-5): ";

		int choice;

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			updateSalary();
			break;
		case 2:
			system("cls");
			viewSalary();
			break;
		case 3:
			system("cls");
			describeSalary();
			break;
		case 4:
			system("cls");
			incrementSalary();
			break;
		case 5:
			system("cls");
			flag = false;
			break;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}

