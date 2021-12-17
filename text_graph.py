# from dataclasses import dataclass
import matplotlib.pyplot as plt
import numpy as np
import datetime
# @dataclass
# class PlotPoint:
#     time: int
#     battery: float

def main():
    data = []
    points = []
    times = []
    times2 = []
    battery = []
    val = 0
    with open("/var/lib/bat_data") as file:
        for line in file:
            line = line.rstrip()
            # make object and store in list
            data = line.split(",")
            # points.append(PlotPoint(int(data[0]), float(data[1])))
            val = int(data[0])

            time = datetime.datetime.fromtimestamp(val)

            times.append(time)
            battery.append(float(data[1]))
            #print(line)
            #print(list)

    file.close()
    # for t in range(0, len(times) -1, 1):
    #     times[t] = abs(times[t] - times[(len(times) -1)])
    #     #time3 = datetime.datetime.fromtimestamp(times[t])
    #     times2.append(times[t])

    # print(points)
    # print(times)
    # print(battery)
    xvals = np.array(times)
    yvals = np.array(battery)
    plt.plot(xvals, yvals)
    plt.show()

if __name__ == "__main__":
    main()