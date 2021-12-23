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
        self.plot_data()


    def plot_data(self):
        canvas_window = self.builder.get_object("main_win_display")
        # graph
        fig = Figure(figsize=(5, 4), dpi=100)
        ax = fig.add_subplot()
        t = np.arange(0.0, 3.0, 0.01)
        s = np.sin(2 * np.pi * t)
        ax.plot(t, s)

        #
        canvas = FigureCanvas(fig)
        canvas.set_size_request(1005, 400)
        canvas_window.add(canvas)
        canvas_window.show_all()

if __name__ == '__main__':
    LBT_gui()
    Gtk.main()