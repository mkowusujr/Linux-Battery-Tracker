"""
file: Handling the graphing of the battery tracker
description:
author: mathew owusu jr
"""
import matplotlib.pyplot as plt
import numpy as np
import datetime


def main():
    times = []
    battery = []
    with open("/var/lib/bat_data") as file:
        for line in file:
            line = line.rstrip()
            data = line.split(",")

            val = int(data[0])
            time = datetime.datetime.fromtimestamp(val)
            times.append(time)

            battery.append(float(data[1]))
    file.close()
    x_vals = np.array(times)
    y_vals = np.array(battery)
    plt.plot(x_vals, y_vals)
    plt.show()


if __name__ == "__main__":
    main()
