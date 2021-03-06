#pragma once

#include "cell.hpp"

// Handles mouse input
class Controller {
private:
    GLFWwindow* window;
    Element element { SAND };
    int x { 0 };
    int y { 0 };
    bool button_down { false };
    int radius { 6 };

    // Cursor callback
    static void cursor_click(GLFWwindow* window, int button, int action, int mods);
    static void cursor_enter(GLFWwindow* window, int entered);
    static void scroll(GLFWwindow* window, double xoffset, double yoffset);
public:
    Controller(GLFWwindow* w);
    ~Controller() { glfwDestroyWindow(window); }

    void update(int tex_w, int tex_h);
    void position(int* x_pos, int* y_pos);
    bool get_button_down() { return button_down; }
    Element current_element() { return element; }
    int get_radius() { return radius; }

    // Keyboard input
    void key_input();
};