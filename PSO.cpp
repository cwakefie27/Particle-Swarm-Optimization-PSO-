#include <iostream>
#include <time.h>
#include <PSO.h>
#include <Particle.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

Vec2 BEST_PARTICLE_POSITION;
float BEST_PARTICLE_FITNESS = -999999;
const float ERROR_THRESHOLD = 0.1;
const float WITHIN_ERROR_THRESHOLD = 0.25;
const int NUM_STATISTICS = 9;

const float SEED_VALUE = time(NULL);
//const float SEED_VALUE = 1.0;

void InitalizeParticles(Particle*,int,Problem*);
void UpdateParticles(Particle*,int,float,float,float,float,Problem*);
void UpdateVelocity(Particle&,float,float,float,float);
void UpdatePosition(Particle&);
void UpdateFitness(Particle&,Problem*);
float CalculateError(Particle*,int);
void CalculateStats(int,vector<vector<float>> &,Particle*,int,Problem*,float);
bool IsWithinGlobalMax(Particle&,Problem*);
void print_particles(Particle*,int,ostream&);
void print_stats(vector<vector<float>>&,int,ostream&);

void ParicleSwarmOptimization(int num_epochs, int num_particles, float inertia, float cognition, float social,float max_velocity,Problem *problem, bool save_to_file, bool save_particle_iterations){
   int iteration = 0;
   vector<vector<float>> statistics(num_epochs+1,vector<float>(NUM_STATISTICS,0));

   Particle swarm[num_particles];
   InitalizeParticles(swarm,num_particles,problem);

   float error = CalculateError(swarm,num_particles);
   CalculateStats(iteration,statistics,swarm,num_particles,problem,error);

   if (save_particle_iterations){
      ofstream out_particles("Particle_List_" + to_string(iteration) + ".csv");
      print_particles(swarm,num_particles,out_particles);
      out_particles.close();
   }

   while(iteration < num_epochs && error > ERROR_THRESHOLD){
      iteration++;
      UpdateParticles(swarm,num_particles,inertia,cognition,social,max_velocity,problem);
      error = CalculateError(swarm,num_particles);
      CalculateStats(iteration,statistics,swarm,num_particles,problem,error);

      if(save_particle_iterations){
         ofstream out_particles("Particle_List_" + to_string(iteration) + ".csv");
         print_particles(swarm,num_particles,out_particles);
         out_particles.close();
      }
   }

   if (save_to_file){
      ofstream out_particles("Final_Particle_List.csv");
      ofstream out_statistics("Statistics.csv");
      print_particles(swarm,num_particles,out_particles);
      print_stats(statistics,iteration+1,out_statistics);
      out_particles.close();
      out_statistics.close();
   }else{
      print_particles(swarm,num_particles,cout);
      cout << endl;
      print_stats(statistics,iteration+1,cout);
      cout << endl;
   }
}

void InitalizeParticles(Particle* swarm,int num_particles,Problem* problem){
   srand (SEED_VALUE);
   int dimensions = swarm[0].position.DIMENSIONS;
   for (int i = 0; i < num_particles; i++){
      for (int j = 0; j < dimensions; j++){
         int range = problem->SEARCH_MAX - problem->SEARCH_MIN + 1;
         swarm[i].position[j] = rand() % range + MIN_VALUE;
         swarm[i].best[j] = swarm[i].position[j];
         swarm[i].velocity[j] = 0;
      }
      UpdateFitness(swarm[i],problem);
      //Ensure best fitness gets set on the first iteration
      swarm[i].best_fitness = swarm[i].fitness;
      swarm[i].best.x = swarm[i].position.x;
      swarm[i].best.y = swarm[i].position.y;
   }
}

void UpdateFitness(Particle& particle,Problem* problem){
   particle.fitness = problem->CalcFitness(particle.position);
   if (particle.fitness > particle.best_fitness){
      particle.best_fitness = particle.fitness;
      particle.best.x = particle.position.x;
      particle.best.y = particle.position.y;
   }
   if (particle.fitness > BEST_PARTICLE_FITNESS){
      BEST_PARTICLE_FITNESS = particle.fitness;
      BEST_PARTICLE_POSITION.x = particle.position.x;
      BEST_PARTICLE_POSITION.y = particle.position.y;
   }
}

void UpdateParticles(Particle* swarm, int num_particles, float inertia, float cognition, float social, float max_velocity, Problem* problem){
   for (int i = 0; i < num_particles; i++){
      UpdateVelocity(swarm[i], inertia, cognition, social, max_velocity);
      UpdatePosition(swarm[i]);
      UpdateFitness(swarm[i],problem);
   }
}

