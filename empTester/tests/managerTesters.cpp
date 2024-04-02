#include "pch.h"
#include "../fixers/managerFixer.h"

TEST_F(managerFixer, managerTest) {
	EXPECT_EQ(manager1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(manager1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(manager1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(manager1.getDob(), "02-02-2002") << "Incorrect value.";
	EXPECT_EQ(manager1.getManagementExperience(), 3) << "Incorrect value.";
	
	EXPECT_NE(manager1.getId(), 2001); //false
	EXPECT_NE(manager1.getFirstname(), "ZZeal"); //false
	EXPECT_NE(manager1.getLastname(), "SShah"); //false
	EXPECT_NE(manager1.getDob(), "01-02-2002"); //false
	EXPECT_NE(manager1.getManagementExperience(), 22); //false
}

TEST_F(managerFixer, InsertManagerTest) {
	EXPECT_TRUE(EmployeeController::insertEmployeeController(e1));
	EXPECT_TRUE(ManagerController::insertManagerController(manager1, salary1));

	EXPECT_FALSE(ManagerController::insertManagerController(manager1, salary1)); //false

}

TEST_F(managerFixer, UpdateManagerTest) {
	EXPECT_TRUE(ManagerController::updateManagerController(manager2, "project_title"));

	EXPECT_FALSE(ManagerController::updateManagerController(manager2, "NULL")); //false
}

TEST_F(managerFixer, DeleteManagerTest) {
	EXPECT_TRUE(ManagerController::deleteManagerController(manager1, "id"));

	EXPECT_FALSE(ManagerController::deleteManagerController(manager1, "NULL")); //false
}
