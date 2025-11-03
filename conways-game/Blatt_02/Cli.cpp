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
        size_t width = std::stoul(match[1]);
        size_t height = std::stoul(match[2]);

        std::cout << "width: " << width << "\n";
        std::cout << "height: " << height << std::endl;
        input = "";
        std::cout << "CGOL> ";
      }
      // load <some UNIX path>
    } else if (std::regex_match(input, std::regex(R"(\s*load\s+.+\s*)"))) {
      std::regex unix_path_regex(R"(\s*load\s+([^\\]+)\s*)");
      std::smatch match;

      if (std::regex_match(input, match, unix_path_regex)) {
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
    } else if (std::regex_match(input, std::regex(R"(\s*save\s+.+\s*)"))) {
      std::regex unix_path_regex(R"(\s*save\s+([^\\]+)\s*)");
      std::smatch match;

      if (std::regex_match(input, match, unix_path_regex)) {
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
      // help - an overview over all possible commands.
    } else if (std::regex_match(input, std::regex(R"(\s*help\s*|\s*h\s*)"))) {
      std::cout << "The following commands are available:\n\ncreate "
                   "<x-length> <y-length>\nload "
                   "<some UNIX path>\nsave <some UNIX path>\nprint <1 "
                   "(enable) | 0 (disable)>\nset <x-index> <y-index> <0 "
                   "(alive) | 1 (dead)>\nget <x-index> <y-index>\n"
                << std::endl;
      input = "";
      std::cout << "CGOL> ";
      // Enable print
    } else if (std::regex_match(input, std::regex(R"(\s*print\s+[01]\s*)"))) {
      std::regex command_print_regex(std::regex(R"(\s*print\s+([01])\s*)"));
      std::smatch match;

      if (std::regex_match(input, match, command_print_regex)) {
        printOn = std::stoi(match[1]);
        std::cout << printOn << std::endl;
        input = "";
        std::cout << "CGOL> ";
      }
      // Base case for handling invalid commands.
    } else {
      std::cout << "\nNot sure what you mean by " << "'" << input << "'"
                << "\n\nPlease type 'help' or 'h' for support.\n"
                << std::endl;
      input = "";
      std::cout << "CGOL> ";
    };
  }
}
