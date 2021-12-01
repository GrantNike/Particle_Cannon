/*
Grant Nike
6349302
Dec 6th
COSC 3P98 Assignment #3
A 3D Graphics Application which implements a 'Particle Cannon'

Note: Uses code from 'rotate2b.c', 'rotate_light_displist.c', and 'cube_perc.c'
from code examples page by Brian J. Ross
*/

/*
Still to be done:
14. lighting and materials
18. different shapes(colours already done)
15. collide with objects on ground, use fast distance
*/

//Header file contains all other includes, and function declarations
#include "header.h"
//For rotation about axes
#define X 0
#define Y 1
#define Z 2

//Menu options
enum{MENU_LIGHTING,MENU_HOLE,MENU_SPRAY, MENU_POLYGON,MENU_WIREFRAME,MENU_PARTICLE,MENU_RATIO,MENU_FOV,MENU_SHADE,MENU_CULL,MENU_RESET, MENU_QUIT};

//the global structure
typedef struct {
    GLfloat screen_width = 1920.0/2;
    GLfloat screen_height = 1080.0/2;
    //Parameters for gluPerspective
    GLfloat fov = 100.0;
    GLfloat aspect_ratio = 1.5;
    GLfloat zNear = 0.1;
    GLfloat zFar = 500.0;
    //Parameters of gluLookAt i.e camera placement in scene
    GLfloat eye[3] = {35.0, 100.0, 150.0};
    //Where the camera is centered
    GLfloat center[3] = {0.0, 0.0, 0.0};
    //Which direction is up relative to the camera
    GLfloat up[3] = {0.0, 1.0, 0.0};
    GLfloat rotate_x = 0.0;
    GLfloat rotate_y = 0.0;
    float angle[3];
    //For resetting image to starting position
    int numb_rotations = 0;
    //For toggling culling and shading
    bool cull_enabled = true;
    bool shaded_colour = true;
    //Pool of particles to be drawn to window
    std::vector<particles::particle> particle_arr;
    //For toggling constant stream of particles
    bool const_stream = false;
    //For swiching between polygon, wireframe, and points
    std::string draw_type = "polygon";
    //For toggling between high spray and low spray
    bool high_spray = false;
    //For toggling square hole in center of ground
    bool square_hole = false;
    //For toggling lighting
    bool lighting = true;
} glob;
glob global;

