#include "pch.h"
#include "../fixers/employeeFixer.h"
#include "include/controllers/employeeController.h"


TEST_F(employeeFixer, empTest) {
	EXPECT_EQ(emp1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(emp1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(emp1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(emp1.getDob(), "02-02-2002") << "Incorrect value.";
	EXPECT_TRUE(EmployeeController::insertEmployeeController(emp1)) << "Error department insert";
	EXPECT_TRUE(EmployeeController::updateEmployeeController(emp2, "dob")) << "Error department update";
	EXPECT_TRUE(EmployeeController::deleteEmployeeController(emp1, "id")) << "Error department delete";
}




