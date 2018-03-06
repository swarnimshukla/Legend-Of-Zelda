#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H


class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y, float z, color_t color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int flag;
    float gravity;
    bounding_box_t box1;
    double speedx;
    double speedy;
    double speedz;
    
private:
    VAO *object;
    VAO *object1;
    
};

#endif // FIREBALL_H
