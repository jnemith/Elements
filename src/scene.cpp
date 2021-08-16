#include "scene.hpp"
#include "controller.hpp"

Scene::Scene(int w, int h) : rand_dir(std::uniform_int_distribution<>(0, 1)) {
    width = w;
    height = h;
    std::random_device rd;
    rng.seed(rd());

    Cell empty { EMPTY };
    for(unsigned int i = 0; i < width * height; i++) {
        cells.push_back(empty);
    }
};

// Update the scene bottom up, width wise
// y = 0 is the bottom of the screen, x = 0 is the left
void Scene::update() {
    Element current;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            current = get_element(x, y);
            set_direction();
            switch(current) {
                case EMPTY: break;
                case DIRT:
                case SAND: update_sand(x, y); break;
                case WATER: update_water(x, y); break;
                case STEEL: break;
            }
        }
    }
}

void Scene::update_sand(int x, int y) {
    if(y >= 0) {
        Element current = get_element(x, y);
        Element below = get_element(x, y - 1);
        Element below_lr = get_element(x + direction, y - 1);

        if(below == EMPTY) {
            remove_cell(x, y);
            add_cell(current, x, y - 1);
        } else if(below_lr == EMPTY) {
            remove_cell(x, y);
            add_cell(current, x + direction, y - 1);
        } else if(below == WATER) {
            add_cell(WATER, x, y);
            add_cell(current, x, y - 1);
        } else if(below_lr == WATER) {
            add_cell(WATER, x, y);
            add_cell(current, x + direction, y - 1);
        }
    }
}

void Scene::update_water(int x, int y) {
    if(y >= 0) {
        Element current = get_element(x, y);
        Element below = get_element(x, y - 1);
        Element below_lr = get_element(x + direction, y - 1);
        Element neighbor = get_element(x + direction, y);

        if(below == EMPTY) {
            remove_cell(x, y);
            add_cell(current, x, y - 1);
        } else if(below_lr == EMPTY) {
            remove_cell(x, y);
            add_cell(current, x + direction, y - 1);
        } else if(neighbor == EMPTY) {
            remove_cell(x, y);
            add_cell(current, x + direction, y);
        }
    }
}

// Return an array of RGB values to result
void Scene::gen_texture(float* result) {
    int color_counter = 0;
    for(unsigned int i = 0; i < width * height * 3; i+=3) {
        glm::vec3 tmp_color = cells.at(color_counter).get_color();
        result[i] = tmp_color.x;
        result[i + 1] = tmp_color.y;
        result[i + 2] = tmp_color.z;
        color_counter += 1;
    }
}

// Add a new cell to the scene at position (x, y)
void Scene::add_cell(Element element, int x, int y) {
    if(bounds(x, y)) {
        int position = (y * width) + x;
        Cell cell { element };
        cells.at(position) = cell;
    }
}

// Remove the cell in position (x, y) if it is not empty
void Scene::remove_cell(int x, int y) {
    if(bounds(x, y)) {
        int position = (y * width) + x;
        if(!cell_empty(x, y)) {
            Cell cell { EMPTY };
            cells.at(position) = cell;
        }
    }
}

// Return the element of the cell at position (x, y)
Element Scene::get_element(int x, int y) {
    if(!bounds(x, y)) {
        return BOUND;
    }
    int position = (y * width) + x;
    return cells.at(position).get_element();
}

// Check if the cell at position (x, y) is empty
bool Scene::cell_empty(int x, int y) {
    if(!bounds(x, y)) {
        return false;
    }
    int position = (y * width) + x;
    return cells.at(position).get_element() == EMPTY;
}

// Get random direction
void Scene::set_direction() {
    int tmp = rand_dir(rng);
    if(tmp == 0) {
        direction = LEFT;
    } else {
        direction = RIGHT;
    }
}

bool Scene::bounds(int x, int y) {
    if(x < 0 || x > width - 1 || y < 0 || y > height) {
        return false;
    }
    return true;
}