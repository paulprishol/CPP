#include "scanner.h"

int main(int argc, const char* argv[]){
    try {
        clock_t start = clock();
        HashCheck res(argc, argv);
        res.scan();
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        res.print_res(seconds);
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    catch (const BaseError) {
        std::cout << "Error: Can not read base file\n";
    }
    catch (std::filesystem::__cxx11::filesystem_error) {
        std::cout << "Error: Can not open directory\n";
    }
    catch (...) {
        std::cout << "Error: Some other exception\n";
    }
    return 0;
}