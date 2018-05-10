import sys
import numpy as np
import pandas as pd
import os

def main():
    if len(sys.argv) >= 2:
        directory = sys.argv[1]
    else:
        print 'USAGE: python ' + sys.argv[0] + " experiments_directory/"
        sys.exit();

    Data = {}

    for problem in os.listdir(directory):
        if problem[0] == '.':
            continue
        print problem
        Data[problem] = pd.DataFrame();
        for experiments_directory in os.listdir(os.path.join(directory,problem)):
            print "   " + experiments_directory
            for params_directory in os.listdir(os.path.join(directory,problem,experiments_directory)):
                print "      " + params_directory
                with open(os.path.join(directory,problem,experiments_directory,params_directory,"Params.csv"),'r') as file:
                    params_data = pd.read_csv(file, error_bad_lines=False,skiprows=[0])
                    params_data = params_data.drop(columns=['Problem Number'])
                file.closed
                with open(os.path.join(directory,problem,experiments_directory,params_directory,"Statistics.csv"),'r') as file:
                    statistics_data = pd.read_csv(file, error_bad_lines=False,skiprows=[0])
                    last_statistic = statistics_data.loc[[len(statistics_data)-1]].reset_index()
                file.closed

                #Row of data with params and results
                experiment = pd.concat([params_data,last_statistic],axis=1,join_axes=[params_data.index]).drop(columns=['index'])
                #Collect all data
                Data[problem] = Data[problem].append(experiment)
            Data[problem] = Data[problem].reset_index().drop(columns=['index']);

    for key in Data:
        Data[key].to_csv(key+".csv")

if __name__== "__main__":
  main()
