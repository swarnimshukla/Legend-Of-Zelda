#include "island.h"
#include "main.h"

Islands::Islands(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    speed = 1;
    this->box1.x = this->position.x;
    this->box1.y = this->position.y;
    this->box1.z = this->position.z;
    int i;
    GLfloat g_vertex_buffer_data[1000004];

        for(int i=0;i<10068;i++){
            g_vertex_buffer_data[i*9]=0.0f;
            g_vertex_buffer_data[i*9+1]=0.0f;
            g_vertex_buffer_data[i*9+2]=0.0f;
            if(i==0){
               g_vertex_buffer_data[i*9+3]=  0.5;
               g_vertex_buffer_data[i*9+4]= 214.0f;
               g_vertex_buffer_data[i*9+5]=0.0f;
               g_vertex_buffer_data[i*9+6] = 0.5;
               g_vertex_buffer_data[i*9+7] = (float)sin(-0.79)*g_vertex_buffer_data[i*9+5] + (float)cos(-0.79)*g_vertex_buffer_data[i*9+4];
               g_vertex_buffer_data[i*9+8] = (float)cos(-0.79)*g_vertex_buffer_data[i*9+5] - (float)sin(-0.79)*g_vertex_buffer_data[i*9+4];
            }
            else{
                g_vertex_buffer_data[i*9+3]=g_vertex_buffer_data[(i-1)*9+6];
                g_vertex_buffer_data[i*9+4]=g_vertex_buffer_data[(i-1)*9+7];
                g_vertex_buffer_data[i*9+5]=g_vertex_buffer_data[(i-1)*9+8];
                g_vertex_buffer_data[i*9+6] = 0.5;
                g_vertex_buffer_data[i*9+7] = (float)sin(-0.79)*g_vertex_buffer_data[i*9+5] + (float)cos(-0.79)*g_vertex_buffer_data[i*9+4];
                g_vertex_buffer_data[i*9+8] = (float)cos(-0.79)*g_vertex_buffer_data[i*9+5] - (float)sin(-0.79)*g_vertex_buffer_data[i*9+4];
            }
    this->object = create3DObject(GL_TRIANGLES, 1000, g_vertex_buffer_data, COLOR_ISLAND, GL_FILL);
    }

}

void Islands::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
}

void Islands::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Islands::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;

}

