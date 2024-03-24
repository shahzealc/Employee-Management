#include "pch.h"
#include "include/database.h"
#include "include/validate.h"
#include "employeeFixer.h"
#include "managerFixer.h"
#include "engineerFixer.h"
#include "departmentFixer.h"
#include "salaryFixer.h"


TEST(TestValidators, DISABLED_Test_validate) {
	EXPECT_TRUE(validateAlphabetic("sdfsf")) << "Not Alphabetic";
	EXPECT_TRUE(validateAlphabetic("12123")) << "Not Alphabetic";
	EXPECT_TRUE(validateNumeric("sdfsf")) << "Not Numeric";
	EXPECT_TRUE(validateNumeric("123131231")) << "Not Numeric";
	EXPECT_TRUE(validateDateOfBirth("02-02-2002")) << "Not Valid DOB";
	EXPECT_TRUE(validateEmail("sdfsf")) << "Not valid Email";
	EXPECT_TRUE(validateEmail("abcd@email.com")) << "Not valid Email";
}

TEST(TestDB, DISABLED_Test_DB) {
	EXPECT_TRUE(Database::getInstance().open("employee.db")) << "Database open error";
	EXPECT_TRUE(Database::getInstance().createTables()) << "Table creating error";
	EXPECT_FALSE(Database::getInstance().executeQuery("employee.db")) << "Execute Query error";
	EXPECT_TRUE(Database::getInstance().executeQuery("select * from employee;")) << "Execute Query error";
	EXPECT_NO_THROW(Database::getInstance().export_to_csv("Department","department.csv")) << "Execute Query error";

}

TEST_F(employeeFixer, DISABLED_empTest) {
	EXPECT_EQ(emp1.getId(), 1001)<<"Incorrect value.";
	EXPECT_EQ(emp1.getFirstname(), "Zeal")<<"Incorrect value.";
	EXPECT_EQ(emp1.getLastname(), "Shah")<<"Incorrect value.";
	EXPECT_EQ(emp1.getDob(), "02-02-2002")<<"Incorrect value.";
}

TEST_F(managerFixer, DISABLED_managerTest) {
	EXPECT_EQ(manager1.getId(), 1001)<<"Incorrect value.";
	EXPECT_EQ(manager1.getFirstname(), "Zeal")<<"Incorrect value.";
	EXPECT_EQ(manager1.getLastname(), "Shah")<<"Incorrect value.";
	EXPECT_EQ(manager1.getDob(), "02-02-2002")<<"Incorrect value.";
	EXPECT_EQ(manager1.getManagementExperience(),3)<<"Incorrect value.";
}

TEST_F(engineerFixer, engineerTest) {
	EXPECT_EQ(engineer1.getId(), 1001)<<"Incorrect value.";
	EXPECT_EQ(engineer1.getFirstname(), "Zeal")<<"Incorrect value.";
	EXPECT_EQ(engineer1.getLastname(), "Shah")<<"Incorrect value.";
	EXPECT_EQ(engineer1.getDob(), "02-02-2002")<<"Incorrect value.";
	EXPECT_EQ(engineer1.getSpecialization(), "C++")<<"Incorrect value.";
}

TEST_F(departmentFixer, DISABLED_departmentTest) {
	EXPECT_EQ(dept1.getId(), 11)<<"Incorrect value.";
	EXPECT_EQ(dept1.getName(), "HR")<<"Incorrect value.";
	EXPECT_EQ(dept1.getManagerId(), 2)<<"Incorrect value.";
	EXPECT_EQ(dept1.getDescription(), "HR Test department")<<"Incorrect value.";
	EXPECT_NO_THROW(dept1.insertDepartment()) << "Throwed from department insert";
	EXPECT_NO_THROW(dept1.deleteDepartment())<<"Throwed from department delete";
}

TEST_F(salaryFixer, DISABLED_salaryTest) {
	EXPECT_EQ(salary1.getId(), 1)<<"Incorrect value.";
	EXPECT_EQ(salary1.getBaseSalary(), 40000)<<"Incorrect value.";
	EXPECT_EQ(salary1.getBonus(), 8000)<<"Incorrect value.";
}