void UpdateVelocity(Particle &particle, float inertia, float cognition, float social, float max_velocity){
   int dimensions = particle.position.DIMENSIONS;
   //Calculate new velocity
   for (int i = 0; i < dimensions; i++){
      particle.velocity[i] = inertia * particle.velocity[i] + (cognition * (rand() % 2)) * (particle.best[i] - particle.position[i]) + (social * (rand() % 2)) * (BEST_PARTICLE_POSITION[i] - particle.position[i]);
   }
   //scale velocity
   if (pow(particle.velocity.x, 2.0) + pow(particle.velocity.y, 2.0) > pow(max_velocity, 2.0))
   {
      float norm = (max_velocity / sqrt(pow(particle.velocity.x, 2.0) + pow(particle.velocity.y, 2.0)));
      for (int i = 0; i < dimensions; i++){
         particle.velocity[i] = norm * particle.velocity[i];
      }
   }
}

void UpdatePosition(Particle& particle){
   int dimensions = particle.position.DIMENSIONS;
   for (int i = 0; i < dimensions; i++){
      particle.position[i] += particle.velocity[i];
   }
}

float CalculateError(Particle* swarm, int num_particles){
   Vec2 error;
   int dimensions = swarm[0].position.DIMENSIONS;
   for (int i = 0; i < num_particles; i++){
      for (int j = 0; j < dimensions; j++){
         error[j] += pow(swarm[i].position[j] - BEST_PARTICLE_POSITION[j], 2.0);
      }
   }

   for (int i = 0; i < dimensions; i++){
      error[i] = sqrt( (1/(2*(float)num_particles)) * error[i]);
   }
   return sqrt(pow(error.x, 2.0) + pow(error.y, 2.0));
}

void CalculateStats(int iteration,vector<vector<float>>& statistics,Particle* swarm, int num_particles, Problem* problem,float error){
   int dimensions = swarm[0].position.DIMENSIONS;
   Vec2 total_position;
   float total_fitness = 0.0;
   int number_within_error = 0;
   for (int i = 0; i < num_particles; i++){
      for (int j = 0; j < dimensions; j++){
         total_position[j] += swarm[i].position[j];
      }
      total_fitness += swarm[i].fitness;
      if(IsWithinGlobalMax(swarm[i],problem)){
         swarm[i].within_error = true;
         number_within_error++;
      }else{
         swarm[i].within_error = false;
      }
   }

   statistics[iteration][0] = (float) iteration;
   statistics[iteration][1] = total_position.x / num_particles;
   statistics[iteration][2] = total_position.y / num_particles;
   statistics[iteration][3] = total_fitness / num_particles;
   statistics[iteration][4] = (float) number_within_error / num_particles * 100;
   statistics[iteration][5] = BEST_PARTICLE_POSITION.x;
   statistics[iteration][6] = BEST_PARTICLE_POSITION.y;
   statistics[iteration][7] = BEST_PARTICLE_FITNESS;
   statistics[iteration][8] = error;
}

bool IsWithinGlobalMax(Particle& particle,Problem* problem){
   float x_diff = fabs(problem->GLOBAL_BEST_X - particle.position.x);
   float y_diff = fabs(problem->GLOBAL_BEST_Y - particle.position.y);
   if (x_diff+y_diff < WITHIN_ERROR_THRESHOLD){
      return true;
   }
   return false;
}

void print_particles(Particle* swarm,int num_particles,ostream& out_particles){
   out_particles << "Final Iteration Particle List Info:" << endl;
   out_particles << "Particle,X Position,Y Position,Fitness Value,Within Global" << endl;
   for (int i = 0; i < num_particles; i++){
      out_particles << setw(8) << i+1 << ", ";
      swarm[i].print_current_info(out_particles);
   }
}

void print_stats(vector<vector<float>>& statistics,int num_epochs, ostream& out_statistics){
   out_statistics << "Statistics per Iteration: " << endl;
   out_statistics << "Iteration,Avg X Position,Avg Y Position,Avg Fitness,% Within Error,Best X Position,Best Y Position,Best Fitness,Error" << endl;
   int width[NUM_STATISTICS] = {9,13,13,10,13,14,14,11,9};
   for(int i = 0; i < num_epochs; i++){
      for(int j = 0; j < NUM_STATISTICS; j++){
         out_statistics << fixed << setprecision(5) << setw(width[j]) << statistics[i][j];
         if(j != NUM_STATISTICS-1){
            out_statistics << ", ";
         }
      }
      out_statistics << endl;
   }
}
