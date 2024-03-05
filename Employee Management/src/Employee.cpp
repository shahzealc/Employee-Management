
#include "../include/Employee.h"
#include "../include/validate.h"

void Employee::setId() {
    std::cout << "ID: ";
    std::cin >> id;
}
void Employee::setFirstname() {
    std::cout << "First Name: ";
    std::cin >> firstname;
}
void Employee::setLastname() {
    std::cout << "Last Name: ";
    std::cin >> lastname;
}
void Employee::setDob() {
    std::cout << "Date of Birth (DD-MM-YYYY): ";
    std::string inputDOB;
    std::cin >> inputDOB;
    if (!validateDateOfBirth(inputDOB)) {
        std::cout << "Invalid Format !!, Enter again :\n";
        Employee::setDob();
    }
    else {
        dob = inputDOB;
    }
}
void Employee::setMobile() {
    std::cout << "Mobile number : ";
    std::string inputMob;
    std::cin >> inputMob;
    if (!validatePhoneNumber(inputMob)) {
        std::cout << "Invalid Format !!, Enter again :\n";
        Employee::setMobile();
    }
    else {
        mobile = inputMob;
    }
}
void Employee::setEmail() {
    std::cout << "Email address : ";
    std::string inputMail;
    std::cin >> inputMail;
    if (!validateEmail(inputMail)) {
        std::cout << "Invalid Format !!, Enter again :\n";
        Employee::setEmail();
    }
    else {
        email = inputMail;
    }
}
void Employee::setAddress() {
    std::cout << "Address: ";
    std::cin.ignore();
    std::getline(std::cin, address);
}
void Employee::setGender() {
    std::cout << "Gender (Male, Female, Other): ";
    std::cin >> gender;
}
void Employee::setDoj() {
    std::cout << "Date of Joining (DD-MM-YYYY): ";
    std::string inputDOJ;
    std::cin >> inputDOJ;
    if (!validateDateOfBirth(inputDOJ)) {
        std::cout << "Invalid Format !!, Enter again :\n";
        Employee::setDoj();
    }
    else {
        doj = inputDOJ;
    }
}
void Employee::setWLocation() {
    std::cout << "Work Location: ";
    std::cin >> w_location;
}
void Employee::setManagerId() {
    std::cout << "Manager ID: ";
    std::cin >> manager_id;
}
void Employee::setDepartmentId() {
    std::cout << "Department ID: ";
    std::cin >> department_id;
}

void Employee::insertEmployee() { 
    
    std::cout << "Enter Employee Details:\n";

    setId();
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

    std::string insertQuery = "INSERT INTO Employee (id, firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, department_id) VALUES ("
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
        std::to_string(manager_id) + ", " +
        std::to_string(department_id) + ");";
 
     if (db_emp.executeQuery(insertQuery))
        std::cout << "Inserted Employee Succesfully ! \n";
    else
        std::cout<<db_emp.getError()<<"\n";

};
void Employee::deleteEmployee() { 
    
    std::string deleteQuery{};
    bool flag = true;
    int choice;
    while (flag) {

        std::cout << "Please select a column to delete an employee:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Firstname\n";
        std::cout << "3. Gmail\n";
        std::cout << "4. Exit\n";

        std::cout << "Enter your choice (1-4): ";


        std::cin >> choice;


        switch (choice) {
        case 1:
            setId();
            deleteQuery = "DELETE FROM Employee WHERE id = " + std::to_string(getId());
            if (db_emp.executeQuery(deleteQuery))
                std::cout << "Employee Deleted Succesfully ! \n";
            else
                std::cout << db_emp.getError() << "\n";
            break;
        case 2:
            setFirstname();
            deleteQuery = "DELETE FROM Employee WHERE firstname = '" + getFirstname()+ "'";
            if (db_emp.executeQuery(deleteQuery))
                std::cout << "Employee Deleted Succesfully ! \n";
            else
                std::cout << db_emp.getError() << "\n";
            break;

        case 3:
            setEmail();
            deleteQuery = "DELETE FROM Employee WHERE email = '" + getEmail() + "'";
            if (db_emp.executeQuery(deleteQuery))
                std::cout << "Employee Deleted Succesfully ! \n";
            else
                std::cout << db_emp.getError() << "\n";
            break;

        case 4:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }
    }

};

void Employee::updateEmployee() { return; };

void Employee::viewEmployee() { 


    std::string selectQuery{};
    bool flag = true;
    int choice;
    while (flag) {

        std::cout << "Please select a column to view an employee:\n";
        std::cout << "1. ALL\n";
        std::cout << "2. ID\n";
        std::cout << "3. Firstname\n";
        std::cout << "4. Gmail\n";
        std::cout << "5. Exit\n";

        std::cout << "Enter your choice (1-5): ";


        std::cin >> choice;


        switch (choice) {
        case 1:
            selectQuery = "SELECT * FROM Employee";

            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;
        case 2:
            setId();
            selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(getId());
            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;
        case 3:
            setFirstname();
            selectQuery = "SELECT * FROM Employee WHERE firstname = '" + getFirstname() + "'";
            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;

        case 4:
            setEmail();
            selectQuery = "SELECT * FROM Employee WHERE email = '" + getEmail() + "'";
            if (!db_emp.executeQueryCallback(selectQuery)) {
                std::cerr << "Error executing query: " << db_emp.getError() << std::endl;
            }
            break;

        case 5:
            flag = false;
            break;
        default:
            std::cerr << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }
    }
    


};


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
