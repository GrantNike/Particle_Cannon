//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//For vector of course
#include <vector>
//For cout,cin,cerr,endl
#include <iostream>
#include <limits>
//For Random
#include <cstdlib> 
//Used as parameter to random seed
#include <ctime>
//For max and min
#include <cmath>

namespace particles{
    //3D coordinates
    //Represents a point in 3D space
    class point{
        public:
        GLfloat x,y,z;
        //Overload == operator to define if two points are equal
        bool operator ==(point p2){
            return x == p2.x && y == p2.y && z == p2.z;
        }
        bool operator !=(point p2){
            return x != p2.x || y != p2.y || z != p2.z;
        }
    };
    //Represents a colour
    class col{
        public:
        GLfloat r,g,b;
        //Overload == operator to define if two colours are equal
        bool operator ==(col c2){
            return r == c2.r && g == c2.g && b == c2.b;
        }
        bool operator !=(col c2){
            return r != c2.r || g != c2.g || b != c2.b;
        }
    };
    //A single particle in the swarm
    class particle{
        public:
        point position;
        point direction;
        GLfloat speed;
        col colour;
    };
}

//Function definitions
void drawcube();
//Glut keyboard function to handle keyboard inputs
void keyboard(unsigned char key, int x, int y);
//Defines what each menu function does
void menu_func(int value);
//Defines a menu accessed by right clicking the graphics window
void create_menu();
//Prints the key and its function to the terminal
void key_commands();