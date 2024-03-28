#ifndef salary_flag
#define salary_flag

#include <iostream>
#include "database.h"
#include "log.h"
#include "validate.h"
#include "attributeHelper.h"

class Salary {
public:

    Salary() = default;
    Salary(int id,float base ,float bonus):id(id),base_salary(base),bonus(bonus){}

    int getId() const { return id; }
    float getBaseSalary() const { return base_salary; }
    float getBonus() const { return bonus; }
    float getPercentage() const { return percentage; }

    void setId();
    void setBaseSalary();
    void setBonus();
    void setPercentage();

    bool insertSalaryById(int id);
    bool deleteSalary();
    bool updateSalary();
    bool viewSalary();

    void describeSalary() const;

    bool incrementSalary();

    void action();

private:

    int id{};
    float percentage{};
    float base_salary {};
    float bonus{};
};

#endif