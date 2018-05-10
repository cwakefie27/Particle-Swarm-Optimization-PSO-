import sys
import numpy as np
import pandas as pd
import os
import matplotlib.pyplot as plt
from os.path import basename

def main():
    if len(sys.argv) >= 2:
        filename = sys.argv[1]
    else:
        print 'USAGE: python ' + sys.argv[0] + " Statistics.csv"
        sys.exit();

    with open(filename,'r') as file:
        statistics_data = pd.read_csv(file, error_bad_lines=False,skiprows=[0])
    file.closed

    #Set the X values
    X_values = np.array(statistics_data.index.values)
    for i in range(0,2):
        #Get Y Values
        if i == 0:
            savename = 'Position.png'
            Y_axis_label = 'Position Difference'
            Y_1_label = 'X Position Difference'
            Y_2_label = 'Y Position Difference'
            Y_values1 = np.array(statistics_data['Best X Position'] - statistics_data['Avg X Position'])
            Y_values2 = np.array(statistics_data['Best Y Position'] - statistics_data['Avg Y Position'])
        elif i == 1:
            savename = 'Fitness.png'
            Y_axis_label = 'Fitness'
            Y_1_label = 'Average Fitness'
            Y_2_label = 'Best Fitness'
            Y_values1 = np.array(statistics_data['Avg Fitness'])
            Y_values2 = np.array(statistics_data['Best Fitness'])

        plt.figure(num=None, figsize=(10, 5.5), dpi=80, facecolor='w', edgecolor='k')
        plt.title(Y_axis_label + ' Comparison')

        plt.xlabel("Epoch to Converge", fontsize=12)
        plt.ylabel(Y_axis_label, fontsize=12)

        plt.plot(X_values,Y_values1,color='red', alpha=.5,label=Y_1_label)
        plt.plot(X_values,Y_values2,color='blue', alpha=.8,label=Y_2_label)

        if i == 0:
            plt.axhline(0, color='black')

        legend = plt.legend(loc='upper right',bbox_to_anchor=(1.1, 1.15), ncol=3)
        legend.get_frame().set_alpha(0.4)

        plt.savefig(savename, bbox_inches='tight')

if __name__== "__main__":
  main()
