#include "pch.h"
#include "../fixers/departmentFixer.h"
#include "include/controllers/departmentController.h"

TEST_F(departmentFixer, AttributeDepartmentTest) {
    EXPECT_EQ(dept1.getId(), 10) << "Incorrect value";
    EXPECT_EQ(dept1.getName(), "HR") << "Incorrect value";
    EXPECT_EQ(dept1.getManagerId(), 2) << "Incorrect value";
    EXPECT_EQ(dept1.getDescription(), "HR Test department") << "Incorrect value";

    EXPECT_NE(dept1.getId(), 11); // false
    EXPECT_NE(dept1.getName(), "test"); // false
    EXPECT_NE(dept1.getManagerId(), 1); // false
    EXPECT_NE(dept1.getDescription(), "Finance Test department"); // false
}

TEST_F(departmentFixer, InsertDepartmentTest) {
    EXPECT_TRUE(DepartmentController::insertDepartmentController(dept1)) << "Error inserting department.";

    EXPECT_FALSE(DepartmentController::insertDepartmentController(dept1)); //false
}

TEST_F(departmentFixer, UpdateDepartmentTest) {
    EXPECT_TRUE(DepartmentController::updateDepartmentController(dept2, "name")) << "Error updating department.";

    EXPECT_FALSE(DepartmentController::updateDepartmentController(dept2, "NULL")); // false
}

TEST_F(departmentFixer, DeleteDepartmentTest) {
    EXPECT_TRUE(DepartmentController::deleteDepartmentController(dept1, "id")) << "Error deleting department.";

    EXPECT_FALSE(DepartmentController::deleteDepartmentController(dept2, "NULL")); // false
}