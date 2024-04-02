#include "pch.h"
#include "include/validate.h"

TEST(ValidatorTest, ValidateAlphabeticTest) {
    EXPECT_TRUE(validateAlphabetic("test"));
    EXPECT_TRUE(validateAlphabetic("Test String"));

    EXPECT_FALSE(validateAlphabetic("123")); //false
    EXPECT_FALSE(validateAlphabetic("Test123")); //false
}

TEST(ValidatorTest, ValidateNumericTest) {
    EXPECT_TRUE(validateNumeric("123"));

    EXPECT_FALSE(validateNumeric("abc")); //false
    EXPECT_FALSE(validateNumeric("123.45")); //false
}

TEST(ValidatorTest, ValidateFloatNumericTest) {
    EXPECT_TRUE(validateFloatNumeric("123.45"));

    EXPECT_FALSE(validateFloatNumeric("abc")); //false
}

TEST(ValidatorTest, ValidateEmailTest) {
    EXPECT_TRUE(validateEmail("abcd@email.com"));

    EXPECT_FALSE(validateEmail("abc@.com")); //false
    EXPECT_FALSE(validateEmail("abc.com")); //false
}

TEST(ValidatorTest, ValidatePhoneNumberTest) {
    EXPECT_TRUE(validatePhoneNumber("1234567890"));

    EXPECT_FALSE(validatePhoneNumber("12345")); //false
    EXPECT_FALSE(validatePhoneNumber("abc")); //false
}

TEST(ValidatorTest, ValidateDateOfBirthTest) {
    EXPECT_TRUE(validateDateOfBirth("02-02-2002"));

    EXPECT_FALSE(validateDateOfBirth("2022-01-01")); //false
    EXPECT_FALSE(validateDateOfBirth("31-02-2000")); //false
}
