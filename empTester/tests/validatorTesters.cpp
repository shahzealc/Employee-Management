#include "pch.h"
#include "include/validate.h"

TEST(TestValidators, Test_validate) {
	EXPECT_TRUE(validateAlphabetic("test")) << "Not Alphabetic";
	EXPECT_TRUE(validateNumeric("123")) << "Not Numeric";
	EXPECT_TRUE(validateDateOfBirth("02-02-2002")) << "Not Valid DOB";
	EXPECT_TRUE(validateEmail("abcd@email.com")) << "Not valid Email";
}