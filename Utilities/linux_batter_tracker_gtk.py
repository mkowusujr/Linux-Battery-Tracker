# Load Gtk
import gi
# matplotlib
from matplotlib.backends.backend_gtk3agg import (
    FigureCanvasGTK3Agg as FigureCanvas)
from matplotlib.figure import Figure
import numpy as np
# TODO set up time
import datetime

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
                times.append(time)

                # store battery data
                battery.append(float(line[1]))
        data.close()

        # store data in coordinates
        x_vals = np.array(times)
        y_vals = np.array(battery)

        # plot the coordinates
        ax.plot(x_vals, y_vals)
        return fig


    def plot_data(self, file):
        canvas_window = self.builder.get_object("main_win_display")
        # graph
        # fig = Figure(figsize=(5, 4), dpi=100)
        # ax = fig.add_subplot()
        # t = np.arange(0.0, 3.0, 0.01)
        # s = np.sin(2 * np.pi * t)
        # ax.plot(t, s)
        fig = self.make_fig(file)
        #
        canvas = FigureCanvas(fig)
        canvas.set_size_request(900, 500)
        canvas_window.add(canvas)
        canvas_window.show_all()

if __name__ == '__main__':
    LBT_gui()
    Gtk.main()