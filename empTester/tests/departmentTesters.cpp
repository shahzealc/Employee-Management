#include "pch.h"
#include "../fixers/departmentFixer.h"
TEST_F(departmentFixer, DISABLED_departmentTest) {
	EXPECT_EQ(dept1.getId(), 10) << "Incorrect value.";
	EXPECT_EQ(dept1.getName(), "HR") << "Incorrect value.";
	EXPECT_EQ(dept1.getManagerId(), 2) << "Incorrect value.";
	EXPECT_EQ(dept1.getDescription(), "HR Test department") << "Incorrect value.";
	EXPECT_TRUE(dept1.insertDepartment()) << "Error department insert";
	EXPECT_TRUE(dept1.updateDepartment()) << "Error department update";
	EXPECT_TRUE(dept1.deleteDepartment()) << "Error department delete";
}