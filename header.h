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
//Particle namespace file
#include "particle.cpp"
//Files for shape definitions
#include "cannon.cpp"
#include "plane.cpp"

//Function definitions
void draw_shapes();
void init_particles();
//Glut keyboard function to handle keyboard inputs
void keyboard(unsigned char key, int x, int y);
//Defines what each menu function does
void menu_func(int value);
//Defines a menu accessed by right clicking the graphics window
void create_menu();
//Prints the key and its function to the terminal
void key_commands();