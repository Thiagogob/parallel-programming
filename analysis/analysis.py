import matplotlib
import numpy as np
matplotlib.use('agg') 

import matplotlib.pyplot as plt
def main():


#----------------------------------Analysis for Sequential Algorithm-------------------------------#
    with open("../algorithms/meanTimesSequential.txt") as file:
        lines = file.readlines()

    meanTimesSequential = []

    for line in lines:
        time = float(line.strip())
        meanTimesSequential.append(time)
    
    with open("../algorithms/resolutions.txt") as file:
        lines = file.readlines()

    resolutions = []

    for line in lines:
        resolution = int(line.strip())
        resolutions.append(resolution)

    plt.figure()

    
    degree = 2
    coefficients = np.polyfit(resolutions, meanTimesSequential, degree)
    polynomial = np.poly1d(coefficients)

    resolution_prediction = np.linspace(min(resolutions), max(resolutions), 100)

    meanTimesSequential_prediction = polynomial(resolution_prediction)

    plt.plot(resolutions, meanTimesSequential, 'o', label = 'Data')
    plt.plot(resolution_prediction, meanTimesSequential_prediction, label = 'Predicted Curve')
    plt.xlabel("Resolution")
    plt.ylabel("Time (ms)")
    
    plt.savefig("predicted_curve_sequential.png", format="png", dpi=300)


    plt.close()


#----------------------------------Analysis for Parallel Algorithm-------------------------------#
    with open("../algorithms/meanTimesParallel.txt") as file:
        lines = file.readlines()
    
    meanTimesParallel = []

    for line in lines:
        time = float(line.strip())
        meanTimesParallel.append(time)
    

    plt.figure()


    degree = 2
    coefficients = np.polyfit(resolutions, meanTimesParallel, degree)
    polynomial = np.poly1d(coefficients)

    resolution_prediction = np.linspace(min(resolutions), max(resolutions), 100)

    meanTimesParallel_prediction = polynomial(resolution_prediction)

    plt.plot(resolutions, meanTimesParallel, 'o', label = 'Data')
    plt.plot(resolution_prediction, meanTimesParallel_prediction, label = 'Predicted Curve')
    plt.xlabel("Resolution")
    plt.ylabel("Time (ms)")

    plt.savefig("predicted_curve_parallel.png", format="png", dpi=300)
    plt.close()

#------------------------------------Analysis for Speedup--------------------------------------#

    speedup = []

    for i in range(len(meanTimesSequential)):
        speedup.append(meanTimesSequential[i]/meanTimesParallel[i])

    mean = np.mean(speedup)

    plt.figure()
    
    plt.plot(resolutions, speedup, 'o', label = 'Data')
    
    plt.xlabel("Resolution")
    plt.ylabel("Speedup")
    plt.axhline(y=mean, color='r', linestyle='--', label = 'Mean Speedup')
    plt.savefig("predicted_curve_speedup.png", format="png", dpi=300)
    
    plt.close()

#---------------------------------------------------------------------------------------------#

if __name__ == "__main__":
    main()
