import os


def main():
	# make the needed directories
	print("Creating needed directories...")
	os.system("sudo mkdir /var/log/battery-tracker")
	os.system("sudo mkdir /var/log/battery-tracker/Past Days")
	os.system("sudo mkdir /usr/lib/battery-tracker")
	os.system("sudo mkdir /usr/lib/battery-tracker/src")
	os.system("sudo mkdir /usr/lib/battery-tracker/Utilities")

	# copy over program files to those locations
	print("Copying over program files...")
	os.system("sudo cp src/battery_tracker.c /usr/lib/battery-tracker/src")
	os.system("sudo cp Utilities/queue.h /usr/lib/battery-tracker/Utilities")
	os.system("sudo cp Utilities/file_queue.c /usr/lib/battery-tracker/Utilities")
	os.system("sudo cp src/battery.service /etc/systemd/system")

	# compile the program
	print("Compiling Program files")
	os.system("sudo gcc src/battery_tracker.c Utilities/file_queue.c -o battery_tracker")

	# create systemctl service file and enable it
	print("Starting the background process")
	os.system("systemctl daemon-reload")
	os.system("systemctl enable battery.service")
	os.system("systemctl start battery.service")

	# create desktop file
	os.system("sudo cp src/battery-tracker.desktop /usr/share/applications")


if __name__ == '__main__':
	main()
