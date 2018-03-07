#include "main.h"

#ifndef ISLANDS_H
#define ISLANDS_H


class Islands {
public:
    Islands() {}
    Islands(float x, float y, float z, color_t color);
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

#endif // ISLANDS_H
