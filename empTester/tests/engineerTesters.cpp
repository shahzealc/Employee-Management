#include "pch.h"
#include "../fixers/engineerFixer.h"

TEST_F(engineerFixer, engineerTest) {
	EXPECT_EQ(engineer1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(engineer1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(engineer1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(engineer1.getDob(), "02-02-2002") << "Incorrect value.";
	EXPECT_EQ(engineer1.getSpecialization(), "Test1") << "Incorrect value.";

	EXPECT_NE(engineer1.getId(), 2001); // false
	EXPECT_NE(engineer1.getFirstname(), "ZZeal"); // false
	EXPECT_NE(engineer1.getLastname(), "SShah"); // false
	EXPECT_NE(engineer1.getDob(), "01-02-2002"); // false
	EXPECT_NE(engineer1.getSpecialization(), "Test1111"); // false
}

TEST_F(engineerFixer, InsertEngineerTest) {
	EXPECT_TRUE(EmployeeController::insertEmployeeController(e1)) << "Error inserting employee";
	EXPECT_TRUE(EngineerController::insertEngineerController(engineer1, salary1)) << "Error inserting engineer";

	EXPECT_FALSE(EngineerController::insertEngineerController(engineer1, salary1)); //false
}

TEST_F(engineerFixer, UpdateEngineerTest) {
	EXPECT_TRUE(EngineerController::updateEngineerController(engineer2, "specialization")) << "Error updating engineer";

	EXPECT_FALSE(EngineerController::updateEngineerController(engineer2, "")); //false
}

TEST_F(engineerFixer, DeleteEngineerTest) {
	EXPECT_TRUE(EngineerController::deleteEngineerController(engineer1, "id")) << "Error deleting engineer";

	EXPECT_FALSE(EngineerController::deleteEngineerController(engineer1, "id")); //false
}
