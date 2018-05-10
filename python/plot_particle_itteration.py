import sys
import numpy as np
import pandas as pd
import os
import matplotlib.pyplot as plt
from os.path import basename

def main():
    if len(sys.argv) >= 8:
        filename = sys.argv[1]
        num_particles = int(sys.argv[2])
        inertia = float(sys.argv[3])
        cognition = float(sys.argv[4])
        social = float(sys.argv[5])
        max_velocity = float(sys.argv[6])
        problem_number = int(sys.argv[7])
        title = "Num Particles: " + str(num_particles) + "  Inertia: " + str(inertia) + "  Cognition: " + str(cognition)
        title += "  Social: " + str(social) + "  Max Velocity: " + str(max_velocity) + "  Problem Number: " + str(problem_number)
    else:
        print 'USAGE: python ' + sys.argv[0] + " Final_Particle_List.csv Num_Particles Inertia Cognition Social Max_Velocity Problem_Number"
        sys.exit();

    with open(filename,'r') as file:
        particle_list = pd.read_csv(file, error_bad_lines=False,skiprows=[0])
    file.closed

    plt.figure(num=None, figsize=(10, 5.5), dpi=80, facecolor='w', edgecolor='k')
    plt.title(title)
    #plt.grid('on')
    plt.xlabel('X Position', fontsize=12)
    plt.ylabel('Y Position', fontsize=12)

    plt.xlim([-50,50])
    plt.ylim([-50,50])

    if problem_number == 1:
        plt.scatter(np.array(particle_list['X Position']),np.array(particle_list['Y Position']),color='blue', alpha=.5,label='Swarm')
        #Plot Exterma
        plt.scatter(20,7,color='red', alpha=1,label='Global Max')
    elif problem_number == 2:
        plt.scatter(np.array(particle_list['X Position']),np.array(particle_list['Y Position']),color='blue', alpha=.5,label='Swarm')
        #Plot Exterma
        plt.scatter(20,7,color='red', alpha=1,label='Global Max')
        plt.scatter(-20,-7,color='green', alpha=1,label='Local Max')
    else:
        print "Only problem_number 1 and 2 solutions are supported"
        plt.quit

    legend = plt.legend(loc='upper left',borderaxespad=0.)
    legend.get_frame().set_alpha(0.4)

    filename = basename(os.path.splitext(sys.argv[1])[0]) + ".png"

    plt.savefig(filename, bbox_inches='tight')

if __name__== "__main__":
  main()
