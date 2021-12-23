import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

# Needed Imports for graphing
from matplotlib.backends.backend_gtk3agg import (
    FigureCanvasGTK3Agg as FigureCanvas)
from matplotlib.figure import Figure
import numpy as np
import datetime


def make_fig(file):
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

# Creating gtk window
win = Gtk.Window()
win.connect("delete-event", Gtk.main_quit)
win.set_default_size(1000, 600)
win.set_title("Embedding in GTK3")

# Plotting data to a figure
# fig = Figure(figsize=(5, 4), dpi=100)
# ax = fig.add_subplot()
# t = np.arange(0.0, 3.0, 0.01)
# s = np.sin(2*np.pi*t)
# ax.plot(t, s)
fig = make_fig("/var/lib/bat_data")

# sw = Gtk.ScrolledWindow()
# win.add(sw)
# A scrolled window border goes outside the scrollbars and viewport
# sw.set_border_width(10)
# Draw to canvas
canvas = FigureCanvas(fig)  # a Gtk.DrawingArea
canvas.set_size_request(500, 250)
# sw.add(canvas)


# add to window
win.add(canvas)
win.show_all()
Gtk.main()