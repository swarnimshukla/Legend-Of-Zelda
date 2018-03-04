#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "rocks.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Water w;
int n=12,i,type=1;
Rocks rock[30];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float eye_x=0, eye_y=100, eye_z=140;
float target_x=0, target_y=80, target_z=0;
const float p = 3.14;
int rock_z, rock_x;
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
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);


    if (up) {
        ball1.position.x -= (1 *sin(ball1.rotation * (p/180))) ;
        ball1.position.z -= (1*cos(ball1.rotation * (p/180))) ;

    }
    if (down) {
       ball1.position.x += (1*sin(ball1.rotation * (p/180))) ;
       ball1.position.z += (1*cos(ball1.rotation * (p/180))) ;

    }
    if(space){
        ball1.speed = 0.5;
        ball1.flag = 1;
    }
    if(left){
        move_left();
    }
    if(right){
        move_right();
    }
        
}

void tick_elements() {
    ball1.tick();
    for(i=0;i<n;++i)
        rock[i].tick();
    for(i=0;i<n;++i)
        if(detect_collision(ball1.box, rock[i].box1))
            printf("Hello\n");

    //camera_rotation_angle += 1;
}
void move_left(){
    ball1.rotation += 0.5;
}
void move_right(){
    ball1.rotation -= 0.5;
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 1, 0 , COLOR_RED);
    w = Water( 0, 0, COLOR_BLUE);
    for( i=0;i<n;++i){
        rock_x = (rand() % (200 + 1 + 200))-200;
        rock_z = (rand() % (-70 + 1 + 300))-300;
        rock[i] = Rocks(rock_x, -7, rock_z, COLOR_BROWN);
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


int main(int argc, char **argv) {
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
            // printf("%ld\n",ball1.position.y);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    Matrices.projection = glm::perspective(45.0f, 1.0f, 100.0f, 1000.0f);
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
    angle = (ball1.rotation)*(p/180);
    if(type==1){
        eye_x = ball1.position.x + 140*sin(angle);
        eye_y = 100;
        eye_z = ball1.position.z + 140*cos(angle);

        target_x = ball1.position.x + sin(angle);
        target_y = 80;
        target_z = ball1.position.z + cos(angle);
    }
    else if(type==2){
        eye_x = ball1.position.x + 30*sin(angle + p);
        eye_y = ball1.position.y + 55.0f;
        eye_z = ball1.position.z + 30*cos(angle + p);

        target_x = ball1.position.x + 40*sin(angle + p);
        target_y = ball1.position.y + 55.0f;
        target_z = ball1.position.z + 40*cos(angle + p);
    }
    else if(type==3){
        eye_x = ball1.position.x;
        eye_y = 500;
        eye_z = ball1.position.z ;

        target_x = ball1.position.x + 1;
        target_y = ball1.position.y;
        target_z = ball1.position.z;   
    }
    else if(type==4){
        eye_x = ball1.position.x + 130 ;
        eye_y = 280;
        eye_z = ball1.position.z ;

        target_x = ball1.position.x;
        target_y = ball1.position.y;
        target_z = ball1.position.z;
    }
}