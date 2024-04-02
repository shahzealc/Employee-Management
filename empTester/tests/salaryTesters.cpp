#include "pch.h"
#include "../fixers/salaryFixer.h"

TEST_F(salaryFixer, AttributeSalaryTest) {
    EXPECT_EQ(salary1.getId(), 1) << "Incorrect id insertion.";
    EXPECT_FLOAT_EQ(salary1.getBaseSalary(), 25000.0) << "Incorrect base salary insertion.";
    EXPECT_FLOAT_EQ(salary1.getBonus(), 10000.0) << "Incorrect bonus insertion.";

    EXPECT_NE(salary1.getId(), 2); //false
    EXPECT_NE(salary1.getBaseSalary(), 1000); //false
    EXPECT_NE(salary1.getBonus(), 10); //false
}

TEST_F(salaryFixer, UpdateSalaryTest) {
    EXPECT_TRUE(SalaryController::updateSalaryController(salary1, "base_salary")) << "Error in updating salary.";

    EXPECT_FALSE(SalaryController::updateSalaryController(salary1, "NULL")); //false
}

TEST_F(salaryFixer, IncrementSalaryTest) {
    EXPECT_TRUE(SalaryController::incrementSalaryController(salary1)) << "Error in incrementing salary.";
}
