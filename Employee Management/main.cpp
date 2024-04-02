#include <conio.h>
#include <iostream>
#include<filesystem>
#include "include/database.h"
#include "include/askPrompt.h"
#include "include/log.h"
#include "include/auth.h"

using logs::Log;

int main() {

	//Authenticating user
	if (Auth::authUser()) {

		std::filesystem::path dbPath = "employee.db";

		if (!Database::getInstance().open(dbPath)) {
			std::cout << "Error opening database: " << Database::getInstance().getError() << "\n";
		}
		else {
			Log::getInstance().Info("Database Opened.");
			system("cls");
			askPromptMain();
		}
		Database::getInstance().close();

	}
	return 0;

}

