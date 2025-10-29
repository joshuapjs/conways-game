# include "Cli.h"
# include <string>
# include <iostream>

void Cli::start() {
    std::string input;
    bool q = false;
    while (!q) {
        std::cout << "CGOL>";
        getline(std::cin, input);
        if (!input.compare("quit")) {
            q = true;
            break;
        };
    }
};