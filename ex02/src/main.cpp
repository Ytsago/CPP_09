#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error\n";
        return 1;
    }

    PmergeMe pm;
    try {
        pm.parseInput(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // Print "Before" line
    std::cout << "Before: ";
    for (int i = 1; i < argc; ++i) {
        std::cout << argv[i];
        if (i + 1 < argc) std::cout << ' ';
    }
    std::cout << '\n';

    pm.sort();
    pm.printResults();

    return 0;
}
