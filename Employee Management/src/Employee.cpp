
#include "../include/Employee.h"

void Employee::insertEmployee() { return; };
void Employee::deleteEmployee() { return; };
void Employee::updateEmployee() { return; };
void Employee::viewEmployee() { return; };


void Employee::action() {
    bool flag = true;

    std::cout << "Employee Table\n";
    std::cout << "Please select a value to perform actions:\n";
    std::cout << "1. Insert\n";
    std::cout << "2. Delete\n";
    std::cout << "3. Update\n";
    std::cout << "4. View\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice (1-5): ";

    int choice;
    std::cin >> choice;

    while (flag) {
        switch (choice) {
        case 1:
            insertEmployee();
            break;
        case 2:
            deleteEmployee();
            break;
        case 3:
            updateEmployee();
            break;
        case 4:
            viewEmployee();
            break;
        case 5: 
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
}
