#pragma once

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <filesystem>
#include <vector>
#include <ctime>

class HashCheck {
    public:
        HashCheck(int argc, const char* argv[]);
        std::string computeMD5FromFile(const std::string &filepath);
        bool check_file(const std::string &hash, const std::string &filepath);
        void scan();
        void print_res(double& sec);
        void logging(const std::string &filepath, const std::string &hash, const std::string &verdict);
        int get_count_all();
        int get_count_malicious();
        int get_file_errors();
    private:
        std::string base, log, path;
        int count_all, count_malicious, file_errors;
};

struct PathError {
    std::string message;
};

struct BaseError {
    std::string message;
};

int check_args(int argc, const char* argv[]);