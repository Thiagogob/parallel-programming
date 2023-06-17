import matplotlib
import numpy as np
matplotlib.use('agg') 

import matplotlib.pyplot as plt
def main():

    with open("../timesSequential.txt") as file:
        lines = file.readlines()

    timesSequential = []

    for line in lines:
        time = float(line.strip())
        timesSequential.append(time)
    
    mean = np.mean(timesSequential)

    plt.plot(timesSequential, label = 'Time for each run')

    plt.axhline(y=mean, color='r', linestyle='--', label = 'Mean time') 

    plt.xlabel("Run")
    plt.ylabel("Time (s)")
    plt.title("Time for each Run and Mean Time")


    plt.savefig('mean_plot.png', format='png', dpi=300)


if __name__ == "__main__":
    main()
