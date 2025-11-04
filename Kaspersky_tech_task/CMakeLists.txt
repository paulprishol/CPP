cmake_minimum_required(VERSION 3.15)
project(FileScanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(scanner SHARED
    src/scanner.cc
    src/scanner.h
)
if (WIN32)
    target_compile_definitions(scanner PRIVATE "_CRT_SECURE_NO_WARNINGS")
endif()

find_package(OpenSSL REQUIRED)
target_link_libraries(scanner PRIVATE OpenSSL::SSL OpenSSL::Crypto)

add_executable(task
    src/main.cc
)

target_link_libraries(task PRIVATE scanner)

if (MINGW)
    target_link_libraries(task PRIVATE stdc++fs)
    target_link_libraries(scanner PRIVATE stdc++fs)
endif()

enable_testing()
find_package(GTest REQUIRED)

add_executable(scanner_tests
    src/tests/test.cc
)

target_link_libraries(scanner_tests PRIVATE scanner GTest::gtest GTest::gtest_main)

add_test(NAME ScannerTest COMMAND scanner_tests)