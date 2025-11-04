#include "Cli.h"

#include <chrono>
#include <iostream>
#include <random>
#include <regex>
#include <string>
#include <thread>

#include "World.h"

Cli::Cli()
    : printOn(true), delayTime(250), stabilityCheck(false), world(nullptr) {}

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
      // help - command overview
    } else if (std::regex_match(input, std::regex(R"(\s*help\s*|\s*h\s*)"))) {
      help(input);
      // examples - usage examples
    } else if (std::regex_match(input, std::regex(R"(\s*example[s]?\s*|\s*ex\s*)"))) {
      examples(input);
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
      // Add Beacon pattern
    } else if (std::regex_match(
                   input, std::regex(R"(\s*beacon\s+[0-9]+\s+[0-9]+\s*)"))) {
      addBeacon(input);
      // Add Methuselah pattern
    } else if (std::regex_match(
                   input, std::regex(R"(\s*methuselah\s+[0-9]+\s+[0-9]+\s*)"))) {
      addMethuselah(input);
      // Base case for handling invalid commands.
    } else {
      std::cout << "\nNot sure what you mean by " << "'" << input << "'"
                << "\n\nPlease type 'help' or 'h' for support.\n"
                << std::endl;
      input = "";
      std::cout << "CGOL> ";
    }
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

//////////////////////////////////////////////////////

void Cli::addMethuselah(std::string& input) {
  const std::regex command_methuselah(R"(\s*methuselah\s+([0-9]+)\s+([0-9]+)\s*)");
  std::smatch match;

  if (std::regex_match(input, match, command_methuselah)) {
    int x = std::stoi(match[1]);
    int y = std::stoi(match[2]);

    if (!world) {
      std::cout << "Error: No world created. Use 'create' or 'load' first."
                << std::endl;
    } else {
      world->set(x, y + 1, true);
      world->set(x, y + 2, true);
      world->set(x + 1, y, true);
      world->set(x + 1, y + 1, true);
      world->set(x + 2, y + 1, true);
      std::cout << "Methuselah added at (" << x << ", " << y << ")" << std::endl;
    }
    input = "";
    std::cout << "CGOL> ";
  }
}

/////////////////////////////////////////////////////

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
        std::cout << "\x1b[3J\x1b[2J\x1b[H";
        std::cout.flush();
        if (printOn) {
          int size = world->getCols() > world->getRows() ? world->getCols() : world->getRows();
          std::cout << "\x1b[3J\x1b[2J\x1b[H";
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
  std::cout << "\n" << std::string(50, '=') << "\n";
  std::cout << "           COMMAND REFERENCE\n";
  std::cout << std::string(50, '=') << "\n\n";

  std::cout << "WORLD MANAGEMENT:\n";
  std::cout << "  create <width> <height>    Create new world\n";
  std::cout << "  load <unix-path>           Load world from file\n";
  std::cout << "  save <unix-path>           Save world to file\n\n";

  std::cout << "SIMULATION CONTROL:\n";
  std::cout << "  run <generations>          Run simulation\n";
  std::cout << "  print <0|1>                Toggle live display\n";
  std::cout << "  delay <milliseconds>       Delay between generations\n";
  std::cout << "  stability <0|1>            Auto-stop when stable\n\n";

  std::cout << "CELL OPERATIONS:\n";
  std::cout << "  set <x> <y> <0|1>          Set cell state\n";
  std::cout << "  set <position> <0|1>       Set cell by 1D index\n";
  std::cout << "  get <x> <y>                Get cell state\n";
  std::cout << "  get <position>             Get cell by 1D index\n\n";

  std::cout << "PATTERNS:\n";
  std::cout << "  glider <x> <y>             Add glider pattern\n";
  std::cout << "  toad <x> <y>               Add toad pattern\n";
  std::cout << "  beacon <x> <y>             Add beacon pattern\n";
  std::cout << "  methuselah <x> <y>         Add methuselah pattern\n";
  std::cout << "  random <count>             Add random patterns\n\n";

  std::cout << "APPLICATION:\n";
  std::cout << "  help, h                    Command reference\n";
  std::cout << "  example, ex                Usage examples\n";
  std::cout << "  quit, q, exit, :q          Exit program\n";

  std::cout << std::string(50, '=') << "\n" << std::endl;

  input = "";
  std::cout << "CGOL> ";
}

void Cli::examples(std::string& input) {
  std::cout << "\n" << std::string(50, '=') << "\n";
  std::cout << "           USAGE EXAMPLES\n";
  std::cout << std::string(50, '=') << "\n\n";

  std::cout << "EXAMPLE 1: Basic simulation with visualization\n";
  std::cout << "  create 30 30       # Create 30x30 world\n";
  std::cout << "  glider 5 5         # Add a glider\n";
  std::cout << "  toad 15 10         # Add a toad oscillator\n";
  std::cout << "  print 1            # Enable live display\n";
  std::cout << "  delay 100          # 100ms between frames\n";
  std::cout << "  run 50             # Run 50 generations\n\n";

  std::cout << "EXAMPLE 2: Fast simulation with stability check\n";
  std::cout << "  create 40 40\n";
  std::cout << "  random 8           # Add 8 random patterns\n";
  std::cout << "  print 0            # Disable display for speed\n";
  std::cout << "  stability 1        # Stop when world becomes stable\n";
  std::cout << "  run 1000           # Run up to 1000 generations\n\n";

  std::cout << "EXAMPLE 3: Manual cell creation\n";
  std::cout << "  create 20 20\n";
  std::cout << "  set 5 5 1          # Create custom pattern\n";
  std::cout << "  set 6 6 1\n";
  std::cout << "  set 7 5 1\n";
  std::cout << "  set 7 6 1\n";
  std::cout << "  set 7 7 1\n";
  std::cout << "  print 1\n";
  std::cout << "  run 20\n\n";

  std::cout << "EXAMPLE 4: Save and load workflow\n";
  std::cout << "  create 25 25\n";
  std::cout << "  glider 0 0\n";
  std::cout << "  beacon 10 10\n";
  std::cout << "  save my_pattern.txt\n";
  std::cout << "  # ... later ...\n";
  std::cout << "  load my_pattern.txt\n";
  std::cout << "  run 100\n\n";

  std::cout << "Type 'help' for complete command reference.\n";
  std::cout << std::string(50, '=') << "\n" << std::endl;

  input = "";
  std::cout << "CGOL> ";
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
