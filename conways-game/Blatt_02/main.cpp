#include <iostream>
#include "World.h"

int main() {
    World world(5, 5);

    if (!world.load("p67_snark_loop.txt")) {
        std::cerr << "Failed to load from file.\n";
        return 1;
    }

    world.print();
    std::cout << '\n';

    for (int i = 0; i < 100; ++i) {
        world.evolve();
        std::cout << "Generation " << i + 1 << ":\n";
        //game.print();
        std::cout << '\n';

        if (world.isStable()) {
            std::cout << "Stabilized at generation " << i + 1 << ".\n";
            break;
        }
    }

    if (!world.save("output.txt")) {
        std::cerr << "Failed to save to file.\n";
        return 1;
    }

    return 0;
}