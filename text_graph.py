"""
file:
description: Handling the graphing of the battery tracker
author: mathew owusu jr
"""
import matplotlib.pyplot as plt
import numpy as np
import datetime


def main():
    """

    """
    times = []
    battery = []

    # Open file
    with open("/var/lib/bat_data") as file:
        for line in file:
            # Break it apart
            line = line.rstrip()
            data = line.split(",")

            # store time data
            val = int(data[0])
            time = datetime.datetime.fromtimestamp(val)
            times.append(time)

            # store battery data
            battery.append(float(data[1]))
    file.close()

    # store data in coordinates
    x_vals = np.array(times)
    y_vals = np.array(battery)

    # plot the coordinates
    plt.plot(x_vals, y_vals)
    # plt.gca()
    plt.show()


if __name__ == "__main__":
    main()
