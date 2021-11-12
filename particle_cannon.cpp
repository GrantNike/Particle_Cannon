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
enum{MENU_RESET, MENU_QUIT};

//the global structure
typedef struct {
    GLfloat screen_width = 1920.0/2;
    GLfloat screen_height = 1080.0/2;
    //Parameters for gluPerspective
    GLfloat fov = 30.0;
    GLfloat aspect_ratio = 1.5;
    GLfloat zNear = 0.1;
    GLfloat zFar = 20.0;
    //Parameters of gluLookAt i.e camera placement in scene
    GLfloat eye[3] = {5.0, 4.0, 6.0};
    GLfloat center[3] = {1.0, 1.0, 1.0};
    GLfloat up[3] = {0.0, 1.0, 0.0};
    GLfloat rotate_x = 0.0;
    GLfloat rotate_y = 0.0;
    float angle[3];
} glob;
glob global;

void drawcube(void) {
  int p[][3] = {{1,1,1}, {1,-1,1}, {-1,-1,1}, {-1,1,1},
                 {1,1,-1}, {1,-1,-1}, {-1,-1,-1}, {-1,1,-1}};

  int e[][4] = {{0,3,2,1},{3,7,6,2},{7,4,5,6},{4,0,1,5}, {0,4,7,3},{1,2,6,5}};
  float c[][3] = {{1.0,0,0},{0,1.0,0},{1.0,1.0,1.0},
		 {0,0,1.0},{.6,0,.6},{0,.6,.6}};
  int i;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glRotatef(global.rotate_x, 1.0, 0.0, 0.0);
  glRotatef(global.rotate_y, 0.0, 1.0, 0.0);
  glRotatef(global.angle[Z], 0.0, 0.0, 1.0);

  for (i=0; i < 6; ++i) {
     glColor3fv(c[i]);
     glBegin(GL_QUADS);
        glVertex3iv(p[e[i][0]]);
        glVertex3iv(p[e[i][1]]);
        glVertex3iv(p[e[i][2]]);
        glVertex3iv(p[e[i][3]]);
     glEnd();
  }
  glutSwapBuffers();
  glFlush();
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
            global.rotate_y += 0.5;
            glutPostRedisplay();
            break;
        case 'a':
            global.rotate_y += -0.5;
            glutPostRedisplay();
            break;
        case 'w':
            global.rotate_x += 0.5;
            glutPostRedisplay();
            break;
        case 's':
            global.rotate_x += -0.5;
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
            break;
    }
}
//Defines a menu accessed by right clicking the graphics window
void create_menu(){
    int main_menu = glutCreateMenu(&menu_func);
    glutAddMenuEntry("Reset",MENU_RESET);
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
    glutDisplayFunc(drawcube);
    glutIdleFunc(drawcube);

    glMatrixMode(GL_PROJECTION);
    //global.aspect_ratio = glutGet(GLUT_WINDOW_WIDTH/HEIGHT);
    gluPerspective(global.fov,global.aspect_ratio,global.zNear,global.zFar);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(
        global.eye[0],global.eye[1],global.eye[2], 
        global.center[0],global.center[1],global.center[2], 
        global.up[0],global.up[1],global.up[2]
    );
    //glClearColor(1.0,1.0,1.0,0.0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}