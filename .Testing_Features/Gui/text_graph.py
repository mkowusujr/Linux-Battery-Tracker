"""
file:
description: Handling the graphing of the battery tracker
author: mathew owusu jr
"""
import matplotlib.pyplot as plt
import numpy as np
import datetime


def fetch_bat_log():
    # list_of_days = []
    with open("/home/mathew/Local_GitHub_Repositories/Linux-Battery-Tracker/Created_Data/bat_log.txt", 'r') as log:
        days = log.readline().strip()
        days = days.split(',')
        list_of_days = days
    log.close()
    return list_of_days


def chart_data(file):
    times = []
    battery = []

    # Open file
    with open(file, 'r') as data:

        for line in data.readlines():
            # Break it apart
            line = line.rstrip()
            line = line.split(",")

            # store time data
            val = int(line[0])
            time = datetime.datetime.fromtimestamp(val)
            times.append(time)

            # store battery data
            battery.append(float(line[1]))
    data.close()

    # store data in coordinates
    x_vals = np.array(times)
    y_vals = np.array(battery)

    # plot the coordinates
    plt.plot(x_vals, y_vals)
    # plt.gca()
    plt.show()


def main():
    """

    """
    chart_data("/var/lib/bat_data")
    days = fetch_bat_log()

    for day in days:
        chart_data(day)


if __name__ == "__main__":
    main()
