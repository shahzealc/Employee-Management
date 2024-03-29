#include "pch.h"
#include "../fixers/departmentFixer.h"
#include "include/controllers/departmentController.h"

TEST_F(departmentFixer, departmentTest) {
	EXPECT_EQ(dept1.getId(), 10) << "Incorrect value.";
	EXPECT_EQ(dept1.getName(), "HR") << "Incorrect value.";
	EXPECT_EQ(dept1.getManagerId(), 2) << "Incorrect value.";
	EXPECT_EQ(dept1.getDescription(), "HR Test department") << "Incorrect value.";
	EXPECT_TRUE(DepartmentController::insertDepartmentController(dept1)) << "Error department insert";
	EXPECT_TRUE(DepartmentController::updateDepartmentController(dept2,"name")) << "Error department update";
	EXPECT_TRUE(DepartmentController::deleteDepartmentController(dept1, "id")) << "Error department delete";
}