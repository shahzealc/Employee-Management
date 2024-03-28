#include "pch.h"
#include "../fixers/employeeFixer.h"


TEST_F(employeeFixer, empTest) {
	EXPECT_EQ(emp1.getId(), 1001) << "Incorrect value.";
	EXPECT_EQ(emp1.getFirstname(), "Zeal") << "Incorrect value.";
	EXPECT_EQ(emp1.getLastname(), "Shah") << "Incorrect value.";
	EXPECT_EQ(emp1.getDob(), "02-02-2002") << "Incorrect value.";
}




