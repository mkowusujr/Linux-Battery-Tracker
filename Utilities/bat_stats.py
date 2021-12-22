# Load Gtk
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


win = Gtk.Window(title="Linux Battery Tracker")
win.show()
win.connect("destroy", Gtk.main_quit)

Gtk.main()
