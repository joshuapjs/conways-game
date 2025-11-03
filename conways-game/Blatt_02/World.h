#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
#include <string>

class World {
private:
    int rows, cols;
    bool** grids[4]{};      // Store 4 snapshots of the world
    int currentGridIndex; // Index of the latest updated grid (0 to 3)

    int countLiveNeighbors(int r, int c) const;
    void allocateGrids();
    void freeGrids();

    // Helper methods to manage grid storage
    void copyGrid(bool** dest, bool** src) const;     // Copy one grid into another
    bool compareGrids(bool** g1, bool** g2) const; // Compare two grids

public:
    World(int rows, int cols);
    ~World();

    void set(int height, int width, bool alive);
    void evolve();                       // Evolves and stores new state in rotation
    bool isStable() const;               // Checks for period-2 stability
    void print() const;

    bool load(const std::string& path);
    bool save(const std::string& path) const;
};

#endif // GAME_OF_LIFE_H