
#include "../include/Employee.h"
#include "../include/validate.h"

void Employee::insertEmployee() { 
    
//    std::cout << "Enter Employee Details:\n";
//    std::cout << "First Name: ";
//    std::cin >> firstname;
//
//    std::cout << "Last Name: ";
//    std::cin >> lastname;
//
//backDOB:
//    std::cout << "Date of Birth (DD-MM-YYYY): ";
//    std::string inputDOB;
//    std::cin >> inputDOB;
//    if (!validateDateOfBirth(inputDOB)) {
//        std::cout << "Invalid Format !!, Enter again :\n";
//        goto backDOB;
//    }
//    else {
//        dob = inputDOB;
//    }
//
//backMob:
//    std::cout << "Mobile number : ";
//    std::string inputMob;
//    std::cin >> inputMob;
//    if (!validatePhoneNumber(inputMob)) {
//        std::cout << "Invalid Format !!, Enter again :\n";
//        goto backMob;
//    }
//    else {
//        mobile = inputMob;
//    }
//
//backEmail:
//    std::cout << "Email address : ";
//    std::string inputMail;
//    std::cin >> inputMail;
//    if (!validateEmail(inputMail)) {
//        std::cout << "Invalid Format !!, Enter again :\n";
//        goto backEmail;
//    }
//    else {
//        email = inputMail;
//    }
//
//    std::cout << "Address: ";
//    std::cin.ignore();
//    std::getline(std::cin, address);
//
//    int genderChoice;
//    std::cout << "Gender (0 for Male, 1 for Female, 2 for Other): ";
//    std::cin >> genderChoice;
//    gender = static_cast<Gender>(genderChoice);
//
//    std::cout << "Date of Joining (DD-MM-YYYY): ";
//    std::cin >> doj;
//
//    std::cout << "Work Location: ";
//    std::cin >> w_location;
//
//    std::cout << "Manager ID: ";
//    std::cin >> manager_id;
//
//    std::cout << "Department ID: ";
//    std::cin >> department_id;

    //std::string insertQuery = "INSERT INTO Employee (firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, department_id) VALUES ('" +
    //    firstname + "', '" +
    //    lastname + "', '" +
    //    dob + "', '" +
    //    mobile + "', '" +
    //    email + "', '" +
    //    address + "', " +
    //    std::to_string(static_cast<int>(gender)) + ", '" +
    //    doj + "', '" +
    //    w_location + "', " +
    //    std::to_string(manager_id) + ", " +
    //    std::to_string(department_id) + ");";

    std::string insertQuery = "INSERT INTO Employee (id,firstname, lastname, dob, mobile, email, address, gender, doj, w_location,manager_id, department_id) "
        "VALUES (2,'John', 'Doe', '1990-05-15', '1234567890', 'john@example.com', '123 Main St, City, Country', 'Male', '2020-01-01','wall street', 1, 1);";

     if (db_emp.executeQuery(insertQuery))
        std::cout << "Inserted Employee Succesfully ! \n";
    else
        std::cout<<db_emp.getError()<<"\n";

};
void Employee::deleteEmployee() { return; };
void Employee::updateEmployee() { return; };
void Employee::viewEmployee() { return; };


void Employee::action() {
    bool flag = true;

    int choice;
     

    while (flag) {
        std::cout << "Employee Table\n";
        std::cout << "Please select a value to perform actions:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Update\n";
        std::cout << "4. View\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";

        std::cin >> choice;

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
