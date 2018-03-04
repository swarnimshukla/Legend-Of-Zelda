#include "main.h"

#ifndef ROCKS_H
#define ROCKS_H


class Rocks {
public:
    Rocks() {}
    Rocks(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t box1;
private:
    VAO *object;
    
};

#endif // ROCKS_H
