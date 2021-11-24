//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PLANE 2

void definePlane(void){
    int p[][3] = {{125,0,100},{-125,0,100},{-125,0,-100},{125,0,-100},
                  {125,-25,100},{-125,-25,100},{-125,-25,-100},{125,-25,-100}};
    
    float sideColours[][3] = { {0.9,0.0,0.0},{0.1,0.0,0.0},{0.8,0.0,0.0},{0.5,0.0,0.0} };
    float topColours[][3] = { {0.0,0.6,0.0},{0.0,0.1,0.0},{0.0,0.5,0.0},{0.0,0.5,0.0} };

    glNewList(PLANE, GL_COMPILE);
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
    glEndList();
}