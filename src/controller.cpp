#include <glm/glm.hpp>
#include <stdio.h>
#include <math.h>
#include "controller.hpp"

void Controller::update(int tex_w, int tex_h) {
    if(button_down) {
        int width, height;
        double x_pos, y_pos;
        glfwGetWindowSize(window, &width, &height);
        glfwGetCursorPos(window, &x_pos, &y_pos);

        // Reverse y position
        y_pos = (height - y_pos);

        double x_scale = x_pos / (double)width;
        double y_scale = y_pos / (double)height;

        x = (int)floor(x_scale * (double)tex_w);
        y = (int)floor(y_scale * (double)tex_h);
    }
}

void Controller::key_input() {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        element = WATER;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        element = SAND;
    }
}

void Controller::cursor_click(GLFWwindow* window, int button, int action, int mods) {
    Controller* c = (Controller*)glfwGetWindowUserPointer(window);
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS) {
            c->button_down = true;
        } else if(action == GLFW_RELEASE) {
            c->button_down = false;
        }
    }
}

void Controller::cursor_enter(GLFWwindow* window, int entered) {
    Controller* c = (Controller*)glfwGetWindowUserPointer(window);
    if(!entered) {
        c->button_down = false;
    }
}

Controller::Controller(GLFWwindow* w) {
    window = w;
    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, cursor_click);
    glfwSetCursorEnterCallback(window, cursor_enter);
}

void Controller::position(int* x_pos, int* y_pos) {
    *x_pos = x;
    *y_pos = y;
}