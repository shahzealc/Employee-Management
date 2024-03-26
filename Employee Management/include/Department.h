#ifndef dept_flag
#define dept_flag

#include <iostream>
#include <string>
#include "database.h"
#include "log.h"
#include "validate.h"
#include "attributeHelper.h"

class Department {
public:
    Department() = default;
    Department(int dept_id, const std::string& dept_name, int mgr_id, const std::string& dept_description)
        : id(dept_id), name(dept_name), manager_id(mgr_id), description(dept_description) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getManagerId() const { return manager_id; }
    std::string getDescription() const { return description; }

    void setId();
    void setName();
    void setManagerId();
    void setDescription();

    void insertDepartment();
    void deleteDepartment();
    void updateDepartment();
    void viewDepartment();

    void describeDepartment() const;

    void action();

private:

    int id{};
    std::string name{};
    int manager_id{};
    std::string description{};
};


#endif