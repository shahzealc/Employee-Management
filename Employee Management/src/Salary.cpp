#include "../include/Salary.h"
#include "../include/log.h"
using logs::Log;

void Salary::setId() {
	std::cout << "Enter Employee Id: ";
	std::cin >> id;
}
void Salary::setBaseSalary() {
	std::cout << "Enter Base: ";
	std::cin >> base_salary;
}
void Salary::setBonus() {
	std::cout << "Enter Bonus: ";
	std::cin >> bonus;
}
void Salary::setPercentage() {
	std::cout << "Enter Increment Percentage: ";
	std::cin >> percentage;
	percentage = (percentage / 100) + 1;
}

void Salary::insertSalary() {

	system("cls");
	std::cout << "Insert Salary Details:\n";
	setId();

	setBaseSalary();
	setBonus();

	std::string insertQuery = "INSERT INTO Salary (id, base_salary, bonus) VALUES ("
		+ std::to_string(id) + ", '" +
		std::to_string(base_salary) + "', '" +
		std::to_string(bonus) + "');";

	if (Database::getInstance().executeQuery(insertQuery)) {

		std::cout << "Inserted Salary Succesfully ! \n\n";
		Log::getInstance().Info("Salary Inserted for id : ",id);
	}
	else
		std::cout << Database::getInstance().getError() << "\n";

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

	std::string updateQuery{};
	int choice;
	system("cls");
	std::cout << "Enter Salary id to update: \n";
	std::cin >> id;


	std::cout << "Please select an attribute to update:\n";
	std::cout << "1. Base Salary\n";
	std::cout << "2. Bonus\n";
	std::cout << "3. Exit\n";
	std::cout << "Enter your choice (1-3): ";

	std::cin >> choice;
	std::cout << "\n";

	switch (choice) {
	case 1:
		setBaseSalary();
		updateQuery = "UPDATE Salary SET base_salary= '" + std::to_string(getBaseSalary()) + "' WHERE id = " + std::to_string(id);
		break;
	case 2:
		setBonus();
		updateQuery = "UPDATE Salary SET bonus = '" + std::to_string(getBonus()) + "' WHERE id = " + std::to_string(id);
		break;
	case 3:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		updateSalary();
		break;
	}

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
	system("cls");
	std::cout << "Please select a column to view a Salary:\n";
	std::cout << "1. ALL\n";
	std::cout << "2. Employee Id\n";
	std::cout << "3. Exit\n";

	std::cout << "Enter your choice (1-3): ";

	std::cin >> choice;
	std::cout << "\n";

	switch (choice) {
	case 1:
		selectQuery = "SELECT id,firstname,lastname,email,amount,base_salary,bonus From Employee NATURAL JOIN Salary";
		break;
	case 2:
		setId();
		selectQuery = "SELECT id,firstname,lastname,email,amount,base_salary,bonus From Employee NATURAL JOIN Salary WHERE id = " + std::to_string(getId());
		break;
	case 3:
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		viewSalary();
		break;
	}

	if (!Database::getInstance().executeQueryCallback(selectQuery)) {
		std::cout << Database::getInstance().getError() << std::endl;
	}
	else {
		Log::getInstance().Info(selectQuery," : Executed.");
	}

};

void Salary::describeSalary()
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
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. View\n";
		std::cout << "4. Describe\n";
		std::cout << "5. Increment Salary\n";
		std::cout << "6. Import from CSV\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter your choice (1-6): ";

		int choice;
		
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1:
			insertSalary();
			break;
		case 2:
			updateSalary();
			break;
		case 3:
			viewSalary();
			break;
		case 4:
			describeSalary();
			break;
		case 5:
			incrementSalary();
			break;
		case 6:
			Database::getInstance().import_from_csv("Salary", "backup/Salary.csv");
			break;
		case 7:
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
