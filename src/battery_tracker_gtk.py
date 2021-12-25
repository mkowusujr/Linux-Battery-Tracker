#!/usr/bin/env python
# Load Gtk
import gi

# matplotlib
from matplotlib.backends.backend_gtk3agg import (
    FigureCanvasGTK3Agg as FigureCanvas)
from matplotlib.figure import Figure
import matplotlib.dates as dates
from matplotlib.ticker import PercentFormatter
from matplotlib.ticker import AutoMinorLocator
import numpy as np

# datetime
import datetime
from datetime import timedelta

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


def fetch_bat_log():
    # list_of_days = []
    with open("/var/log/battery-tracker/bat_log.txt", 'r') as log:
        days = log.readline().strip()
        days = days.split(',')
        list_of_days = days
    log.close()
    if list_of_days[0] == '':
        return ''
    return list_of_days


def queue_len():
    nnn = len(fetch_bat_log())
    return nnn


def open_file(file):
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
    return times, battery


def get_date(index):
    if index < 0:
        return "No Data"
    try:
        if index == 7:
            file = "/var/log/battery-tracker/bat_data"
        else:
            days = fetch_bat_log()
            file = days[index]

        times = open_file(file)
        date_time = times[0][0]
        date_str = date_time.strftime('%A, %B %-d')
        return date_str
    except IndexError:
        return "No Data"


def make_fig(index):
    fig = Figure(figsize=(5, 4), dpi=100)
    ax = fig.add_subplot()

    try:
        if index == 7:
            file = "/var/log/battery-tracker/bat_data"
        else:
            if index < 0:
                raise IndexError
            days = fetch_bat_log()
            file = days[index]

        times, battery = open_file(file)

        # store data in coordinates
        x_vals = np.array(times)
        y_vals = np.array(battery)

        # plot the coordinates
        ax.plot(x_vals, y_vals)

        year = int(times[0].date().strftime("%Y"))
        month = int(times[0].date().strftime("%m"))
        day = int(times[0].date().strftime("%d"))
        next_day = times[0] + timedelta(days=1)
        y2 = int(next_day.date().strftime("%Y"))
        m2 = int(next_day.date().strftime("%m"))
        d2 = int(next_day.date().strftime("%d"))
        ax.set_xlim([datetime.date(year, month, day), datetime.date(y2, m2, d2)])
    except IndexError:
        ax.set_xlim([datetime.date(1970, 1, 1), datetime.date(1970, 1, 2)])
        pass

    ax.set_xlabel("Time")
    ax.xaxis.set_major_locator(dates.HourLocator(interval=4))
    ax.xaxis.set_major_formatter(dates.DateFormatter('%I:%M %p'))

    ax.set_ylabel("Battery Percentage")
    ax.set_ylim(0, 102.5)
    ax.set_yticks([0, 20, 40, 60, 80, 100])
    ax.yaxis.set_major_formatter(PercentFormatter())
    ax.yaxis.set_minor_locator(AutoMinorLocator())
    ax.tick_params(which='minor', length=2, color='r')
    ax.grid(True)
    return fig


class LBTGui:
    def __init__(self):
        self.builder = Gtk.Builder()
        self.builder.add_from_file("lbt_gtk_layout.glade")
        self.builder.connect_signals(self)

        self.window = self.builder.get_object("main_win")
        self.window.show_all()

        date_str = get_date(7)
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(7)

    def plot_data(self, file):
        canvas_window = self.builder.get_object("main_win_display")
        # graph data
        fig = make_fig(file)
        # add to canvas and window
        canvas = FigureCanvas(fig)
        canvas.set_size_request(900, 500)
        canvas_window.add(canvas)
        canvas_window.show_all()

    def on_td_clicked(self, button):
        date_str = get_date(7)
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(7)

    def on_yd_clicked(self, button):
        date_str = get_date(-1 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-1 + queue_len())

    def on_2d_clicked(self, button):
        date_str = get_date(-2 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-2 + queue_len())

    def on_3d_clicked(self, button):
        date_str = get_date(-3 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-3 + queue_len())

    def on_4d_clicked(self, button):
        date_str = get_date(-4 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-4 + queue_len())

    def on_5d_clicked(self, button):
        date_str = get_date(-5 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-5 + queue_len())

    def on_6d_clicked(self, button):
        date_str = get_date(-6 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-6 + queue_len())

    def on_wk_clicked(self, button):
        date_str = get_date(-7 + queue_len())
        self.builder.get_object("chart_name").set_text(date_str)
        self.plot_data(-7 + queue_len())


if __name__ == '__main__':
    LBTGui()
    Gtk.main()
