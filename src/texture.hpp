#pragma once

#include <glad/glad.h>

class Texture {
private:
    unsigned int id;
    int width;
    int height;
public:
    Texture(int w, int h) {
        width = w;
        height = h;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    ~Texture() { glDeleteTextures(1, &id); }

    void render(float* data) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_FLOAT,
            data
        );
    }
};