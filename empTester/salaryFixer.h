#pragma once
#include<gtest/gtest.h>
#include "include/Salary.h"

class salaryFixer : public testing::Test {
protected:
	void SetUp() override {
		Database::getInstance().open("employee.db");
		Database::getInstance().createTables();
	}

	Salary salary1{ 1,40000,8000 };

};