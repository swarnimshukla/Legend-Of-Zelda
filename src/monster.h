#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, color_t color, int c);
    glm::vec3 position;
    float rotation;
    int c;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int flag;
    float gravity;
    bounding_box_t box1;
private:
    VAO *object;
    VAO *object1;
    
};

#endif // MONSTER_H
