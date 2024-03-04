#include "../include/Department.h"

void Department::insertDepartment() {};
void Department::deleteDepartment() {};
void Department::updateDepartment() {};
void Department::viewDepartment() {};


void Department::action() {
    bool flag = true;

    std::cout << "Department Table\n";
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
            insertDepartment();
            break;
        case 2:
            deleteDepartment();
            break;
        case 3:
            updateDepartment();
            break;
        case 4:
            viewDepartment();
            break;
        case 5: // Exit
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
}
