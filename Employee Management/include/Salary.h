#ifndef salary_flag
#define salary_flag

#include <iostream>
#include "database.h"


class Salary {
public:

    Salary() = default;

    int getId() const { return id; }
    float getBaseSalary() const { return base_salary; }
    float getBonus() const { return bonus; }
    float getPercentage() const { return percentage; }

    void setId();
    void setBaseSalary();
    void setBonus();
    void setPercentage();

    void insertSalary();
    void deleteSalary();
    void updateSalary();
    void viewSalary();

    void describeSalary();

    void incrementSalary();

    void action();

private:

    int id{};
    float percentage{};
    float base_salary {};
    float bonus{};
};

#endif