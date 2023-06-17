import matplotlib
import numpy as np
matplotlib.use('agg') 

import matplotlib.pyplot as plt
def main():


#----------------------------------Analysis for Sequential Algorithm-------------------------------#
    with open("../timesSequential.txt") as file:
        lines = file.readlines()

    timesSequential = []

    for line in lines:
        time = float(line.strip())
        timesSequential.append(time)
    
    mean = np.mean(timesSequential)

    plt.figure()

    plt.plot(timesSequential, label = 'Time for each run')

    plt.axhline(y=mean, color='r', linestyle='--', label = 'Mean time') 

    plt.xlabel("Run")
    plt.ylabel("Time (s)")
    plt.title("Time for each Run and Mean Time in Sequential Algorithm")


    plt.savefig('mean_plot_sequential.png', format='png', dpi=300)

    plt.close()


#----------------------------------Analysis for Parallel Algorithm-------------------------------#
    with open("../timesParallel.txt") as file:
        lines = file.readlines()
    
    timesParallel = []

    for line in lines:
        time = float(line.strip())
        timesParallel.append(time)
    
    mean = np.mean(timesParallel)

    plt.figure()

    plt.plot(timesParallel, label = 'Time for each run')

    plt.axhline(y=mean, color='r', linestyle='--', label = 'Mean time')

    plt.xlabel("Run")
    plt.ylabel("Time (s)")
    plt.title("Time for each Run and Mean Time in Parallel Algorithm")

    plt.savefig('mean_plot_parallel.png', format='png', dpi=300)

    plt.close()

#------------------------------------Analysis for Speedup--------------------------------------#

    speedup = []

    for i in range(len(timesSequential)):
        speedup.append(timesSequential[i]/timesParallel[i])

    mean = np.mean(speedup)

    plt.figure()

    plt.plot(speedup, label = 'Speedup for each Run')

    plt.axhline(y=mean, color='r', linestyle='--', label = 'Mean Speedup')

    plt.xlabel("Run")
    plt.ylabel("Speedup")
    plt.title("Speedup for each Run")

    plt.savefig('speedup_plot.png', format='png', dpi=300)

    plt.close()

if __name__ == "__main__":
    main()
