#include "main.h"

#ifndef GIFTS_H
#define GIFTS_H


class Gifts {
public:
    Gifts() {}
    Gifts(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int flag;
    float gravity;
    bounding_box_t b;
private:
    VAO *object;
    
};

#endif // GIFTS_H
