# Load Gtk
import gi
from matplotlib.backends.backend_gtk3agg import FigureCanvasGTK3Agg
import matplotlib.pyplot as plt
import numpy as np
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

    def plot_data(self):
        canvas_window = self.builder.get_object("display_box")
        # graph
        fig = plt.figure()

        #
        canvas = FigureCanvasGTK3Agg(fig)
        canvas.set_size_request(600, 400)
        canvas_window.add(canvas)
        canvas_window.show_all()

if __name__ == '__main__':
    LBT_gui()
    Gtk.main()