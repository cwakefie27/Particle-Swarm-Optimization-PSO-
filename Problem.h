#ifndef PROBLEM_H
#define PROBLEM_H

#include <Particle.h>
#include <string>

using namespace std;

struct Problem{
   virtual float CalcFitness (Vec2) = 0;
   //Best known solution to problem
   float const GLOBAL_BEST_X,GLOBAL_BEST_Y;
   //Search window to initalize particles in
   float const SEARCH_MIN, SEARCH_MAX;
protected:
   Problem(float x,float y, float min, float max) : GLOBAL_BEST_X(x),GLOBAL_BEST_Y(y),SEARCH_MIN(min),SEARCH_MAX(max) { }
};

struct Problem1 : public Problem{
   Problem1() : Problem(20.0,7.0,-50,50) {}
   float CalcFitness(Vec2);
};

struct Problem2 : public Problem{
   Problem2() : Problem(19.95,6.98,-50,50) {}
   float CalcFitness(Vec2);
};

#endif
