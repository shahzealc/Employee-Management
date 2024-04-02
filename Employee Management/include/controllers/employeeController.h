#pragma once

#include "../Employee.h"
class Employee;

class EmployeeController {
public:
    static bool insertEmployeeController(Employee& emp);
    static bool deleteEmployeeController(Employee& emp, std::string attribute);
    static bool updateEmployeeController(Employee& emp, std::string attribute);
    static bool viewEmployeeController(Employee& emp, std::string attribute);
};