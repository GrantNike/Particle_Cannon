//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "particle.cpp"

namespace shapes{
    
    void drawCube(particles::particle part) {
        //Dimensions of shape
        int dimensions[][3] = {{2,2,2}, {2,-2,2}, {-2,-2,2}, {-2,2,2},
                    {2,2,-2}, {2,-2,-2}, {-2,-2,-2}, {-2,2,-2}};
        int e[][4] = {{0,3,2,1},{3,7,6,2},{7,4,5,6},{4,0,1,5}, {0,4,7,3},{1,2,6,5}};
        float c[][3] = {{1.0,0,0},{0,1.0,0},{1.0,1.0,1.0},
            {0,0,1.0},{.6,0,.6},{0,.6,.6}};

        float singleColour[][3] = { {0.0,0.0,0.9},{0.0,0.0,0.4},{0.0,0.0,0.8},{0.0,0.0,0.6} };
        //Move shape to position
        glPushMatrix();
        glTranslatef(part.position.x,part.position.y,part.position.z);
        glRotatef(part.angle[0], 1.0, 0.0, 0.0);
        glRotatef(part.angle[1], 0.0, 1.0, 0.0);
        glRotatef(part.angle[2], 0.0, 0.0, 1.0);
        //Draw shape
        for (int i=0; i < 6; ++i) {
            glColor3fv(c[i]);
            glBegin(GL_POLYGON);
                glColor3fv(part.colour[0]);
                glVertex3iv(dimensions[e[i][0]]);
                glColor3fv(part.colour[1]);
                glVertex3iv(dimensions[e[i][1]]);
                glColor3fv(part.colour[2]);
                glVertex3iv(dimensions[e[i][2]]);
                glColor3fv(part.colour[3]);
                glVertex3iv(dimensions[e[i][3]]);
            glEnd();
        }
        glPopMatrix();
    }

    void drawCubeWire(particles::particle part) {
        int v[8][3] = {
            {2,2,2}, 
            {2,-2,2}, 
            {-2,-2,2}, 
            {-2,2,2},
            {2,2,-2}, 
            {2,-2,-2}, 
            {-2,-2,-2}, 
            {-2,2,-2}
        };
        int path[16] = {
            0, 1, 2, 3,
            0, 4, 5, 6,
            7, 4, 5, 1,
            2, 6, 7, 3
        };

        glPushMatrix();
        glTranslatef(part.position.x,part.position.y,part.position.z);
        glRotatef(part.angle[0], 1.0, 0.0, 0.0);
        glRotatef(part.angle[1], 0.0, 1.0, 0.0);
        glRotatef(part.angle[2], 0.0, 0.0, 1.0);	

        glBegin(GL_LINE_STRIP);
        for (int i=0; i < 16; i++){
            glColor3fv(part.colour[i%4]);
            glVertex3i(v[path[i]][0], v[path[i]][1], v[path[i]][2]);
        }
        glEnd();
        glPopMatrix();
    }
}