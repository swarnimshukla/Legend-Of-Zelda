#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z, color_t color, int c) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // this->c=c;
    speed = 1;
    this->box1.x = this->position.x;
    this->box1.y = this->position.y;
    this->box1.z = this->position.z;
    gravity = -0.1;
        if(c==1){
            static const GLfloat vertex_buffer_data[] = {
            -15.0f,-15.0f,-15.0f, // triangle 1 : begin
             -15.0f,-15.0f, 15.0f,
             -15.0f, 15.0f, 15.0f, // triangle 1 : end
             15.0f, 15.0f,-15.0f, // triangle 2 : begin
             -15.0f,-15.0f,-15.0f,
             -15.0f, 15.0f,-15.0f, // triangle 2 : end
             15.0f,-15.0f, 15.0f,
             -15.0f,-15.0f,-15.0f,
             15.0f,-15.0f,-15.0f,
             15.0f, 15.0f,-15.0f,
             15.0f,-15.0f,-15.0f,
             -15.0f,-15.0f,-15.0f,
             -15.0f,-15.0f,-15.0f,
             -15.0f, 15.0f, 15.0f,
             -15.0f, 15.0f,-15.0f,
             15.0f,-15.0f, 15.0f,
             -15.0f,-15.0f, 15.0f,
             -15.0f,-15.0f,-15.0f,
             -15.0f, 15.0f, 15.0f,
             -15.0f,-15.0f, 15.0f,
             15.0f,-15.0f, 15.0f,
             15.0f, 15.0f, 15.0f,
             15.0f,-15.0f,-15.0f,
             15.0f, 15.0f,-15.0f,
             15.0f,-15.0f,-15.0f,
             15.0f, 15.0f, 15.0f,
             15.0f,-15.0f, 15.0f,
             15.0f, 15.0f, 15.0f,
             15.0f, 15.0f,-15.0f,
             -15.0f, 15.0f,-15.0f,
             15.0f, 15.0f, 15.0f,
             -15.0f, 15.0f,-15.0f,
             -15.0f, 15.0f, 15.0f,
             15.0f, 15.0f, 15.0f,
             -15.0f, 15.0f, 15.0f,
             15.0f,-15.0f, 15.0f,
        
            10.0f, 15.0f, 0.0f,
            14.0f, 15.0f, 0.0f,
            12.0f, 33.0f, 0.0f,
                    
          -10.0f, 15.0f, 0.0f,
           -14.0f, 15.0f, 0.0f,
         -12.0f, 33.0f, 0.0f,
       

        
        };
        this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_RED, GL_FILL);
        this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 108, COLOR_BROWN, GL_FILL);
    }
    else{
        static const GLfloat vertex_buffer_data[] = {

        -30.0f,-30.0f,-30.0f, // triangle 1 : begin
             -30.0f,-30.0f, 30.0f,
             -30.0f, 30.0f, 30.0f, // triangle 1 : end
             30.0f, 30.0f,-30.0f, // triangle 2 : begin
             -30.0f,-30.0f,-30.0f,
             -30.0f, 30.0f,-30.0f, // triangle 2 : end
             30.0f,-30.0f, 30.0f,
             -30.0f,-30.0f,-30.0f,
             30.0f,-30.0f,-30.0f,
             30.0f, 30.0f,-30.0f,
             30.0f,-30.0f,-30.0f,
             -30.0f,-30.0f,-30.0f,
             -30.0f,-30.0f,-30.0f,
             -30.0f, 30.0f, 30.0f,
             -30.0f, 30.0f,-30.0f,
             30.0f,-30.0f, 30.0f,
             -30.0f,-30.0f, 30.0f,
             -30.0f,-30.0f,-30.0f,
             -30.0f, 30.0f, 30.0f,
             -30.0f,-30.0f, 30.0f,
             30.0f,-30.0f, 30.0f,
             30.0f, 30.0f, 30.0f,
             30.0f,-30.0f,-30.0f,
             30.0f, 30.0f,-30.0f,
             30.0f,-30.0f,-30.0f,
             30.0f, 30.0f, 30.0f,
             30.0f,-30.0f, 30.0f,
             30.0f, 30.0f, 30.0f,
             30.0f, 30.0f,-30.0f,
             -30.0f, 30.0f,-30.0f,
             30.0f, 30.0f, 30.0f,
             -30.0f, 30.0f,-30.0f,
             -30.0f, 30.0f, 30.0f,
             30.0f, 30.0f, 30.0f,
             -30.0f, 30.0f, 30.0f,
             30.0f,-30.0f, 30.0f,
        
            24.0f, 30.0f, 15.0f,
            26.0f, 30.0f, 15.0f,
            29.0f, 53.0f, 15.0f,
                    
          -24.0f, 30.0f, 15.0f,
           -26.0f, 30.0f, 15.0f,
         -29.0f, 53.0f, 15.0f,



    };

        this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_RED, GL_FILL);
        this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 108, COLOR_BROWN, GL_FILL);

}
}
void Monster::draw(glm::mat4 VP) {
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
    draw3DObject(this->object1);
    
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    // if(c==1){
        this->box1.x = this->position.x;
        this->box1.y = this->position.y;
        this->box1.z = this->position.z;
        this->box1.height = 30;
        this->box1.width = 30;
        this->box1.length = 30; 
    // }
    // else{
    //     this->box1.x = this->position.x;
    //     this->box1.y = this->position.y;
    //     this->box1.z = this->position.z;
    //     this->box1.height = 60;
    //     this->box1.width = 60;
    //     this->box1.length = 60;    
    // }

}

