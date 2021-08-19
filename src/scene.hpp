#pragma once

#include <random>
#include <vector>
#include "cell.hpp"

enum Direction : int {
    LEFT = -1,
    RIGHT = 1
};

// The game state containing every simulated cell
class Scene {
public:
    Scene(int w, int h);

    void update();
    void gen_texture(float* result);
    void add_cell(Element element, int x, int y);
    void add_input(int x_pos, int y_pos, int radius, Element current_element);
    void remove_cell(int x, int y);
private:
    std::vector<Cell> cells;
    Direction direction { LEFT };
    int width;
    int height;

    // Randomization
    std::mt19937 rng;
    std::uniform_int_distribution<int> rand_dir;
    std::uniform_real_distribution<float> rand_color;

    Element get_element(int x, int y);
    void set_direction();
    bool cell_empty(int x, int y);
    bool bounds(int x, int y);

    // Update functions depending on cell element.
    void update_sand(int x, int y);
    void update_water(int x, int y);
};