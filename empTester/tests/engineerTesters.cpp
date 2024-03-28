
#include "pch.h"
#include "../fixers/engineerFixer.h"
TEST_F(engineerFixer, engineerTest) {
	EXPECT_EQ(engineer1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(engineer1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(engineer1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(engineer1.getDob(), "02-02-2002") << "Incorrect value.";
	EXPECT_EQ(engineer1.getSpecialization(), "C++") << "Incorrect value.";
}