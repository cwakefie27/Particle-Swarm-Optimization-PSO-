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
        print 'USAGE: python ' + sys.argv[0] + " problem_number.csv"
        sys.exit();

    with open(filename,'r') as file:
        problem_data = pd.read_csv(file, error_bad_lines=False,index_col=0)
    file.closed

    #Save the problem name and set parameters used
    problem = basename(os.path.splitext(sys.argv[1])[0])

    statistics = ['Iteration','% Within Error','Avg Fitness','Error','Best Fitness']
    parameters = ['Number Particles','Inertia','Cognition','Social','Max Velocity']

    # for statistic in statistics
    for statistic in statistics:
        for parameter in parameters:
            problem_data = problem_data.sort_values(by=[parameter])
            plt.figure(num=None, figsize=(10, 5.5), dpi=80, facecolor='w', edgecolor='k')
            plt.title(problem + ": " + statistic + " vs " + parameter)

            plt.xlabel(parameter, fontsize=12)
            plt.ylabel(statistic, fontsize=12)

            X_values = np.array(problem_data[parameter])
            Y_values = np.array(problem_data[statistic])

            # calc the trendline
            z = np.polyfit(X_values, Y_values, 2)
            p = np.poly1d(z)
            plt.plot(X_values,p(X_values),"g--",alpha=.5,label="Trend Line")

            #calc tje average_epochs_to_converge
            average_epochs_to_converge = [problem_data.loc[problem_data[parameter] == i][statistic].mean() for i in np.unique(X_values)]

            plt.scatter(X_values,Y_values,color='red', alpha=.5,label="Experiment")
            plt.scatter(np.unique(X_values),average_epochs_to_converge,color='blue', alpha=.8,label="Average Experiment")

            plt.xticks(np.unique(X_values))

            legend = plt.legend(loc='upper right',bbox_to_anchor=(1.1, 1.15), ncol=3)
            legend.get_frame().set_alpha(0.4)

            savename = problem + '_' + statistic + '_' + parameter + '.png'
            plt.savefig(savename, bbox_inches='tight')

if __name__== "__main__":
  main()
