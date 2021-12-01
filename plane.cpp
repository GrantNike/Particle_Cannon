//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PLANE 2
#define PLANE_HOLE 3

void definePlane(void){
    int p[][3] = {{125,0,100},{-125,0,100},{-125,0,-100},{125,0,-100},
                  {125,-25,100},{-125,-25,100},{-125,-25,-100},{125,-25,-100}};
    
    float topColours[][3] = { {0.9,0.0,0.0},{0.1,0.0,0.0},{0.8,0.0,0.0},{0.5,0.0,0.0} };
    float sideColours[][3] = { {0.0,0.6,0.0},{0.0,0.3,0.0},{0.0,0.5,0.0},{0.0,0.4,0.0} };
    //float sideColours[][3] = { {0.0,0.4,0.0},{0.0,0.1,0.0},{0.0,0.3,0.0},{0.0,0.2,0.0} };
    

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

void definePlaneHole(void){
    int p[][3] = {{125,0,100},{-125,0,100},{-125,0,-100},{125,0,-100},
                  {125,-25,100},{-125,-25,100},{-125,-25,-100},{125,-25,-100}};
    int rect1[][3] = {{125,0,100},{-125,0,100},{-125,0,50},{125,0,50},
                      {125,-25,100},{-125,-25,100},{-125,-25,50},{125,-25,50}};
    int rect2[][3] = {{125,0,-50},{-125,0,-50},{-125,0,-100},{125,0,-100},
                      {125,-25,-50},{-125,-25,-50},{-125,-25,-100},{125,-25,-100}};
    int rect3[][3] = {{-50,0,50},{-125,0,50},{-125,0,-50},{-50,0,-50},
                      {-50,-25,50},{-125,-25,50},{-125,-25,-50},{-50,-25,-50}};
    int rect4[][3] = {{125,0,50},{50,0,50},{50,0,-50},{125,0,-50},
                      {125,-25,50},{50,-25,50},{50,-25,-50},{125,-25,-50}};
    
    float topColours[][3] = { {0.9,0.0,0.0},{0.1,0.0,0.0},{0.8,0.0,0.0},{0.5,0.0,0.0} };
    float sideColours[][3] = { {0.0,0.6,0.0},{0.0,0.3,0.0},{0.0,0.5,0.0},{0.0,0.4,0.0} };
    //float sideColours[][3] = { {0.0,0.4,0.0},{0.0,0.1,0.0},{0.0,0.3,0.0},{0.0,0.2,0.0} };
    

    glNewList(PLANE_HOLE, GL_COMPILE);
    //Top 1
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect1[3]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect1[2]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect1[1]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect1[0]);
    glEnd();
    //Top 2
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect2[3]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect2[2]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect2[1]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect2[0]);
    glEnd();
    //Top 3
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect3[3]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect3[2]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect3[1]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect3[0]);
    glEnd();
    //Top 4
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect4[3]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect4[2]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect4[1]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect4[0]);
    glEnd();
    //Interior sides
    glBegin(GL_QUADS);
        glColor3fv(sideColours[0]);
        glVertex3iv(rect1[7]);
        glColor3fv(sideColours[1]);
        glVertex3iv(rect1[6]);
        glColor3fv(sideColours[2]);
        glVertex3iv(rect1[2]);
        glColor3fv(sideColours[3]);
        glVertex3iv(rect1[3]);
    glEnd();
    //Interior sides
    glBegin(GL_QUADS);
        glColor3fv(sideColours[0]);
        glVertex3iv(rect2[5]);
        glColor3fv(sideColours[1]);
        glVertex3iv(rect2[4]);
        glColor3fv(sideColours[2]);
        glVertex3iv(rect2[0]);
        glColor3fv(sideColours[3]);
        glVertex3iv(rect2[1]);
    glEnd();
    //Interior sides
    glBegin(GL_QUADS);
        glColor3fv(sideColours[0]);
        glVertex3iv(rect3[4]);
        glColor3fv(sideColours[1]);
        glVertex3iv(rect3[7]);
        glColor3fv(sideColours[2]);
        glVertex3iv(rect3[3]);
        glColor3fv(sideColours[3]);
        glVertex3iv(rect3[0]);
    glEnd();
    //Interior sides
    glBegin(GL_QUADS);
        glColor3fv(sideColours[0]);
        glVertex3iv(rect4[6]);
        glColor3fv(sideColours[1]);
        glVertex3iv(rect4[5]);
        glColor3fv(sideColours[2]);
        glVertex3iv(rect4[1]);
        glColor3fv(sideColours[3]);
        glVertex3iv(rect4[2]);
    glEnd();
    //Sides
    glBegin(GL_QUADS);
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
    glBegin(GL_QUADS);
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
    glBegin(GL_QUADS);
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
    glBegin(GL_QUADS);
        glColor3fv(sideColours[0]);
        glVertex3iv(p[5]);
        glColor3fv(sideColours[1]);
        glVertex3iv(p[4]);
        glColor3fv(sideColours[2]);
        glVertex3iv(p[0]);
        glColor3fv(sideColours[3]);
        glVertex3iv(p[1]);
    glEnd();
    //Bottom 1
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect1[4]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect1[5]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect1[6]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect1[7]);
    glEnd();
    //Bottom 2
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect2[4]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect2[5]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect2[6]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect2[7]);
    glEnd();
    //Bottom 3
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect3[4]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect3[5]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect3[6]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect3[7]);
    glEnd();
    //Bottom 4
    glBegin(GL_POLYGON);
        glColor3fv(topColours[0]);
        glVertex3iv(rect4[4]);
        glColor3fv(topColours[1]);
        glVertex3iv(rect4[5]);
        glColor3fv(topColours[2]);
        glVertex3iv(rect4[6]);
        glColor3fv(topColours[3]);
        glVertex3iv(rect4[7]);
    glEnd();
    glEndList();
}