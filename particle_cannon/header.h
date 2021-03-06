/*
Grant Nike
6349302
Dec 6th
COSC 3P98 Assignment #3
*/

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
//Files for shape definitions
#include "cannon.cpp"
#include "plane.cpp"
#include "shapes.cpp"

//Function definitions
void myLightInit();
void init_particles(int numb_particels);
void reset_orientation();
void reset_particles();
void reset_scene();
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