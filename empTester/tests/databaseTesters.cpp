#include "pch.h"
#include "include/database.h"
TEST(TestDB, Test_DB) {
	EXPECT_TRUE(Database::getInstance().open("employee.db")) << "Database open error";
	EXPECT_TRUE(Database::getInstance().createTables()) << "Table creating error";
	EXPECT_TRUE(Database::getInstance().executeQuery("select * from Employee;")) << "Execute Query error";
	EXPECT_NO_THROW(Database::getInstance().export_to_csv("select * from Department", "department.csv")) << "Execute Query error";
}
