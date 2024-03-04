
#pragma once

#include <iostream>
#include <string>
#include "database.h"

enum class Gender { Male, Female, Other };

class Employee {

public:
    Employee() = default;
    Employee(const Database& db) {
        db_emp = db;
    }

    
    int getId() const { return id; }
    std::string getFirstname() const { return firstname; }
    std::string getLastname() const { return lastname; }
    std::string getDob() const { return dob; }
    std::string getMobile() const { return mobile; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    Gender getGender() const { return gender; }
    std::string getDoj() const { return doj; }
    std::string getWLocation() const { return w_location; }
    int getManagerId() const { return manager_id; }
    int getDepartmentId() const { return department_id; }

    void setId(int ID) { id = ID; }
    void setFirstname(const std::string& Firstname) { firstname = Firstname; }
    void setLastname(const std::string& Lastname) { lastname = Lastname; }
    void setDob(const std::string& Dob) { dob = Dob; }
    void setMobile(const std::string& Mobile) { mobile = Mobile; }
    void setEmail(const std::string& Email) { email = Email; }
    void setAddress(const std::string& Address) { address = Address; }
    void setGender(Gender Gender) { gender = Gender; }
    void setDoj(const std::string& Doj) { doj = Doj; }
    void setWLocation(int WLocation) { w_location = WLocation; }
    void setManagerId(int ManagerId) { manager_id = ManagerId; }
    void setDepartmentId(int DepartmentId) { department_id = DepartmentId; }

    void insertEmployee();
    void deleteEmployee();
    void updateEmployee();
    void viewEmployee();

    void action();

private:
    Database db_emp;
    int id{};
    std::string firstname{};
    std::string lastname{};
    std::string dob{};
    std::string mobile{};
    std::string email{};
    std::string address{};
    Gender gender{};
    std::string doj{};
    std::string w_location{};
    int manager_id{};
    int department_id{};
};
