//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace shapes{
    
    void drawCube(GLfloat x,GLfloat y,GLfloat z) {
        //Dimensions of shape
        int dimensions[][3] = {{2,2,2}, {2,-2,2}, {-2,-2,2}, {-2,2,2},
                    {2,2,-2}, {2,-2,-2}, {-2,-2,-2}, {-2,2,-2}};
        int e[][4] = {{0,3,2,1},{3,7,6,2},{7,4,5,6},{4,0,1,5}, {0,4,7,3},{1,2,6,5}};
        float c[][3] = {{1.0,0,0},{0,1.0,0},{1.0,1.0,1.0},
            {0,0,1.0},{.6,0,.6},{0,.6,.6}};

        float singleColour[][3] = { {0.0,0.0,0.9},{0.0,0.0,0.4},{0.0,0.0,0.8},{0.0,0.0,0.6} };
        //Move shape to position
        glPushMatrix();
        glTranslatef(x,y,z);
        //Draw shape
        for (int i=0; i < 6; ++i) {
            glColor3fv(c[i]);
            glBegin(GL_QUADS);
                glColor3fv(singleColour[0]);
                glVertex3iv(dimensions[e[i][0]]);
                glColor3fv(singleColour[1]);
                glVertex3iv(dimensions[e[i][1]]);
                glColor3fv(singleColour[2]);
                glVertex3iv(dimensions[e[i][2]]);
                glColor3fv(singleColour[3]);
                glVertex3iv(dimensions[e[i][3]]);
            glEnd();
        }
        glPopMatrix();
    }
}