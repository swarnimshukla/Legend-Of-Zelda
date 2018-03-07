#include "gifts.h"
#include "main.h"

Gifts::Gifts(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    gravity = -0.1;
    rotation=0;
    this->b.x = this->position.x;
    this->b.y = this->position.y;
    this->b.z = this->position.z;

    static const GLfloat vertex_buffer_data[] = {
        0.0f, 10.0f, 0.0f,
        0.0f,-10.0f, 0.0f,
        20.0f,3.0f, 0.0f,

        0.0f, 10.0f, 0.0f,
        0.0f,-10.0f, 0.0f,
        -20.0f,2.0f, 0.0f,


        
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);


}

void Gifts::draw(glm::mat4 VP) {
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

void Gifts::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Gifts::tick() {
    this->b.x = this->position.x;
    this->b.y = this->position.y;
    this->b.z = this->position.z;
    this->b.height = 60;
    this->b.width = 60;
    this->b.length = 25; 
    this->rotation+=speed;   
}

