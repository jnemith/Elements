#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const glm::vec3 BG_COLOR = glm::vec3(0.3f, 0.4f, 0.3f);

enum Element {
    EMPTY = 0,

    // Out of range
    BOUND,

    // Gravity
    SAND,
    DIRT,

    // Fluid
    WATER,

    // No gravity
    STEEL,
};

class Cell {
public:
    Cell(Element elem) {
        element = elem;
        default_color(elem);
    };
    glm::vec3 get_color() { return color; }
    void set_color(glm::vec3 c) { color = c; }
    Element get_element() { return element; }
private:
    Element element;
    float lifetime { 0.0f };
    glm::vec3 color { BG_COLOR };

    void default_color(Element elem) {
        // Determine color based on element type
        glm::vec3 res;

        switch(elem) {
            case EMPTY: res = BG_COLOR; break;
            case DIRT: res = glm::vec3(0.5, 0.4, 0.0); break;
            case SAND: res = glm::vec3(0.8 , 0.75 , 0.5); break;
            case WATER: res = glm::vec3(0.1, 0.7 , 0.9 ); break;
            case STEEL: res = glm::vec3(0.8, 0.8, 0.9 ); break;
            default: res = BG_COLOR;
        }

        color = res;
    }
};