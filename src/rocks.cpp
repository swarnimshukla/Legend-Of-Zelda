#include "rocks.h"
#include "main.h"

Rocks::Rocks(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
       -7.0f,-7.0f,-7.0f, // triangle 1 : begin
        -7.0f,-7.0f, 7.0f,
        -7.0f, 7.0f, 7.0f, // triangle 1 : end
        7.0f, 7.0f,-7.0f, // triangle 2 : begin
        -7.0f,-7.0f,-7.0f,
        -7.0f, 7.0f,-7.0f, // triangle 2 : end
        7.0f,-7.0f, 7.0f,
        -7.0f,-7.0f,-7.0f,
        7.0f,-7.0f,-7.0f,
        7.0f, 7.0f,-7.0f,
        7.0f,-7.0f,-7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f, 7.0f, 7.0f,
        -7.0f, 7.0f,-7.0f,
        7.0f,-7.0f, 7.0f,
        -7.0f,-7.0f, 7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f, 7.0f, 7.0f,
        -7.0f,-7.0f, 7.0f,
        7.0f,-7.0f, 7.0f,
        7.0f, 7.0f, 7.0f,
        7.0f,-7.0f,-7.0f,
        7.0f, 7.0f,-7.0f,
        7.0f,-7.0f,-7.0f,
        7.0f, 7.0f, 7.0f,
        7.0f,-7.0f, 7.0f,
        7.0f, 7.0f, 7.0f,
        7.0f, 7.0f,-7.0f,
        -7.0f, 7.0f,-7.0f,
        7.0f, 7.0f, 7.0f,
        -7.0f, 7.0f,-7.0f,
        -7.0f, 7.0f, 7.0f,
        7.0f, 7.0f, 7.0f,
        -7.0f, 7.0f, 7.0f,
        7.0f,-7.0f, 7.0f

        
    };
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_BROWN, GL_FILL);


}

void Rocks::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
}

void Rocks::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rocks::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    this->box1.x = this->position.x;
    this->box1.y = this->position.y;
    this->box1.z = this->position.z;
    this->box1.height = 14;
    this->box1.width = 14;
    this->box1.length = 14; 
}

