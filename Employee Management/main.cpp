
#include <conio.h>
#include <iostream>
#include<filesystem>
#include "include/database.h"
#include "include/askPrompt.h"

int main() {

	std::filesystem::path dbPath = "employee.db";

	if (!Database::getInstance().open(dbPath)) {
		std::cerr << "Error opening database: " << Database::getInstance().getError() << std::endl;
		return 1;
	}

	askPromptMain();

	Database::getInstance().close();

	return 0;
}
