#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "rocks.h"
#include "cannon.h"
#include "barrel.h"
#include "gifts.h"
#include "monster.h"
#include "fireball.h"
#include "health.h"
#include "booster.h"
#include "island.h"
#include "unistd.h"
#include "sys/types.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Water w;
int n=20,i,type=1, pid;
Rocks rock[30];
Cannon can;
Barrel bar[30];
Gifts gift[32];
int health=100, score=0;
Health heal[6];
Monster monster[30];
Booster boos;
Islands island;
int factor=1, count=10;
Fireball fire;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float eye_x=0, eye_y=120, eye_z=150;
float target_x=0, target_y=80, target_z=0;
const float p = 3.14;
int rock_z, rock_x, barrel_x, barrel_z, monster_x, monster_z, health_x, health_z;
float angle;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( eye_x, eye_y, eye_z );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    w.draw(VP);
    for(i=0;i<n;++i)
        rock[i].draw(VP);
    can.draw(VP);
    for(i=1;i<=n;++i){
        bar[i].draw(VP);
        gift[i].draw(VP);
    }
    for(i=0;i<n;++i)
        monster[i].draw(VP);

    fire.draw(VP);
     for(i=0;i<5;++i)
        heal[i].draw(VP);

    boos.draw(VP);
    island.draw(VP);

}

void displayScore(){
    string a = "Score : ";
    string b = to_string(score);
    b = a+b;
    string c = " Health : ";
    string d= to_string(health);
    d = c + d;
    b = b + d;

    glfwSetWindowTitle(window, const_cast<char*>(b.c_str()));
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f= glfwGetKey(window, GLFW_KEY_F);
    int d= glfwGetKey(window, GLFW_KEY_D);
    int a= glfwGetKey(window, GLFW_KEY_A);



    if (up) {
        ball1.position.x -= (factor*2.5 *sin(ball1.rotation * (p/180))) ;
        ball1.position.z -= (factor*2.5*cos(ball1.rotation * (p/180))) ;
        can.position.x -= (factor*2.5 *sin(ball1.rotation * (p/180)));
        can.position.z -= (factor*2.5 *cos(ball1.rotation * (p/180)));
        if(fire.position.y<=-8){
            fire.position.x -= (factor*2.5 *sin(ball1.rotation * (p/180)));
            fire.position.z -= (factor*2.5 *cos(ball1.rotation * (p/180)));
        }

    }
    if (down) {
       ball1.position.x += (factor*2.5*sin(ball1.rotation * (p/180))) ;
       ball1.position.z += (factor*2.5*cos(ball1.rotation * (p/180))) ;
       can.position.x += (factor*2.5 *sin(ball1.rotation * (p/180)));
       can.position.z += (factor*2.5 *cos(ball1.rotation * (p/180)));
       if(fire.position.y<=-8){
            fire.position.x += (factor*2.5 *sin(ball1.rotation * (p/180)));
            fire.position.z += (factor*2.5 *cos(ball1.rotation * (p/180)));
        }
    }
    if(space){
        if(ball1.position.y <=2){
            ball1.speed = 3;
            ball1.flag = 1;
            can.speed = 3;
            can.flag = 1;
        }   

    }
    if(left){
        move_left();
    }
    if(right){
        move_right();
    }
    if(d)
        move_cannon_right();
    if(a)
        move_cannon_left();
    if(f && fire.position.y <= -30){
        fire.speedy = 4.5;
        fire.flag=1;
        fire.speedx = -4.5 * sin(fire.rotation * (p/180));
        fire.speedz = -4.5 * cos(fire.rotation * (p/180));
     }
        
}

