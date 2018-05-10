#ifndef PARTICLE_H
#define PARTICLE_H

#include <fstream>

struct Vec2{
   Vec2(){x=0;y=0;}
   const int DIMENSIONS = 2;
   float x,y;
   float operator [](int i) const {if(i==0){return x;}else{return y;}}
   float & operator [](int i) {if(i==0){return x;}else{return y;}}
};

struct Particle{
   Particle(){best_fitness=-9999;within_error = false; velocity.x = 0; velocity.y = 0;}
   Vec2 position;
   Vec2 velocity;
   Vec2 best;
   float fitness;
   float best_fitness;
   bool within_error;
   void print(std::ostream&);
   void print_current_info(std::ostream&);
};

#endif
