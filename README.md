# Employee Database Management System
 
- This project is an Employee Database Management System implemented in C++. It provides functionalities to manage various aspects of employee data, including departments, salaries, engineers, and managers.
 
## ER Diagram of Project
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/diagram.png)
 
## Inheritance
 
- In this project, the Employee class serves as the base class, which is inherited by the Engineer and Manager classes. This inheritance allows for the reuse of common attributes and methods defined in the Employee class while also allowing each subclass to have its own specialized attributes and methods.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/Inheritance.png)
 
## Classes
 
### 1. Employee Class (Base Class)
 
- The Employee class defines common attributes such as id, firstname, lastname, dob, mobile, email, address, gender, doj, w_location, manager_id, and department_id. It also includes methods for CRUD operations on employee records.
 
### 2. Engineer Class
 
- The Engineer class inherits from the Employee class and adds specialized attributes such as programming_language and specialization. It also includes methods specific to engineers, such as CRUD operations on engineer records.
 
### 3. Manager Class
 
- The Manager class also inherits from the Employee class and adds specialized attributes such as management_experience and project_title. It includes methods specific to managers, such as CRUD operations on manager records.
 
### 4. Department Class
 
- The Department component handles department-related data within the organization. It includes attributes such as name, manager_id, and description. The Department class provides methods for CRUD operations on department records.
 
### 5. Salary Class
 
- The Salary component is responsible for managing salary-related information for employees. It includes attributes such as base_salary, bonus, and amount, and provides methods for CRUD operations on salary records.
 
## Features of Project:
 
### 1. CRUD Operations:
 
- Efficiently manage employee data with functionalities for creating, reading, updating, and deleting records.
 
### 2. Authentication:
 
- Users(DBA) can securely log in with a maximum of 3 login attempts for added security.
 
- Future Scope: Introducing permission levels (e.g., read, read/update, read/update/delete) to enable varying levels of authorization for DBAs.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/auth.png)
 
### 3. Table Operations:
 
- Options for create, display, delete, and describe database tables.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/tableOptions.png)
 
### 4. Custom Queries:
- Option for executing personalized SQL queries to retrieve specific record with different constraints.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/customQuery.png)
 
### 5. Backup:
 
- User can take back up all existing tables into CSV format files stored in a “Backup” folder for data preservation.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/backupDeptExample.png)
 
### 6. Input Validation:
 
- Ensure data integrity by validating each input fields.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/inputValidations.png)
 
### 7. Confirmation Prompt:
 
- Confirmation prompt is displayed before deleting a record to ensure user confirmation.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/confirmDelete.png)
 
### 8. Sorting Options:
 
- Sort records based on user-selected fields in ascending or descending order.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/orderbyQuery.png)
 
### 9. Check Existence:
 
- Before adding a record, the system checks if the ID already exists. If it does, no further input is requested.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/checkID_Insert.png)
 
- Similarly, when updating a record, the system checks if the ID exists. If it doesn't, no further input is requested.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/checkID_Update.png)
 
### 10. Increment Salary:
 
- Enables salary increments for employees by applying a specified percentage to their base salary, resulting in an updated total salary.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/incrementSalary.png)
 
### 11. Export to CSV:
 
- After viewing a record, you have the option to save it in CSV format by specifying a file name. The saved file is stored in the 'exports' folder.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/exportQuery.png)
 
### 12. Logging System:
 
- Each and every events are logged in “databaseLog.txt” file that helps to track and monitors the errors, warnings and information.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/logs.png)
 
## GTest Integration
 
- Integrated Google Test (GTest) for unit testing of each functionality to ensure robustness and reliability.
 
![diagram](https://github.com/shahzealc/Employee-Management/blob/master/Employee%20Management/screenshots/GTest.png)
 
## Future Scope
 
- Introducing permission levels (e.g., read, read/update, read/update/delete) to enable varying levels of authorization for DBAs.
- Enable the generation of PDF documents after viewing specific records, facilitating easy storage and printing of important information.
 
 
## Requirements
 
- C++ compiler that supports C++17 standard.
- SQLite database library.
- Standard C++ libraries.