void tick_elements() {
    ball1.tick();
    boos.tick();

    for(i=0;i<n;++i){
        monster[i].tick();
        gift[i].tick();

    }
    for(i=0;i<=5;++i)
        heal[i].tick();
    for(i=0;i<=n;++i)
        rock[i].tick();
    for(i=0;i<=n;++i)
        if(detect_collision(ball1.box, rock[i].box1)){
            rock[i].position.y=-100;
            health -= 5;

        }
    can.tick();    
    for(int i=0;i<n;++i){
        if(abs(monster[i].position.x - ball1.position.x)<600 && abs(monster[i].position.z - ball1.position.z)<600){
            if(monster[i].position.x > ball1.position.x ){
               monster[i].position.x -= 0.3 *(i%3+1);
            }
            else if(monster[i].position.x < ball1.position.x){
               monster[i].position.x += 0.3 *(i%3+1);
            }
            if(monster[i].position.z > ball1.position.z ){
               monster[i].position.z -= 0.3 *(i%3+1);
            }
            else if(monster[i].position.z < ball1.position.z){
               monster[i].position.z += 0.3 *(i%3+1);
            }
        }
    }
    if(fire.flag==1){
        fire.tick();
        if(fire.position.y<-30){
            fire.position.y=-30;
            fire.position.x= can.position.x;
            fire.position.z= can.position.z-10;

        }
    }
    for(int i=0;i<=n;++i){
        if(detect_collision(ball1.box, gift[i].b)){
            gift[i].position.x = -1000;
            gift[i].position.y = -1000;
            gift[i].position.z = -1000;

            if(i%3==0){
                score+=10;
                break;
            }
            else if(i%3==1){
                score+=20;
                break;
            }
            else if(i%3==2){
                score+=30;
                break;
            }

        }
    }
    for(int i=0;i<n;++i){
        if(detect_collision(fire.box1, monster[i].box1)){
            if(i==15){
                monster[i].position.y=-100;
                score +=50;
                boos.position.x=monster[i].position.x;
                boos.position.y=monster[i].position.y  + 130;
                boos.position.z=monster[i].position.z;
            }
            else{
                monster[i].position.y=-100;
                score +=50;
            }
        }
    }
    for(int i=0;i<n;++i){
        if(detect_collision(ball1.box, monster[i].box1)){
            monster[i].position.y=-100;
            health -= 10;

        }

    }
    for(int i=0;i<5;++i){
        if(detect_collision(ball1.box, heal[i].box1)){
            heal[i].position.y=-100;
            health += 50;
        }
    }


    if(detect_collision(ball1.box, boos.box1)){
        boos.position.y=-100;
        factor=2;

    }
    if(count>0){
        ball1.position.y-=0.1;
        count--;
    }
    else{
        ball1.position.y+=0.1;
        if(count==-10)
            count=10;
        count--;
    }


}
void move_left(){
    ball1.rotation += factor*0.5;
    can.rotation += factor*0.5;
    fire.rotation = can.rotation;
}
void move_right(){
    ball1.rotation -= factor*0.5;
    can.rotation -= factor*0.5;
    fire.rotation = can.rotation;

}
void move_cannon_left(){
    can.rotation += factor*0.5;
    fire.rotation = can.rotation;

}
void move_cannon_right(){
    can.rotation -= factor*0.5;
    fire.rotation = can.rotation;

}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 1, 0 , COLOR_RED);
    w = Water( 0, 0, COLOR_BLUE);
    for( i=0;i<50;++i){
        rock_x = (rand() % (-300 + 1 + 1800))-1800;
        rock_z = (rand() % (-300 + 1 + 1200))-1200;
        rock[i] = Rocks(rock_x, -7, rock_z, COLOR_BROWN);
    }
    can = Cannon(0,0,0, COLOR_CANNON);
    for(i=0;i<=n;++i){
        barrel_x = (rand() % (-300 + 1 + 1800))-1800;
        barrel_z = (rand() % (-950 + 1 + 2200))-2200;
        bar[i] = Barrel(barrel_x, -17, barrel_z, COLOR_BARREL);
        if(i%3==0)
            gift[i] = Gifts(barrel_x, 33, barrel_z, COLOR_GIFTS);
        else if(i%3==1)
            gift[i] = Gifts(barrel_x, 33, barrel_z, COLOR_RED);
        else if(i%3==2)
            gift[i] = Gifts(barrel_x, 33, barrel_z, COLOR_FUCHSIA);

    }   
    boos = Booster(-1000, -1000, -1000, COLOR_RED);
    island = Islands(0,-2, -5000, COLOR_ISLAND);

    for(i=0; i<n; ++i){
        if(i!=15){
            monster_x = ((((i+1)*rand()+i*584)%10000)/10) + 30;
            monster_z = (rand() % (-450 + 1 + 5200))-5200;
            monster[i] = Monster(monster_x, 0, monster_z, COLOR_MONSTERS,1);
        }
        else{
            monster_x = ((((i+1)*rand()+i*584)%10000)/10) + 30;
            monster_z = (rand() % (-450 + 1 + 4200))-4200;
            monster[i] = Monster(200, 0, -800, COLOR_MONSTERS,2);
        }
    }
    fire = Fireball(can.position.x, -30, can.position.z, COLOR_GIFTS);

     for(i=0;i<5;++i){
        health_x = ((((i+1)*rand()+i*584)%10000)/10) + 30;
        health_z = (rand() % (-450 + 1 + 5200))-5200;
        heal[i] = Health(health_x, 35, health_z, COLOR_GIFTS);

     }



    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
        
}
void choose_camera(){
    if(type!=5){
            type++;
    }
    else if(type==5){
        type=1;
    }
}
void camera_change(){
    if(type==1){
        eye_x = ball1.position.x + 150*sin(ball1.rotation*(p/180));
        eye_y = 100;
        eye_z = ball1.position.z + 150*cos(ball1.rotation*(p/180));

        target_x = ball1.position.x + sin(ball1.rotation*(p/180));
        target_y = 80;
        target_z = ball1.position.z + cos(ball1.rotation*(p/180));
    }
    else if(type==2){
        eye_x = ball1.position.x;
        eye_y = 800;
        eye_z = ball1.position.z ;

        target_x = ball1.position.x + 1;
        target_y = ball1.position.y;
        target_z = ball1.position.z;   


    }
    else if(type==3){
        eye_x = ball1.position.x + 130 ;
        eye_y = 580;
        eye_z = ball1.position.z ;

        target_x = ball1.position.x;
        target_y = ball1.position.y;
        target_z = ball1.position.z;


    }
    else if(type==4){
        eye_x = ball1.position.x + sin(ball1.rotation*(p/180) + p);
        eye_y = ball1.position.y + 55.0f;
        eye_z = ball1.position.z + cos(ball1.rotation*(p/180) + p);

        target_x = ball1.position.x + 30*sin(ball1.rotation*(p/180) + p);
        target_y = ball1.position.y + 55.0f;
        target_z = ball1.position.z + 30*cos(ball1.rotation*(p/180) + p);
        
    }
}


int main(int argc, char **argv) {

    // pid = fork();
    // audio_init();

    // if(pid >= 0){
        srand(time(0));
        int width  = 600;
        int height = 600;

        window = initGLFW(width, height);

        initGL (window, width, height);


        /* Draw in loop */
        while (!glfwWindowShouldClose(window)) {
                // Process timers

            if (t60.processTick()) {
                // 60 fps
                // OpenGL Draw commands
                draw();
                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);

                tick_elements();
                tick_input(window);
                camera_change();
                displayScore();
            }

            // Poll for Keyboard and mouse events
            glfwPollEvents();
        }

        quit(window);
    // }
    // else{
    //     printf("diosdf\n");
    //     while(true) audio_play();
    // }
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    Matrices.projection = glm::perspective(45.0f, 1.0f, 100.0f, 1000.0f);
}
