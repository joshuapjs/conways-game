#include "World.h"
#include <iostream>
#include <fstream>

void World::allocateGrids() {
    for (auto & grid : grids) {
        grid = new bool*[rows];
        for (int j = 0; j < rows; ++j)
            grid[j] = new bool[cols]{false};
    }
}

void World::freeGrids() {
    for (auto & grid : grids) {
        for (int j = 0; j < rows; ++j)
            delete[] grid[j];
        delete[] grid;
    }
}

World::World(int height, int width) : rows(height), cols(width), currentGridIndex(0) {
    allocateGrids();
}

World::~World() {
    freeGrids();
}

int World::countLiveNeighbors(int r, int c) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int nr = (r + dr + rows) % rows;
            int nc = (c + dc + cols) % cols;

            if (grids[currentGridIndex][nr][nc]) ++count;
        }
    }
    return count;
}

void World::set(int height, int width, bool alive) {
    if (height >= 0 && height < rows && width >= 0 && width < cols)
        grids[currentGridIndex][height][width] = alive;
}

void World::copyGrid(bool** dest, bool** src) const {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            dest[i][j] = src[i][j];
}

bool World::compareGrids(bool** g1, bool** g2) const {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (g1[i][j] != g2[i][j])
                return false;
    return true;
}

void World::evolve() {
    int nextIndex = (currentGridIndex + 1) % 4;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int liveNeighbors = countLiveNeighbors(r, c);
            if (grids[currentGridIndex][r][c])
                grids[nextIndex][r][c] = (liveNeighbors == 2 || liveNeighbors == 3);
            else
                grids[nextIndex][r][c] = (liveNeighbors == 3);
        }
    }

    currentGridIndex = nextIndex;
}

bool World::isStable() const {
    int g0 = currentGridIndex,
        g1 = (g0 + 3) % 4,
        g2 = (g0 + 2) % 4,
        g3 = (g0 + 1) % 4;

    return compareGrids(grids[g1], grids[g3]) &&
           compareGrids(grids[g2], grids[g0]);
}

void World::print() const {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c)
            std::cout << (grids[currentGridIndex][r][c] ? '1' : '0');
        std::cout << '\n';
    }
}

bool World::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    int newRows, newCols;
    file >> newRows >> newCols;
    if (!file.good() || newRows <= 0 || newCols <= 0) return false;

    freeGrids();
    rows = newRows;
    cols = newCols;
    currentGridIndex = 0;
    allocateGrids();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int val;
            file >> val;
            grids[currentGridIndex][r][c] = (val != 0);
        }
    }

    for (int i = 1; i < 4; ++i)
        copyGrid(grids[i], grids[0]);

    return true;
}

bool World::save(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) return false;

    file << rows << "\n" << cols << "\n";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            file << (grids[currentGridIndex][r][c] ? 1 : 0);
            if (c < cols - 1) file << ' ';
        }
        file << '\n';
    }

    return true;
}