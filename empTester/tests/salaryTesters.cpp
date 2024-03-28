#include "pch.h"
#include "../fixers/salaryFixer.h"
TEST_F(salaryFixer, DISABLED_salaryTest) {
	EXPECT_EQ(salary1.getId(), 1) << "Incorrect value.";
	EXPECT_EQ(salary1.getBaseSalary(), 40000) << "Incorrect value.";
	EXPECT_EQ(salary1.getBonus(), 8000) << "Incorrect value.";
	EXPECT_TRUE(salary1.insertSalaryById(2)) << "Error Salary insert";
	EXPECT_TRUE(salary1.updateSalary()) << "Error salary update";
	EXPECT_TRUE(salary1.deleteSalary()) << "Error salary delete";
}