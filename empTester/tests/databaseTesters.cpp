#include "pch.h"
#include "include/database.h"

TEST(TestDB, TestOpenDatabase) {
    EXPECT_TRUE(Database::getInstance().open("employeeTest.db")) << "Database open error";
}

TEST(TestDB, TestCreateTables) {
    EXPECT_TRUE(Database::getInstance().createTables()) << "Table creating error";
}

TEST(TestDB, TestExecuteQuery) {
    EXPECT_TRUE(Database::getInstance().executeQuery("SELECT * FROM Employee;")) << "Execute Query error";

    EXPECT_FALSE(Database::getInstance().executeQuery("SELECT abc from emp;")); //false
}

TEST(TestDB, TestExportToCSV) {
    EXPECT_TRUE(Database::getInstance().export_to_csv("SELECT * FROM Department", "Department.csv")) << "Export to CSV error";
}

TEST(TestDB, TestExportDatabase) {
    EXPECT_TRUE(Database::getInstance().exportDatabase()) << "Export database error";
}