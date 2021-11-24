/*
Grant Nike
6349302
Dec 6th
COSC 3P98 Assignment #3
*/

//Header file
#include "header.h"
//Particle namespace file
#include "particle.cpp"
//Files for shape definitions
#include "cannon.cpp"
#include "plane.cpp"

#define X 0
#define Y 1
#define Z 2

//Menu options
enum{MENU_PARTICLE,MENU_RATIO,MENU_FOV,MENU_SHADE,MENU_CULL,MENU_RESET, MENU_QUIT};

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
    //particles::particle part;
    std::vector<particles::particle> particle_arr;
} glob;
glob global;
//Initialize some particles
void initParticles(int numb_particles){
    for(int i=0;i<numb_particles;i++){
        //Initialize parameters for new particle
        GLfloat speed = 1.0;
        std::string shape = "cube";
        GLfloat x = -110.0;
        GLfloat y = 45.0;
        GLfloat z = 0.0;
        //Create particle and set its parameters
        particles::particle part;
        part.position.x = x;
        part.position.y = y;
        part.position.z = z;
        part.speed = speed;
        part.shape = shape;
        //Add particle to global particle pool
        global.particle_arr.push_back(part);
    }
}
//Draw all entities to the window
void drawShapes(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glRotatef(global.rotate_x, 1.0, 0.0, 0.0);
    glRotatef(global.rotate_y, 0.0, 1.0, 0.0);
    glRotatef(global.angle[Z], 0.0, 0.0, 1.0);

    glCallList(CANNON);
    glCallList(PLANE);
    
    for(int i=0;i<global.particle_arr.size();i++){
        //If particle has been killed, remove it from vector
        if(global.particle_arr[i].kill){
            global.particle_arr.erase(global.particle_arr.begin()+i);
            continue;
        }
        //Update the particle's position
        global.particle_arr[i].update_position();
        //Draw the particle
        shapes::drawCube(global.particle_arr[i].position.x,global.particle_arr[i].position.y,global.particle_arr[i].position.z);
        //std::cout<<global.particle_arr[0].position.x<<","<<global.particle_arr[0].position.y<<","<<global.particle_arr[0].position.z<<std::endl;
    }

    glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
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
            glutPostRedisplay;
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
            global.angle[X] = 0.0;
            global.angle[Y] = 0.0;
            global.angle[Z] = 0.0;
            global.rotate_x = 0.0;
            global.rotate_y = 0.0;
            for(int i=0;i<global.numb_rotations;i++){
                glPopMatrix();
            }
            global.numb_rotations = 0;
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
            initParticles(1);
        break;
        case MENU_FOV:
            std::cout<<"Current FOV value: "<<global.fov<<std::endl;
            std::cout<<"Enter new value for FOV: ";
            try{
                float new_fov;
                std::cin>>new_fov;
                if(std::cin.fail()) throw 1;
                if(new_fov < 1 || new_fov > 1000) throw 2;
                global.fov = new_fov;
            }
            catch(int err){
                //Clear error flags
                std::cin.clear();
                //Clear input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(err == 1){
                    std::cout<<"Invalid input. FOV must be a number."<<std::endl;
                }
                if(err == 2){
                    std::cout<<"Invalid input. FOV must be greater than 0 and less than 1000."<<std::endl;
                }
            }
        break;
        case MENU_RATIO:
        std::cout<<"Current aspect ratio value: "<<global.aspect_ratio<<std::endl;
        std::cout<<"Enter new value for aspect ratio: ";
        try{
            float new_aspect_ratio;
            std::cin>>new_aspect_ratio;
            if(std::cin.fail()) throw 1;
            if(new_aspect_ratio < 0.1 || new_aspect_ratio > 5) throw 2;
            global.aspect_ratio = new_aspect_ratio;
        }
        catch(int err){
            //Clear error flags
            std::cin.clear();
            //Clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(err == 1){
                std::cout<<"Invalid input. Aspect ratio must be a number."<<std::endl;
            }
            else if(err == 2){
                std::cout<<"Invalid input. Aspect ratio must be greater than 0.1 and less than 5."<<std::endl;
            }
        }
        break;
    }
}
//Defines a menu accessed by right clicking the graphics window
void create_menu(){
    //Menu for changing perspective parameters
    int perspective_menu = glutCreateMenu(&menu_func);
    glutAddMenuEntry("Change FOV", MENU_FOV);
    glutAddMenuEntry("Change aspect ratio", MENU_RATIO);
    //Main right click menu
    int main_menu = glutCreateMenu(&menu_func);
    glutAddMenuEntry("Reset",MENU_RESET);
    glutAddMenuEntry("New Particle",MENU_PARTICLE);
    //glutAddSubMenu("Perspective Parameters", perspective_menu);
    glutAddMenuEntry("Toggle Shading", MENU_SHADE);
    glutAddMenuEntry("Toggle Backface Culling", MENU_CULL);
    glutAddMenuEntry("Quit", MENU_QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//Prints the key and its function to the terminal
void key_commands(){
    std::cout<<"Q = Quit"<<std::endl;
}

int main (int argc, char **argv){
    glutInit(&argc,argv);
    glutInitWindowSize(global.screen_width,global.screen_height);
    //Enable z buffering, must clear buffer when drawing a new frame
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Particle Cannon");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    key_commands();
    create_menu();
    glutDisplayFunc(drawShapes);
    glutIdleFunc(drawShapes);

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

    glutMainLoop();
    return 0;
}