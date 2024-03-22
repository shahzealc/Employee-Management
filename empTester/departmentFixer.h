#pragma once
#include<gtest/gtest.h>
#include "include/Department.h"

class departmentFixer : public testing::Test {
protected:
	void SetUp() override {
		Database::getInstance().open("employee.db");
		Database::getInstance().createTables();
	}

	Department dept1{11,"HR",2,"HR Test department"};

};