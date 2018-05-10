#include <iostream>
#include <Particle.h>
#include <iomanip>

using namespace std;

void Particle::print(ostream &out){
   out << "      Fitness: " << fitness << endl;
   out << "      Best Fitness: " << best_fitness << endl;

   int dimensions = position.DIMENSIONS;
   out << "      Position: ";
   for (int i = 0; i < dimensions; i++){
      out << position[i] << " ";
   }
   out << endl;

   out << "      Best Positions: ";
   for (int i = 0; i < dimensions; i++){
      out << best[i] << " ";
   }
   out << endl;

   out << "      Velocity: ";
   for (int i = 0; i < dimensions; i++){
      out << velocity[i] << " ";
   }
   out << endl;
}

void Particle::print_current_info(ostream &out){
   out << setw(9) << position.x << ", " << setw(9) << position.y << ", " << setw(12) << best_fitness << ", " << setw(12) << within_error << endl;
}
