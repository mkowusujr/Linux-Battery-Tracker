import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

# Needed Imports for graphing
from matplotlib.backends.backend_gtk3agg import (
    FigureCanvasGTK3Agg as FigureCanvas)
from matplotlib.figure import Figure
import numpy as np


# Creating gtk window
win = Gtk.Window()
win.connect("delete-event", Gtk.main_quit)
win.set_default_size(1000, 600)
win.set_title("Embedding in GTK3")


# Plotting data to a figure
fig = Figure(figsize=(5, 4), dpi=100)
ax = fig.add_subplot()
t = np.arange(0.0, 3.0, 0.01)
s = np.sin(2*np.pi*t)
ax.plot(t, s)

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