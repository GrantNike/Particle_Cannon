//For gl and glut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//For string
#include <string>
//For particle shapes

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
    //A single particle in the swarm
    class particle{
        public:
        point position;
        point velocity;
        GLfloat angle[3];
        GLfloat angle_increment[3];
        GLfloat gravity;
        GLfloat friction;
        GLfloat colour[4][3] = { {0.9,0.0,0.0},{0.1,0.0,0.0},{0.8,0.0,0.0},{0.5,0.0,0.0} };
        std::string shape;
        bool kill;
        GLfloat size_mult;
        //Default Particle constructor
        particle(){
            gravity = -0.1;
            velocity.x = 0.1;
            velocity.y = -1;
            velocity.z = 0;
            kill = false;
        }
        //Particle constructor with start position as parameter
        particle(GLfloat x, GLfloat y, GLfloat z, bool high_spray, bool rand_size, bool rand_colour, GLfloat gravity_mod,GLfloat friction_mod){
            gravity = -0.1*gravity_mod;
            friction = 0.8*friction_mod;
            velocity.x = 0;
            velocity.y = -1;
            velocity.z = 0;
            kill = false;
            if(rand_size) size_mult = (((float)(rand()%150))/100.0)+0.5;
            else size_mult = 1;
            GLfloat speed_x = ((float)(rand()%250))/100.0;
            GLfloat speed_z;
            if(high_spray) speed_z = ((float)((rand()%500)-250))/100.0;
            else speed_z = ((float)((rand()%100)-50))/100.0;
            velocity.x += speed_x;
            velocity.z += speed_z;
            position.x = x;
            position.y = y;
            position.z = z;
            angle_increment[0] = 2;
            angle_increment[1] = -2;
            if(velocity.z > 0){
                angle_increment[2] = 2;
            }
            else{
                angle_increment[2] = -2;
            }
            angle[0] = 0;
            angle[1] = 0;
            angle[2] = 0;
            shape = "cube";
            if(rand_colour) init_colour();
        }
        void init_colour(){
            for(int j=0;j<3;j++){
                colour[0][j] = ((float)(rand()%100))/100.0;
            }
            for(int i=0;i<4;i++){
                for(int j=0;j<3;j++){
                    colour[i][j] = colour[0][j] * (2.0/(((double)i)+1.0));
                }
            }
        }
        //Check if the particle has collided with the plane
        bool ground_collision(bool hole){
            GLfloat new_x = position.x + velocity.x;
            GLfloat new_y = position.y + velocity.y;
            GLfloat new_z = position.z + velocity.z;
            if(hole){
                return (new_y < 3 && new_y > 0) && 
                       ((new_x > -125 && new_x < -50 && new_z > -50 && new_z < 50) || (new_x > 50 && new_x < 125 && new_z > -50 && new_z < 50) || 
                       (new_x > -125 && new_x < 125 && new_z < 100 && new_z > 50) || (new_x > -125 && new_x < 125 && new_z < -50 && new_z > -100));
            }
            else{
                return new_y < 3 && new_x < 125 && new_x > -125 && new_z < 100 && new_z > -100;
            }
        }
        void update_position(bool hole){
            //If particle collides with ground
            if(ground_collision(hole)){
                //Completly stop particle once it reaches a certain minimum speed
                if(abs(velocity.y) < 0.5){
                    velocity.y = 0;
                    velocity.x = 0;
                    velocity.z = 0;
                    gravity = 0;
                    angle_increment[0] = 0;
                    angle_increment[1] = 0;
                    angle_increment[2] = 0;
                }
                else{
                    //Reverse y velocity of particle to make it bounce, 
                    //And scale down magnitude of velocity to add momentum loss due to friction
                    velocity.y = -friction*velocity.y;
                    velocity.x = friction*velocity.x;
                    velocity.z = friction*velocity.z;
                    if(angle_increment[0] < 5) angle_increment[0] = angle_increment[0]*abs(velocity.x);
                    else angle_increment[0] -= 5;
                    if(angle_increment[1] < 5) angle_increment[1] = angle_increment[1]*abs(velocity.y);
                    else angle_increment[1] -= 5;
                    if(angle_increment[2] < 5) angle_increment[2] = angle_increment[2]*abs(velocity.z);
                    else angle_increment[2] -= 5;
                    //angle_increment[1] = -angle_increment[1];
                }
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
            //Update angle based on angle increment
            //Angle X
            GLfloat new_angle_x = angle[0] + angle_increment[0];
            if(new_angle_x < 360) angle[0] = new_angle_x;
            //Angle Y
            GLfloat new_angle_y = angle[1] + angle_increment[1];
            if(new_angle_y < 360) angle[1] = new_angle_y;
            //Angle Z
            GLfloat new_angle_z = angle[2] + angle_increment[2];
            if(new_angle_z < 360) angle[2] = new_angle_z;
        }
        
    };
}