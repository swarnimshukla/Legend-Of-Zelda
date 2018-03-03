#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    gravity= -0.015;    
    flag=0;
    i=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        
        8.0f, 4.0f, -12.0f,
        -8.0f,4.0f, -12.0f,
        0.0f,4.0f, -18.0f,

        -8.0f, 4.0f, -12.0f,
        -8.0f,-4.0f,-12.0f,
        0.0f, 4.0f, -18.0f,

        8.0f, 4.0f, -12.0f,
        8.0f,-4.0f,-12.0f,
        0.0f, 4.0f, -18.0f,

        8.0f,-4.0f,-12.0f,
        -8.0f, -4.0f, -12.0f,
        0.0f, 4.0f, -18.0f,

        
        -8.0f,-4.0f, 12.0f,
         8.0f, 4.0f, 12.0f,
        -8.0f, 4.0f, 12.0f,
        -8.0f,-4.0f, 12.0f,
         8.0f, 4.0f, 12.0f,
         8.0f,-4.0f, 12.0f,

         8.0f, 4.0f, 12.0f,
         8.0f,-4.0f,-12.0f,
         8.0f,-4.0f, 12.0f,
         8.0f, 4.0f, 12.0f,
         8.0f,-4.0f,-12.0f,
         8.0f, 4.0f,-12.0f,

        8.0f, 4.0f,-12.0f,
        -8.0f,-4.0f,-12.0f,
         8.0f,-4.0f,-12.0f,
         8.0f, 4.0f,-12.0f,
        -8.0f,-4.0f,-12.0f,
        -8.0f, 4.0f,-12.0f,

        -8.0f,-4.0f,-12.0f,
        -8.0f, 4.0f, 12.0f,
        -8.0f, 4.0f,-12.0f,
        -8.0f,-4.0f,-12.0f,
        -8.0f, 4.0f, 12.0f,
        -8.0f,-4.0f, 12.0f,

        -8.0f,-4.0f, 12.0f,
         8.0f,-4.0f,-12.0f,
         8.0f,-4.0f, 12.0f,
        -8.0f,-4.0f, 12.0f,
         8.0f,-4.0f,-12.0f,
        -8.0f,-4.0f,-12.0f,

        
        
    };

    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data + 9, COLOR_GREEN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data + 18, COLOR_GREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data + 27, COLOR_GREEN, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 36, COLOR_RED, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 54, COLOR_YELLOW, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 72, COLOR_RED, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 90, COLOR_YELLOW, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 108, COLOR_LIME, GL_FILL);
    
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
    draw3DObject(this->object8);
    draw3DObject(this->object9);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->rotation += speed;
    if(flag==1 && this->position.y >-4.1){
        this->position.y += speed;
        speed += gravity;
    }
    if(this->position.y<= -4.1){
        while(this->position.y<0)
            this->position.y += 0.2;
        flag=0;
    }
    
    
    
    // this->position.x -= speed;
    // this->position.y -= speed;
}

