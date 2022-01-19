import os


def main():
	# make the needed directories
	print("Creating needed directories...")
	os.system("sudo mkdir /var/log/battery-tracker")
	os.system("sudo mkdir /var/log/battery-tracker/past-days")
	os.system("sudo mkdir /usr/lib/battery-tracker")
	os.system("sudo mkdir /usr/lib/battery-tracker/src")
	os.system("sudo mkdir /usr/lib/battery-tracker/Utilities")
	print("done...")
	
	# downloaded packages for gtk
	print("Downloading python packages for gtk application")
	os.system("pip install -r requirements.txt")

	# copy over program files to those locations
	print("Copying over program files...")
	os.system("sudo cp src/battery_tracker.c /usr/lib/battery-tracker/src")
	os.system("sudo cp Utilities/queue.h /usr/lib/battery-tracker/Utilities")
	os.system("sudo cp Utilities/file_queue.c /usr/lib/battery-tracker/Utilities")
	os.system("sudo cp src/battery.service /etc/systemd/system")
	print("done...")
	
	# compile the program
	print("Compiling Program files")
	os.system("sudo gcc /usr/lib/battery-tracker/src/battery_tracker.c /usr/lib/battery-tracker/Utilities/file_queue.c -o /usr/lib/battery-tracker/battery_tracker")
	print("done...")
	
	# create systemctl service file and enable it
	print("Starting the background process")
	os.system("systemctl daemon-reload")
	os.system("systemctl enable battery.service")
	os.system("systemctl start battery.service")
	print("done...")
	
	# create desktop file
	print("Creating desktop file in applications...")
	os.system("sudo cp src/battery-tracker.desktop /usr/share/applications")
	print("Installation is done and complete. The Battery Tracker is running in the background")

	
if __name__ == '__main__':
	main()
