#include "scanner.h"

HashCheck::HashCheck(int argc, const char* argv[]) {
    if (argc != 7 || check_args(argc, argv) != 3) {
        throw std::invalid_argument("Incorrect input");
    }
    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--base") {
            base = argv[i+1];
        } else if (arg == "--log") {
            log = argv[i+1];
        } else if (arg == "--path") {
            path = argv[i+1];
        }
    }
    count_all = 0;
    count_malicious = 0;
    file_errors = 0;
}

std::string HashCheck::computeMD5FromFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::exception();
    }
    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(
        EVP_MD_CTX_new(), &EVP_MD_CTX_free
    );
    if (!ctx || EVP_DigestInit_ex(ctx.get(), EVP_md5(), nullptr) != 1) {
        throw std::exception();
    }
    const size_t BUF_SIZE = 4096;
    std::vector<char> buffer(BUF_SIZE);
    while (file) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = file.gcount();

        if (bytesRead > 0) {
            if (EVP_DigestUpdate(ctx.get(), buffer.data(), static_cast<size_t>(bytesRead)) != 1) {
                throw std::exception();
            }
        }
    }
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLen = 0;
    if (EVP_DigestFinal_ex(ctx.get(), digest, &digestLen) != 1) {
        throw std::exception();
    }
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < digestLen; ++i) {
        hexStream << std::setw(2) << static_cast<int>(digest[i] & 0xFF);
    }
    file.close();
    return hexStream.str();
}

bool HashCheck::check_file(const std::string &hash, const std::string &filepath) {
    std::ifstream file(base, std::ios::in);
    if (!file.is_open()) {
        throw BaseError{"Base Error"};
    }
    bool res = false;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string hash_mask, verdict;
        std::getline(ss, hash_mask, ';');
        std::getline(ss, verdict);
        if (hash_mask == hash) {
            res = true;
            logging(filepath, hash, verdict);
            break;
        }
    }
    file.close();
    return res;
}

void HashCheck::scan() {
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path)) {
        std::string str_path = dirEntry.path().string();
        if (std::filesystem::is_directory(str_path) == false) {
            try {
                const std::string hash = computeMD5FromFile(str_path);
                if (check_file(hash, str_path)) count_malicious++;
            }
            catch (const std::exception) {
                file_errors++;
            }
            count_all++;
        }
    }
}

void HashCheck::print_res(double& sec) {
    std::cout << std::left << std::setw(18) << "All files:  " << count_all << std::endl;
    std::cout << std::left << std::setw(18) << "Malicious files: " << count_malicious << std::endl;
    std::cout << std::left << std::setw(18) << "File errors: " << file_errors << std::endl;
    std::cout << std::left << std::setw(18) << "Execution time: " << sec << std::endl;
}

void HashCheck::logging(const std::string &filepath, const std::string &hash, const std::string &verdict) {
    std::ofstream file(log, std::ios::app);
    if (!file.is_open()) {
        throw std::exception();
    }
    file << filepath << " : " << hash << " : " << verdict << std::endl;
    file.close();
}

int HashCheck::get_count_all() {return count_all;}

int HashCheck::get_count_malicious() {return count_malicious;}

int HashCheck::get_file_errors() {return file_errors;}

int check_args(int argc, const char* argv[]) {
    char flags[][7] {"--base", "--log", "--path"};
    int res = 0;
    for (std::string flag : flags) {
        for (int i = 1; i < argc; i+=2)  {
            std::string arg = argv[i];
            if (flag == arg) {
                res += 1;
                break;
            }
        }
    }
    return res;
}