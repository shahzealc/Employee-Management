#include "pch.h"
#include "../fixers/employeeFixer.h"
#include "include/controllers/employeeController.h"


TEST_F(employeeFixer, AttributeEmployeeTest) {
	EXPECT_EQ(emp1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(emp1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(emp1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(emp1.getDob(), "02-02-2002") << "Incorrect value.";

	EXPECT_NE(emp1.getId(), 2001); // false
	EXPECT_NE(emp1.getFirstname(), "ZZeal"); // false
	EXPECT_NE(emp1.getLastname(), "SShah"); // false
	EXPECT_NE(emp1.getDob(), "01-02-2002"); // false
}

TEST_F(employeeFixer, InsertEmployeeTest) {
	EXPECT_TRUE(EmployeeController::insertEmployeeController(emp1)) << "Error Employee insert";
	EXPECT_FALSE(EmployeeController::insertEmployeeController(emp1)); //false
}

TEST_F(employeeFixer, UpdateEmployeeTest) {
	EXPECT_TRUE(EmployeeController::updateEmployeeController(emp2, "dob")) << "Error Employee update";
	EXPECT_FALSE(EmployeeController::updateEmployeeController(emp2, "NULL")); //false
}

TEST_F(employeeFixer, DeleteEmployeeTest) {
	EXPECT_TRUE(EmployeeController::deleteEmployeeController(emp1, "id")) << "Error Employee delete";
	EXPECT_FALSE(EmployeeController::deleteEmployeeController(emp1, "id")); // false
}



