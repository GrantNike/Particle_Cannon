//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define CANNON 1

void defineCannon(void) {
    int p[][3] = {{10,10,10}, {10,-10,10}, {-10,-10,10}, {-10,10,10},
                 {10,10,-10}, {10,-10,-10}, {-10,-10,-10}, {-10,10,-10}};

    int e[][4] = {{0,3,2,1},{3,7,6,2},{7,4,5,6},{4,0,1,5}, {0,4,7,3},{1,2,6,5}};
    float c[][3] = {{1.0,0,0},{0,1.0,0},{1.0,1.0,1.0},
		 {0,0,1.0},{.6,0,.6},{0,.6,.6}};

    float singleColour[][3] = { {0.0,0.0,0.9},{0.0,0.0,0.4},{0.0,0.0,0.8},{0.0,0.0,0.6} };

  
  glNewList(CANNON, GL_COMPILE);
  //Move cannon to position
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
  glEndList();
}