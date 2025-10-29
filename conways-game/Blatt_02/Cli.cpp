# include "Cli.h"
# include <string>
# include <iostream>

// The implementation of Cli::start
void Cli::start() {
    std::string input;
    bool q = false;
    while (!q) {
        std::cout << "CGOL>";
        getline(std::cin, input);
        if (input == "quit") {
            q = true;
            break;
        };
    }
};