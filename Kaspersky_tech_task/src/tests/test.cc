#include <gtest/gtest.h>

#include "../scanner.h"

TEST(ScannerTest, success) {
    int test_argc = 7;
    const char* test_argv[] = {
        "task.exe",
        "--base",
        "..\\src\\hash_table.csv",
        "--log",
        "malicious.log",
        "--path",
        "..\\root_dir"
    };
    HashCheck res(test_argc, test_argv);
    res.scan();
    EXPECT_EQ(res.get_file_errors(), 0);
    EXPECT_EQ(res.get_count_all(), 5);
    EXPECT_EQ(res.get_count_malicious(), 2);
}

TEST(ScannerTest, fail_1) {
    int test_argc = 1;
    const char* test_argv[] = {
        "task.exe"
    };
    EXPECT_THROW(HashCheck res(test_argc, test_argv), std::invalid_argument);
}

TEST(ScannerTest, fail_2) {
    int test_argc = 7;
    const char* test_argv[] = {
        "task.exe",
        "--base",
        "error",
        "--log",
        "malicious.log",
        "--path",
        "..\\root_dir"
    };
    HashCheck res(test_argc, test_argv);
    EXPECT_THROW(res.scan(), BaseError);
}

TEST(ScannerTest, fail_3) {
    int test_argc = 7;
    const char* test_argv[] = {
        "task.exe",
        "--base",
        "..\\src\\hash_table.csv",
        "--log",
        "malicious.log",
        "--path",
        "error"
    };
    HashCheck res(test_argc, test_argv);
    EXPECT_THROW(res.scan(), std::filesystem::__cxx11::filesystem_error);
}