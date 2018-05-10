#!/bin/bash
#Run below command to make script executable
#chmod +x experiment.sh

#Clean directory
rm -rf problems *.o

#Called from wrong directory
make &> /dev/null
if [ $? -ne 0 ]; then
   echo "You are in the wrong directory, move back one and use the command below"
   echo "USAGE: ./shell/run_experiments.sh"
   exit 1
fi

#terminate after an error
set -e

#run experiments and save directories
for problem_number in 1 2
do
   mkdir -p ./problems/problem$problem_number/experiments/
   for num_epochs in 2000
   do
      for num_particles in 2 5 10 30 70 100 200 1000
      # for num_particles in 2 5
      do
         for inertia in .1 .2 .3 .4 .5 .6 .7 .8 .9 1
         # for inertia in .4 .2
         do
            for cognition in .2 .5 1 2 2.5 3 3.5 4 5
            # for cognition in 2
            do
               for social in .2 .5 1 2 2.5 3 3.5 4 5
               # for social in 2
               do
                  for max_velocity in 1 2 5 10 50
                  # for max_velocity in 1 10
                  do
                     mkdir -p ./problems/problem$problem_number/experiments/$num_particles"_"$inertia"_"$cognition"_"$social"_"$max_velocity/
                     ./project5 $num_epochs $num_particles $inertia $cognition $social $max_velocity $problem_number true false
                     mv *.csv ./problems/problem$problem_number/experiments/$num_particles"_"$inertia"_"$cognition"_"$social"_"$max_velocity/
                  done
               done
            done
         done
      done
   done
done

#Compile data into the needed csv files
python python/combine_data.py problems/

#place them in experiment folders
for problem_number in 1 2
do
   #Create Graphs using compiled csv
   python python/plot_params_vs_epoch.py problem$problem_number.csv &> /dev/null
   #move all the info to the directory
   mv problem$problem_number.csv *.png ./problems/problem$problem_number/
done
