#include "../include/Salary.h"

using logs::Log;

void Salary::setId() {
	setAttribute("Enter Employee Id", id, validateNumeric);
}

void Salary::setBaseSalary() {
	setAttribute("Enter Base", base_salary, validateNumeric);
}

void Salary::setBonus() {
	setAttribute("Enter Bonus", bonus, validateNumeric);
}

void Salary::setPercentage() {
	setAttribute("Enter Increment Percentage", percentage, validateNumeric);
	percentage = (percentage / 100) + 1;
}

[[nodiscard]] std::string Salary::insertSalaryById(int id) {

	setBaseSalary();
	setBonus();

	std::string insertQuery = "INSERT INTO Salary (id, base_salary, bonus) VALUES ("
		+ std::to_string(id) + ", '" +
		std::to_string(base_salary) + "', '" +
		std::to_string(bonus) + "');";

	return insertQuery;

};

void Salary::deleteSalary() {

	system("cls");

	setId();
	std::string deleteQuery = "DELETE FROM Salary WHERE id = " + std::to_string(getId());

	if (Database::getInstance().executeQuery(deleteQuery)) {

		int changes = sqlite3_changes(Database::getInstance().db);

		std::cout << changes << " row affected \n\n";
		if (changes != 0) {
			std::cout << "Salary Deleted Succesfully ! \n\n";
			Log::getInstance().Info("Salary Deleted for id : ",id);
		}

	}
	else
		std::cout << Database::getInstance().getError() << "\n";

};

void Salary::updateSalary() {

	std::string updateQuery = "UPDATE Salary SET";
	int choice;
	system("cls");
	bool flag = true;
	while (flag) {
		std::cout << "Enter Salary id to update: \n";
		std::cin >> id;
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
			return;
		default:
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
			std::cout << "Salary Updated Succesfully ! \n\n";
			Log::getInstance().Info("Salary Updated for id : ", id);
		}

	}
	else
		std::cout << Database::getInstance().getError() << "\n";

};

void Salary::viewSalary() {
	std::string selectQuery{};

	int choice;
	bool flag = true;
	while (flag) {
		system("cls");
		flag = false;
		std::cout << "Please select a column to view a Salary:\n";
		std::cout << "1. ALL\n";
		std::cout << "2. Employee Id\n";
		std::cout << "3. Go Back\n";

		std::cout << "Enter your choice (1-3): ";

		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			system("cls");
			selectQuery = "SELECT id,firstname,lastname,email,amount,base_salary,bonus From Employee NATURAL JOIN Salary";
			break;
		case 2:
			system("cls");
			setId();
			selectQuery = "SELECT id,firstname,lastname,email,amount,base_salary,bonus From Employee NATURAL JOIN Salary WHERE id = " + std::to_string(getId());
			break;
		case 3:
			system("cls");
			return;
		default:
			system("cls");
			std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
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
		Log::getInstance().Info(selectQuery," : Executed.");
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

void Salary::incrementSalary() {

	setId();
	setPercentage();

	std::string updateSalary = "UPDATE Salary SET base_salary = base_salary * " + std::to_string(getPercentage()) + " WHERE id = " + std::to_string(getId()) + "; ";

	if (!Database::getInstance().executeQuery(updateSalary)) {
		std::cout << Database::getInstance().getError();
	}
	else {
		Log::getInstance().Info("Salary Incremented for id : ",id);
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
			std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}

