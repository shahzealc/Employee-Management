#ifndef salary_flag
#define salary_flag

#include <iostream>
#include "database.h"


class Salary {
public:

    Salary() = default;

    int getId() const { return id; }
    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    float getBonus() const { return bonus; }

    void setId();
    void setAmount();
    void setBaseSalary();
    void setBonus();

    void insertSalary();
    void deleteSalary();
    void updateSalary();
    void viewSalary();

    void action();

private:

    int id{};
    float amount {};
    float base_salary {};
    float bonus{};
};

#endif