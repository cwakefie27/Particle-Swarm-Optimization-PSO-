import sys
import numpy as np
import pandas as pd
import os
import matplotlib.pyplot as plt
import imageio

def main():
    if len(sys.argv) >= 2:
        directory = sys.argv[1]
    else:
        print "Either usage will work"
        print '   USAGE: python ' + sys.argv[0] + " Directory_Particle_List_PNG/"
        sys.exit();

    images = []
    for file_number in range(0,len(os.listdir(directory))):
        filename = os.path.join(directory,"Particle_List_" + str(file_number) + ".png")
        images.append(imageio.imread(filename))
    duration = (1/np.sqrt(len(os.listdir(directory)))) * 1.5
    imageio.mimsave("Experiment.gif", images,format='GIF', duration=duration)

if __name__== "__main__":
  main()
