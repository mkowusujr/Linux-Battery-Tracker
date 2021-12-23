#!/usr/bin/env python
# Load Gtk
import gi
# matplotlib
from matplotlib.backends.backend_gtk3agg import (
    FigureCanvasGTK3Agg as FigureCanvas)
from matplotlib.figure import Figure
import numpy as np
import datetime
import matplotlib.dates as dates
import matplotlib.ticker as ticker
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


class LBT_gui:
    def __init__(self):
        self.builder = Gtk.Builder()
        self.builder.add_from_file("lbt_gtk_layout.glade")
        self.builder.connect_signals(self)

        self.window = self.builder.get_object("main_win")
        self.window.show_all()
        self.plot_data("/var/lib/bat_data")

    def fetch_bat_log(self):
        # list_of_days = []
        with open("/home/mathew/Local_GitHub_Repositories/Linux-Battery-Tracker/Created_Data/bat_log.txt", 'r') as log:
            days = log.readline().strip()
            days = days.split(',')
            list_of_days = days
        log.close()
        return list_of_days

    def make_fig(self, file):
        fig = Figure(figsize=(5, 4), dpi=100)
        ax = fig.add_subplot()

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
                # time = time.time().strftime('%H:%M')
                times.append(time)

                # store battery data
                battery.append(float(line[1]))
        data.close()

        # store data in coordinates
        x_vals = np.array(times)
        y_vals = np.array(battery)

        # plot the coordinates
        ax.plot(x_vals, y_vals)
        # ax.set_title(file)
        ax.set_xlabel("Time")
        ##ax.xaxis.set_major_locator(ticker.MultipleLocator(240))
        #ax.locator_params(axis='x', nbins=4)
        #formatter = dates.DateFormatter('%H:%M')


        #ax.xaxis.set_major_formatter(formatter)
        ax.xaxis.set_major_formatter(dates.DateFormatter('%H:%M'))
        ##ax.set_xlim(0, 1440)


        #ax.tick_params('x', length=5, width=2, which="major")
        #ax.set_xlim('00:00:00', '23:59:59')
        #ax.set_xticks([00:00:00, '04:00:00', '08:00:00', '12:00:00', '16:00:00', '20:00:00'])
        ax.set_ylabel("Battery Percentage")
        ax.set_ylim(0, 105)
        ax.set_yticks([0, 20, 40, 60, 80, 100])
        ax.grid(True)
        return fig

    def plot_data(self, file):
        canvas_window = self.builder.get_object("main_win_display")
        # graph data
        fig = self.make_fig(file)
        # add to canvas and window
        canvas = FigureCanvas(fig)
        canvas.set_size_request(900, 500)
        canvas_window.add(canvas)
        canvas_window.show_all()

    def on_td_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data("/var/lib/bat_data")

    def on_yd_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[6])

    def on_2d_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[5])

    def on_3d_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[4])

    def on_4d_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[3])

    def on_5d_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[2])

    def on_6d_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[1])

    def on_wk_clicked(self, button):
        days = self.fetch_bat_log()
        self.plot_data(days[0])


if __name__ == '__main__':
    LBT_gui()
    Gtk.main()
