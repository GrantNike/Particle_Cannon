//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//For string
#include <string>
//For particle shapes
#include "shapes.cpp"

namespace particles{
    //3D coordinates
    //Represents a point in 3D space
    class point{
        public:
        GLfloat x,y,z;
        point(){

        };
        point(GLfloat x,GLfloat y,GLfloat z){
            x = x;
            y = y;
            z = z;
        }
        //Overload == operator to define if two points are equal
        bool operator ==(point p2){
            return x == p2.x && y == p2.y && z == p2.z;
        }
        bool operator !=(point p2){
            return x != p2.x || y != p2.y || z != p2.z;
        }
        point operator *(GLfloat speed){
            x = x*speed;
            z = z*speed;
            point p(x,y,z);
            return p;
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
        point velocity;
        //GLfloat speed;
        GLfloat gravity;
        col colour;
        std::string shape;
        bool kill;
        //Default Particle constructor
        particle(){
            gravity = -0.1;
            velocity.x = 0.1;
            velocity.y = -1;
            velocity.z = 0;
            kill = false;
        }
        //Particle constructor with start position as parameter
        particle(GLfloat x, GLfloat y, GLfloat z){
            gravity = -0.1;
            velocity.x = 0.1;
            velocity.y = -1;
            velocity.z = 0;
            kill = false;
            GLfloat speed_x = ((float)(rand()%200))/100.0;
            GLfloat speed_z = ((float)((rand()%400)-200))/100.0;
            velocity.x += speed_x;
            //Keep direction of speed, just change magnitude of velocity in z direction
            velocity.z += speed_z;
            position.x = x;
            position.y = y;
            position.z = z;
            shape = "cube";
        }
        //Check if the particle has collided with the plane
        bool ground_collision(){
            GLfloat new_x = position.x + velocity.x;
            GLfloat new_y = position.y + velocity.y;
            GLfloat new_z = position.z + velocity.z;

            return new_y < 3 && new_x < 125 && new_x > -125 && new_z < 100 && new_z > -100;
        }
        void update_position(){
            //If particle collides with ground
            if(ground_collision()){
                //Completly stop particle once it reaches a certain minimum speed
                if(abs(velocity.y) < 0.5){
                    velocity.y = 0;
                    velocity.x = 0;
                    velocity.z = 0;
                    gravity = 0;
                }
                //Reverse y velocity of particle to make it bounce, 
                //And scale down magnitude of velocity to add momentum loss due to friction
                velocity.y = -0.9*velocity.y;
                velocity.x = 0.9*velocity.x;
                velocity.z = 0.9*velocity.z;
            }
            //Kill particle once it goes a certain depth off the plane
            else if(position.y + velocity.y < -500){
                kill = true;
            }
            //Add gravity to y velocity each time, providing acceleration
            velocity.y += gravity;
            //Update position based on current velocity
            position.x += velocity.x;
            position.y += velocity.y;
            position.z += velocity.z;
        }
        void draw_particle(){
            if(shape == "cube"){
                update_position();
                shapes::drawCube(position.x,position.y,position.z);
            }
        }
        
    };
}