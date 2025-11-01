#include "Cli.h"

#include <iostream>
#include <regex>
#include <string>

// The implementation of Cli::start
void Cli::start() {
  std::string input;

  std::cout << "CGOL> ";
  while (std::getline(std::cin, input)) {
    // quit the application
    if (std::regex_match(input, std::regex(R"(\s*quit\s*)")) ||
        std::regex_match(input, std::regex(R"(\s*q\s*)")) ||
        std::regex_match(input, std::regex(R"(\s*quit\s*)")) ||
        std::regex_match(input, std::regex(R"(\s*exit\s*)")) ||
        std::regex_match(input, std::regex(R"(\s*logout\s*)")) ||
        std::regex_match(input, std::regex(R"(\s*:q\s*)"))) {
      std::cout << "ciao." << std::endl;
      break;
      // create <int> <int>
    } else if (std::regex_match(
                   input, std::regex(R"(\s*create\s+[0-9]+\s+[0-9]+\s*)")) &&
               !std::regex_match(input, std::regex(R"(-)"))) {
      std::regex command_create_regex(R"(\s*create\s+([0-9]+)\s+([0-9]+)\s*)");
      std::smatch match;

      if (std::regex_match(input, match, command_create_regex)) {
        size_t first_int = std::stoul(match[1]);
        size_t second_int = std::stoul(match[2]);

        std::cout << "First integer: " << first_int << "\n";
        std::cout << "Second integer: " << second_int << std::endl;
        input = "";
        std::cout << "CGOL> ";
      }
      // load <some UNIX path>
    } else if (std::regex_match(input, std::regex(R"(\s*load\s+[^ ]+\s*)"))) {
      std::regex command_load_regex(R"(\s*load\s+([^\\]+)\s*)");
      std::smatch match;

      if (std::regex_match(input, match, command_load_regex)) {
        std::string path = match[1];

        std::cout << "Following path for loading was specified: " << path
                  << std::endl;
        input = "";
        std::cout << "CGOL> ";
      } else {
        input = "";
        std::cout << "Only UNIX paths are allowed" << "\n";
        std::cout << "CGOL> ";
      }
      // save <some UNIX path>
    } else if (std::regex_match(input, std::regex(R"(\s*save\s+[^ ]+\s*)"))) {
      std::regex command_save_regex(R"(\s*save\s+([^\\]+)\s*)");
      std::smatch match;

      if (std::regex_match(input, match, command_save_regex)) {
        std::string path = match[1];

        std::cout << "Following path for saving was specified: " << path
                  << std::endl;
        input = "";
        std::cout << "CGOL> ";
      } else {
        input = "";
        std::cout << "Only UNIX paths are allowed" << std::endl;
        std::cout << "CGOL> ";
      }
      // Base case for handling invalid commands.
    } else {
      std::cout << "\nNot sure what you mean by " << "'" << input << "'" << "\n\nPlease type 'help' or 'h' for support.\n" << std::endl;
      input = "";
      std::cout << "CGOL> ";
    };
  }
}
