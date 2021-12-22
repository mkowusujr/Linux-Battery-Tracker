# Load Gtk
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class LBT_gui:
    def __init__(self):
        self.builder = Gtk.Builder()
        self.builder.add_from_file("lbt_gtk_layout.glade")
        self.builder.connect_signals(self)

        self.window = self.builder.get_object("main_win")
        self.window.show_all()

if __name__ == '__main__':
    LBT_gui()
    Gtk.main()
# win = Gtk.Window(title="Linux Battery Tracker")
# win.show()
# win.connect("destroy", Gtk.main_quit)
#
# Gtk.main()
