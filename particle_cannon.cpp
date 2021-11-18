/*
Grant Nike
6349302
Dec 6th
COSC 3P98 Assignment #3
*/

//Header file
#include "header.h"

#define X 0
#define Y 1
#define Z 2

//Menu options
enum{MENU_SHADE,MENU_CULL,MENU_RESET, MENU_QUIT};

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
    GLfloat eye[3] = {35.0, 85.0, 170.0};
    //Where the camera is centered
    GLfloat center[3] = {0.0, 0.0, 0.0};
    //Which direction is up relative to the camera
    GLfloat up[3] = {0.0, 1.0, 0.0};
    GLfloat rotate_x = 0.0;
    GLfloat rotate_y = 0.0;
    float angle[3];
    int numb_rotations = 0;
    bool cull_enabled = true;
    bool shaded_colour = true;
} glob;
glob global;

void drawShapes(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glRotatef(global.rotate_x, 1.0, 0.0, 0.0);
    glRotatef(global.rotate_y, 0.0, 1.0, 0.0);
    glRotatef(global.angle[Z], 0.0, 0.0, 1.0);

    drawcube();
    drawPlane();

    glutSwapBuffers();
    glFlush();
}

void drawcube(void) {
    int p[][3] = {{10,10,10}, {10,-10,10}, {-10,-10,10}, {-10,10,10},
                 {10,10,-10}, {10,-10,-10}, {-10,-10,-10}, {-10,10,-10}};

    int e[][4] = {{0,3,2,1},{3,7,6,2},{7,4,5,6},{4,0,1,5}, {0,4,7,3},{1,2,6,5}};
    float c[][3] = {{1.0,0,0},{0,1.0,0},{1.0,1.0,1.0},
		 {0,0,1.0},{.6,0,.6},{0,.6,.6}};

    float singleColour[][3] = { {0.0,0.0,0.9},{0.0,0.0,0.4},{0.0,0.0,0.8},{0.0,0.0,0.6} };

  glPushMatrix();
  glTranslatef(-125.0,45.0,0.0);

  for (int i=0; i < 6; ++i) {
     glColor3fv(c[i]);
     glBegin(GL_QUADS);
        glColor3fv(singleColour[0]);
        glVertex3iv(p[e[i][0]]);
        glColor3fv(singleColour[1]);
        glVertex3iv(p[e[i][1]]);
        glColor3fv(singleColour[2]);
        glVertex3iv(p[e[i][2]]);
        glColor3fv(singleColour[3]);
        glVertex3iv(p[e[i][3]]);
     glEnd();
  }
  glPopMatrix();
}

void drawPlane(void){
    int p[][3] = {{125,0,100},{-125,0,100},{-125,0,-100},{125,0,-100},
                  {125,-25,100},{-125,-25,100},{-125,-25,-100},{125,-25,-100}};
    
    float topColours[][3] = { {0.9,0.0,0.0},{0.1,0.0,0.0},{0.8,0.0,0.0},{0.5,0.0,0.0} };
    float sideColours[][3] = { {0.0,0.9,0.0},{0.0,0.1,0.0},{0.0,0.8,0.0},{0.0,0.5,0.0} };

    //Top
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(p[3]);
        glColor3fv(topColours[1]);
        glVertex3iv(p[2]);
        glColor3fv(topColours[2]);
        glVertex3iv(p[1]);
        glColor3fv(topColours[3]);
        glVertex3iv(p[0]);
    glEnd();
    //Sides
    glBegin(GL_POLYGON);
        glColor3fv(sideColours[0]);
        glVertex3iv(p[4]);
        glColor3fv(sideColours[1]);
        glVertex3iv(p[7]);
        glColor3fv(sideColours[2]);
        glVertex3iv(p[3]);
        glColor3fv(sideColours[3]);
        glVertex3iv(p[0]);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glColor3fv(sideColours[0]);
        glVertex3iv(p[7]);
        glColor3fv(sideColours[1]);
        glVertex3iv(p[6]);
        glColor3fv(sideColours[2]);
        glVertex3iv(p[2]);
        glColor3fv(sideColours[3]);
        glVertex3iv(p[3]);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glColor3fv(sideColours[0]);
        glVertex3iv(p[6]);
        glColor3fv(sideColours[1]);
        glVertex3iv(p[5]);
        glColor3fv(sideColours[2]);
        glVertex3iv(p[1]);
        glColor3fv(sideColours[3]);
        glVertex3iv(p[2]);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glColor3fv(sideColours[0]);
        glVertex3iv(p[5]);
        glColor3fv(sideColours[1]);
        glVertex3iv(p[4]);
        glColor3fv(sideColours[2]);
        glVertex3iv(p[0]);
        glColor3fv(sideColours[3]);
        glVertex3iv(p[1]);
    glEnd();
    //Bottom
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(p[4]);
        glColor3fv(topColours[1]);
        glVertex3iv(p[5]);
        glColor3fv(topColours[2]);
        glVertex3iv(p[6]);
        glColor3fv(topColours[3]);
        glVertex3iv(p[7]);
    glEnd();
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
            global.rotate_y += 0.5;
            global.numb_rotations++;
            glutPostRedisplay();
            break;
        case 'a':
            glPushMatrix();
            global.rotate_y += -0.5;
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
    }
}
//Defines a menu accessed by right clicking the graphics window
void create_menu(){
    int main_menu = glutCreateMenu(&menu_func);
    glutAddMenuEntry("Reset",MENU_RESET);
    glutAddMenuEntry("Toggle Backface Culling", MENU_CULL);
    glutAddMenuEntry("Toggle Shading", MENU_SHADE);
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

    glutMainLoop();
    return 0;
}