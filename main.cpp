#include <iostream>
#include <Problem.h>
#include <PSO.h>
#include <iomanip>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
   if (argc < 10){
      printf("USAGE: %s Num_Epochs Num_Particles Inertia Cognition Social Max_Velocity Problem_Number SaveOutputToFile SaveParticleIterations\n",argv[0]);
      return(-1);
   }

   //Save arguments to the program
   int num_epochs = atoi(argv[1]);
   int num_particles = atoi(argv[2]);
   float inertia = atof(argv[3]);
   float cognition = atof(argv[4]);
   float social = atof(argv[5]);
   float max_velocity = atof(argv[6]);
   int problem_number = atoi(argv[7]);
   bool save_to_file = false;
   bool save_particle_iterations = false;

   //Possibly save each output to csv
   if (argv[8][0] == 'T' || argv[8][0] == 't') save_to_file = true;

   //Possibly save Itterations for each Particle List
   if (argv[9][0] == 'T' || argv[9][0] == 't') save_particle_iterations = true;

   //Set which problem will be used
   Problem *problem;
   switch (problem_number) {
      case 1:
         problem = new Problem1();
         break;
      case 2:
         problem = new Problem2();
         break;
      default:
         cerr << "Problem number must be 1 or 2" << endl;
         return -1;
         break;
   }

   streambuf *buffer;
   ofstream params;

   if(save_to_file) {
      params.open("Params.csv");
      buffer = params.rdbuf();
   } else {
      buffer = cout.rdbuf();
   }

   ostream out_params(buffer);

   out_params << "Program Parameters:" << endl;
   out_params << "Number Particles,Inertia,Cognition,Social,Max Velocity,Problem Number" << endl;
   out_params << setw(16) << num_particles << "," << setw(7) << inertia << "," << setw(9) << cognition;
   out_params << "," << setw(6) << social << "," << setw(12) << max_velocity <<  "," << setw(14) << problem_number << endl << endl;

   ParicleSwarmOptimization(num_epochs,num_particles,inertia,cognition,social,max_velocity,problem,save_to_file,save_particle_iterations);

   params.close();

   return(0);
}
