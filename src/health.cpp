#include "health.h"
#include "main.h"

Health::Health(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->box1.x = this->position.x;
    this->box1.y = this->position.y;
    this->box1.z = this->position.z;
    GLfloat vertex_buffer_data[] = {
        4.0f, 20.0f, 0.0f,
        -4.0f,20.0f, 0.0f,
        4.0f,-20.0f, 0.0f,

        -4.0f, 20.0f, 0.0f,
        -4.0f,-20.0f, 0.0f,
        4.0f,-20.0f, 0.0f,

        8.0f, 5.0f, 0.0f,
        -8.0f,5.0f, 0.0f,
        8.0f,-5.0f, 0.0f,

        8.0f, -5.0f, 0.0f,
        -8.0f,-5.0f, 0.0f,
        -8.0f,5.0f, 0.0f,


       
    };
    

    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, COLOR_GIFTS, GL_FILL);


}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);


    
}

void Health::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Health::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    this->box1.x = this->position.x;
    this->box1.y = this->position.y;
    this->box1.z = this->position.z;
    this->box1.height = 16;
    this->box1.width = 16;
    this->box1.length = 16; 
    this->rotation+= speed;

}

