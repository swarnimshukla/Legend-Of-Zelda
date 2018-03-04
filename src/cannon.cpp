#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        -2.0f, 2.0f, -12.0f,
        2.0f,2.0f, -12.0f,
        2.0f,2.0f, -52.0f,

        -2.0f, 2.0f, -12.0f,
        -2.0f,2.0f, -52.0f,
        2.0f,2.0f, -52.0f,


        
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_CANNON, GL_FILL);


}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::

            mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
}

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

