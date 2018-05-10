#include <iostream>
#include <Problem.h>
#include <PSO.h>
#include <cmath>

using namespace std;

float mdist();
float pdist(Vec2);
float ndist(Vec2);

float Problem1::CalcFitness(Vec2 position){
   return 100.0 * (1.0 - (pdist(position) / mdist()));
}

float Problem2::CalcFitness(Vec2 position){
   return (9.0 * max(0.0, 10.0 - pow(pdist(position), 2.0))) + (10.0 * (1.0 - (pdist(position) / mdist()))) + (70.0 * (1.0 - (ndist(position) / mdist())));
}

float mdist()
{
   int range = MAX_VALUE - MIN_VALUE;
   return sqrt(pow(range, 2.0) + pow(range, 2.0)) / 2.0;
}

float pdist(Vec2 position)
{
   return sqrt(pow(position.x - 20.0, 2.0) + pow(position.y - 7.0, 2.0));
}

float ndist(Vec2 position)
{
   return sqrt(pow(position.x + 20.0, 2.0) + pow(position.y + 7.0, 2.0));
}
