#include "pch.h"
#include "../fixers/managerFixer.h"
TEST_F(managerFixer, managerTest) {
	EXPECT_EQ(manager1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(manager1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(manager1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(manager1.getDob(), "02-02-2002") << "Incorrect value.";
	EXPECT_EQ(manager1.getManagementExperience(), 3) << "Incorrect value.";
}