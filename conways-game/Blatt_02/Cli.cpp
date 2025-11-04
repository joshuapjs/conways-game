#include "Cli.h"

#include <chrono>
#include <iostream>
#include <random>
#include <regex>
#include <string>
#include <thread>

#include "World.h"

Cli::Cli()
    : printOn(false), delayTime(100), stabilityCheck(false), world(nullptr) {}

Cli::~Cli() = default;

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
      create(input);
      // load <some UNIX path>
    } else if (std::regex_match(input, std::regex(R"(\s*load\s+.+\s*)"))) {
      load(input);
      // save <some UNIX path>
    } else if (std::regex_match(input, std::regex(R"(\s*save\s+.+\s*)"))) {
      save(input);
      // help - an overview over all possible commands.
    } else if (std::regex_match(input, std::regex(R"(\s*help\s*|\s*h\s*)"))) {
      help(input);
      // Enable print
    } else if (std::regex_match(input, std::regex(R"(\s*print\s+[01]\s*)"))) {
      print(input);
      // set delay
    } else if (std::regex_match(input, std::regex(R"(\s*delay\s+[0-9]+\s*)"))) {
      delay(input);
      // Stability check
    } else if (std::regex_match(input,
                                std::regex(R"(\s*stability\s+[01]\s*)"))) {
      stability(input);
      // Run simulation
    } else if (std::regex_match(input, std::regex(R"(\s*run\s+[0-9]+\s*)"))) {
      run(input);
      // Set cell state 2D position
    } else if (std::regex_match(
                   input,
                   std::regex(R"(\s*set\s+[0-9]+\s+[0-9]+\s+[01]\s*)"))) {
      setTwoD(input);
      // Set cell state 1D position
    } else if (std::regex_match(input,
                                std::regex(R"(\s*set\s+[0-9]+\s+[01]\s*)"))) {
      setOneD(input);
      // Get cell state 2D position
    } else if (std::regex_match(input,
                                std::regex(R"(\s*get\s+[0-9]+\s+[0-9]+\s*)"))) {
      getTwoD(input);
      // Get cell state 1D position
    } else if (std::regex_match(input, std::regex(R"(\s*get\s+[0-9]+\s*)"))) {
      getOneD(input);
      // Add Glider pattern
    } else if (std::regex_match(
                   input, std::regex(R"(\s*glider\s+[0-9]+\s+[0-9]+\s*)"))) {
      addGlider(input);
      // Add Toad pattern
    } else if (std::regex_match(
                   input, std::regex(R"(\s*toad\s+[0-9]+\s+[0-9]+\s*)"))) {
      addToad(input);
      // Beacon pattern
    } else if (std::regex_match(
                   input, std::regex(R"(\s*beacon\s+[0-9]+\s+[0-9]+\s*)"))) {
      addBeacon(input);
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

void Cli::addBeacon(std::string& input) {
  const std::regex command_beacon(R"(\s*beacon\s+([0-9]+)\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_beacon)) {
    int x = std::stoi(match[1]);
    int y = std::stoi(match[2]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      world->set(x, y, true);
      world->set(x + 1, y, true);
      world->set(x, y + 1, true);
      world->set(x + 3, y + 2, true);
      world->set(x + 2, y + 3, true);
      world->set(x + 3, y + 3, true);
      std::cout << "Beacon added at (" << x << ", " << y << ")" << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::addToad(std::string& input) {
  const std::regex command_toad(R"(\s*toad\s+([0-9]+)\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_toad)) {
    int x = std::stoi(match[1]);
    int y = std::stoi(match[2]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      world->set(x, y + 1, true);
      world->set(x, y + 2, true);
      world->set(x, y + 3, true);
      world->set(x + 1, y, true);
      world->set(x + 1, y + 1, true);
      world->set(x + 1, y + 2, true);
      std::cout << "Toad added at (" << x << ", " << y << ")" << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::addGlider(std::string& input) {
  const std::regex command_glider(R"(\s*glider\s+([0-9]+)\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_glider)) {
    int x = std::stoi(match[1]);
    int y = std::stoi(match[2]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      // Glider pattern
      world->set(x, y + 1, true);
      world->set(x + 1, y + 2, true);
      world->set(x + 2, y, true);
      world->set(x + 2, y + 1, true);
      world->set(x + 2, y + 2, true);
      std::cout << "Glider added at (" << x << ", " << y << ")" << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::getOneD(std::string& input) {
  const std::regex command_get_1d(R"(\s*get\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_get_1d)) {
    int pos = std::stoi(match[1]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      std::cout << "Cell at position " << pos << " - use world inspection"
                << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::getTwoD(std::string& input) {
  const std::regex command_get_2d(R"(\s*get\s+([0-9]+)\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_get_2d)) {
    int x = std::stoi(match[1]);
    int y = std::stoi(match[2]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      // Get state through print grid access or add getter
      std::cout << "Cell at (" << x << ", " << y << ") - use world inspection"
                << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::setOneD(std::string& input) {
  const std::regex command_set_1d(R"(\s*set\s+([0-9]+)\s+([01])\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_set_1d)) {
    int pos = std::stoi(match[1]);
    int state = std::stoi(match[2]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      int cols = world->getCols();
      int x = pos % cols;
      int y = pos / cols;
      world->set(x, y, state);
      std::cout << "Cell at position " << pos << " set to "
                << (state ? "alive" : "dead") << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::setTwoD(std::string& input) {
  const std::regex command_set_2d(R"(\s*set\s+([0-9]+)\s+([0-9]+)\s+([01])\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_set_2d)) {
    int x = std::stoi(match[1]);
    int y = std::stoi(match[2]);
    int state = std::stoi(match[3]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      world->set(x, y, state);
      std::cout << "Cell at (" << x << ", " << y << ") set to "
                << (state ? "alive" : "dead") << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::run(std::string& input) {
  const std::regex command_run(R"(\s*run\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_run)) {
    int generations = std::stoi(match[1]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      auto start = std::chrono::high_resolution_clock::now();

      for (int i = 0; i < generations; ++i) {
        if (printOn) {
          std::cout << "\033[2J\033[H";
          world->print();
          std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
        }

        world->evolve();

        if (stabilityCheck && world->isStable()) {
          std::cout << "Stability reached after " << (i + 1) << " generations"
                    << std::endl;
          break;
        }
      }

      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      std::cout << "Time for " << generations
                << " generations: " << duration.count() << " ms" << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::stability(std::string& input) {
  const std::regex command_stability(R"(\s*stability\s+([01])\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_stability)) {
    stabilityCheck = std::stoi(match[1]);
    std::cout << "Stability check " << (stabilityCheck ? "enabled" : "disabled")
              << std::endl;
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::delay(std::string& input) {
  const std::regex command_delay(R"(\s*delay\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_delay)) {
    delayTime = std::stoi(match[1]);
    std::cout << "Delay set to " << delayTime << " ms" << std::endl;
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::print(std::string& input) {
  const std::regex command_print_regex(std::regex(R"(\s*print\s+([01])\s*)"));
  std::smatch match;

  if (std::regex_match(input, match, command_print_regex)) {
    printOn = std::stoi(match[1]);
    std::cout << "Print was " << (printOn? "enabled" : "disabled")
              << std::endl;
    input = "";
    std::cout << "CGOL> ";
  }
}

void Cli::help(std::string& input) {
  std::cout << "The following commands are available:\n\ncreate "
               "<x-length> <y-length>\nload "
               "<some UNIX path>\nsave <some UNIX path>\nprint <1 "
               "(enable) | 0 (disable)>\ndelay <time in ms>\nstability <1 "
               "(enable) | 0 (disable)>\nrun <n generations>\nset <x-index> "
               "<y-index> <0 "
               "(alive) | 1 (dead)>\nset <position> <0 | 1>\nget <x-index> "
               "<y-index>\nget <position>\n"
               "glider <x> <y>\ntoad <x> <y>\nbeacon <x> <y>\n"
            << std::endl;
  input = "";
  std::cout << "CGOL> ";
  // Enable print
}

void Cli::save(std::string& input) {
  const std::regex unix_path_regex(R"(\s*save\s+([^\\]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, unix_path_regex)) {
    std::string path = match[1];

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else if (world->save(path)) {
      std::cout << "Following path for saving was specified: " << path
                << std::endl;
    } else {
      std::cout << "Error: Failed to save world to " << path << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  } else {
    input = "";
    std::cout << "Only UNIX paths are allowed" << std::endl;
    std::cout << "CGOL> ";
  }
}

void Cli::load(std::string& input) {
  const std::regex unix_path_regex(R"(\s*load\s+([^\\]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, unix_path_regex)) {
    std::string path = match[1];

    world = std::make_unique<World>(1, 1);
    if (world->load(path)) {
      std::cout << "Following path for loading was specified: " << path
                << std::endl;
    } else {
      std::cout << "Error: Failed to load world from " << path << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  } else {
    input = "";
    std::cout << "Only UNIX paths are allowed" << "\n";
    std::cout << "CGOL> ";
  }
}

void Cli::create(std::string& input) {
  const std::regex command_create_regex(R"(\s*create\s+([0-9]+)\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_create_regex)) {
    size_t width = std::stoul(match[1]);
    size_t height = std::stoul(match[2]);

    world = std::make_unique<World>(height, width);
    std::cout << "width: " << width << "\n";
    std::cout << "height: " << height << std::endl;
    input = "";
    std::cout << "CGOL> ";
  }
}
