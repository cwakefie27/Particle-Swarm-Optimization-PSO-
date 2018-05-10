#!/bin/bash
#Run below command to make script executable
#chmod +x plot_experiment.sh

#Read in args
args=("$@")
if [ ${#args[@]} -ne 8 ]; then
   echo "Not enough parameters specified"
   echo "USAGE: ./shell/create_Particle_GIF.sh Num_Epochs Num_Particles Inertia Cognition Social Max_Velocity Problem_Number make_gif"
   exit 1
fi

#Called from wrong directory
make &> /dev/null
if [ $? -ne 0 ]; then
   echo "You are in the wrong directory, move back one and use the command below"
   echo "USAGE: ./shell/create_Particle_GIF.sh Num_Epochs Num_Particles Inertia Cognition Social Max_Velocity Problem_Number make_gif"
   exit 1
fi

#terminate after an error
#set -e

#Save experiment info
./project5 ${args[0]} ${args[1]} ${args[2]} ${args[3]} ${args[4]} ${args[5]} ${args[6]} true true

#move all csv files to directory
mkdir -p ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/result/csv/
mkdir -p ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/csv/
mv Final_Particle_List.csv Params.csv Statistics.csv ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/result/csv/
#move at most 20 files to the particle directory
for i in {0..20}
do
   mv Particle_List_$i.csv ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/csv/ 2>/dev/null
done

#remove the rest of the csv files
rm -rf *.csv

#Plot experiment
python python/plot_experiment_performance.py experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/result/csv/Statistics.csv

mkdir -p ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/result/png/
mv *.png ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/result/png/


if [[ ${args[7]:0:1} == "t" ]] || [[ ${args[7]:0:1} == "T" ]] ; then
   for filename in ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/csv/* ;
   do
      python python/plot_particle_itteration.py $filename ${args[1]} ${args[2]} ${args[3]} ${args[4]} ${args[5]} ${args[6]}
   done

   #move all png files to directory
   mkdir -p ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/png/
   mv *.png ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/png/

   #create gif and named it based on params, then move it to the experiments fold
   python python/create_gif.py ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/png/
   mv ./*.gif ${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}.gif
   mv ./*.gif ./experiments/${args[0]}_${args[1]}_${args[2]}_${args[3]}_${args[4]}_${args[5]}_${args[6]}/particle_iterations/
fi