void myLightInit() {
   GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
   GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat position[] = {1.0, 1.0, 1.0, 0.0};
   GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat local_view[] = {0.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glEnable(GL_LIGHTING);   /* turns on lighting */
   glEnable(GL_LIGHT0);     /* turns on light 0  */

   glEnable(GL_NORMALIZE);
}
//Initialize some particles
void init_particles(int numb_particles){
    //Initialize parameters for new particles
    GLfloat x = -115.0;
    GLfloat y = 45.0;
    GLfloat z = 0.0;
    for(int i=0;i<numb_particles;i++){
        //Create particle and set its starting position
        particles::particle part(x,y,z,global.high_spray);
        //Add particle to global particle pool
        global.particle_arr.push_back(part);
    }
}
//Draw all entities to the window
void draw_shapes(){
    //Clear buffer to prepare for new image
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //Rotate scene based on user input
    glRotatef(global.rotate_x, 1.0, 0.0, 0.0);
    glRotatef(global.rotate_y, 0.0, 1.0, 0.0);
    glRotatef(global.angle[Z], 0.0, 0.0, 1.0);
    //Draw cannon
    glCallList(CANNON);
    //Draw plane
    if(global.square_hole) glCallList(PLANE_HOLE);
    else glCallList(PLANE);
    //Remove excess particles
    for(int i=0;i<global.particle_arr.size();i++){
        //If particle has been killed, remove it from vector
        if(global.particle_arr[i].kill){
            global.particle_arr.erase(global.particle_arr.begin()+i);
        }
    }
    //Create a new particle if user has enabled constant particle stream
    if(global.const_stream){
        init_particles(1);
    }
    //Draw particles to screen
    for(int i=0;i<global.particle_arr.size();i++){
        //Update the particle's position
        global.particle_arr[i].update_position(global.square_hole);
        if(global.draw_type == "polygon"){
            shapes::drawCube(global.particle_arr[i]);
        }
        //Draw the particle
        else if(global.draw_type == "wireframe"){
            shapes::drawCubeWire(global.particle_arr[i]);
        }
    }
    //Display new scene
    glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}
//Reset orientation of scene
void reset_orientation(){
    global.angle[X] = 0.0;
    global.angle[Y] = 0.0;
    global.angle[Z] = 0.0;
    global.rotate_x = 0.0;
    global.rotate_y = 0.0;
    for(int i=0;i<global.numb_rotations;i++){
        glPopMatrix();
    }
    global.numb_rotations = 0;
}
//Clear all particles from scene
void reset_particles(){
    global.particle_arr.clear();
}
//Reset all parameters of scene to inital values
void reset_scene(){
    reset_orientation();
    reset_particles();
}
//Glut mouse function to handle mouse inputs
void mouse(int btn, int state, int x, int y) {
    float scale_factor = 1.15;
    //Mouse wheel scroll up
    if(btn == 3){
        if(state == GLUT_UP) return;
        //Zoom in perspective
        glMatrixMode(GL_PROJECTION_MATRIX);
        glScalef(scale_factor,scale_factor,scale_factor);
    }
    //Mouse wheel scroll down
    if(btn == 4){
        if(state == GLUT_UP) return;
        //Zoom out perspective
        glMatrixMode(GL_PROJECTION_MATRIX);
        float scale_down = 1/scale_factor;
        glScalef(scale_down,scale_down,scale_down);
    }
   
}
//Glut keyboard function to handle keyboard inputs
void keyboard(unsigned char key, int x, int y){
    switch (key){
        //Quit
        case 0x1B:
        case 'q':
        case 'Q':
            exit(0);
            break;
        case 'd':
            glPushMatrix();
            global.rotate_y += -0.5;
            global.numb_rotations++;
            glutPostRedisplay();
            break;
        case 'a':
            glPushMatrix();
            global.rotate_y += 0.5;
            global.numb_rotations++;
            glutPostRedisplay();
            break;
        case 'w':
            glPushMatrix();
            global.rotate_x += 0.5;
            global.numb_rotations++;
            glutPostRedisplay();
            break;
        case 's':
            glPushMatrix();
            global.rotate_x += -0.5;
            global.numb_rotations++;
            glutPostRedisplay();
            break;
        //Single particle shot
        case 'E':
        case 'e':
            init_particles(1);
        break;
        case 'F':
        case 'f':
            if(global.const_stream){
                global.const_stream = false;
            }
            else{
                global.const_stream = true;
            }
        break;
    }
}
//Defines what each menu function does
void menu_func(int value){
    switch(value){
        //Close the program
        case MENU_QUIT:
            exit(0);
        break;
        case MENU_RESET:
            reset_scene();
        break;
        case MENU_CULL:
            if(global.cull_enabled){
                glDisable(GL_CULL_FACE);
                global.cull_enabled = false;
                std::cout<<"Backface culling disabled"<<std::endl;
            }
            else{
                glEnable(GL_CULL_FACE);
                global.cull_enabled = true;
                std::cout<<"Backface culling enabled"<<std::endl;
            }
        break;
        case MENU_SHADE:
            if(global.shaded_colour){
                glShadeModel(GL_FLAT);
                global.shaded_colour = false;
                std::cout<<"Flat shading enabled"<<std::endl;
            }
            else{
                glShadeModel(GL_SMOOTH);
                global.shaded_colour = true;
                std::cout<<"Gouraud shading enabled"<<std::endl;
            }
        break;
        case MENU_PARTICLE:
            init_particles(1);
        break;
        case MENU_POLYGON:
            global.draw_type = "polygon";
        break;
        case MENU_WIREFRAME:
            global.draw_type = "wireframe";
        break;
        case MENU_SPRAY:
            if(global.high_spray){
                global.high_spray = false;
                std::cout<<"Spray toggled to low spray"<<std::endl;
            }
            else{
                global.high_spray = true;
                std::cout<<"Spray toggled to high spray"<<std::endl;
            }
        break;
        case MENU_HOLE:
            if(global.square_hole){
                global.square_hole = false;
            }
            else{
                global.square_hole = true;
            }
        break;
        case MENU_LIGHTING:
            if(global.lighting){
                global.lighting = false;
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
            }
            else{
                global.lighting = true;
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }
        break;
    }
}
//Defines a menu accessed by right clicking the graphics window
void create_menu(){
    int draw_type_menu = glutCreateMenu(&menu_func);
    glutAddMenuEntry("Polygon", MENU_POLYGON);
    glutAddMenuEntry("Wireframe",MENU_WIREFRAME);
    //Main right click menu
    int main_menu = glutCreateMenu(&menu_func);
    glutAddMenuEntry("Reset",MENU_RESET);
    glutAddMenuEntry("New Particle",MENU_PARTICLE);
    glutAddMenuEntry("Toggle Lighting",MENU_LIGHTING);
    glutAddMenuEntry("Toggle Square Hole",MENU_HOLE);
    glutAddMenuEntry("Toggle Particle Spray",MENU_SPRAY);
    glutAddSubMenu("Particle Render Type", draw_type_menu);
    glutAddMenuEntry("Toggle Shading", MENU_SHADE);
    glutAddMenuEntry("Toggle Backface Culling", MENU_CULL);
    glutAddMenuEntry("Quit", MENU_QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//Prints the key and its function to the terminal
void key_commands(){
    std::cout<<"E = Single Particle Shot"<<std::endl;
    std::cout<<"Q = Quit"<<std::endl;
}

int main (int argc, char **argv){
    //Initialize seed for random number generation
    srand(time(NULL));
    glutInit(&argc,argv);
    glutInitWindowSize(global.screen_width,global.screen_height);
    //Enable z buffering, must clear buffer when drawing a new frame
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Particle Cannon");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    key_commands();
    create_menu();
    glutDisplayFunc(draw_shapes);
    glutIdleFunc(draw_shapes);

    glMatrixMode(GL_PROJECTION);
    float width = glutGet(GLUT_WINDOW_WIDTH);
    float height = glutGet(GLUT_WINDOW_HEIGHT);
    //global.aspect_ratio = width/height;
    //std::cout<<global.aspect_ratio;
    gluPerspective(global.fov,global.aspect_ratio,global.zNear,global.zFar);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(
        global.eye[0],global.eye[1],global.eye[2], 
        global.center[0],global.center[1],global.center[2], 
        global.up[0],global.up[1],global.up[2]
    );
    //glClearColor(1.0,1.0,1.0,0.0);

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW); 
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    defineCannon();
    definePlane();
    definePlaneHole();
    myLightInit();

    glutMainLoop();
    return 0;
}