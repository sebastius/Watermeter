#!/usr/bin/env python3

print ("Watermeter doorgever")
print ("Control-C om te stoppen")

import serial
import subprocess

#Set COM port config
ser = serial.Serial()
ser.baudrate = 115200
ser.bytesize=serial.EIGHTBITS
ser.parity=serial.PARITY_NONE
ser.stopbits=serial.STOPBITS_ONE
ser.xonxoff=0
ser.rtscts=0
ser.timeout=20
ser.port="/dev/ttyWatertrekker"

#Open COM port
try:
	ser.open()
except:
	sys.exit ("Fout bij het openen van %s. Programma afgebroken."  % ser.name)      

while 1:
	p1_line=''

	try:
		p1_raw = ser.readline()
	except:
		sys.exit ("Seriele poort %s kan niet gelezen worden. Programma afgebroken." % ser.name )      

	p1_str=str(p1_raw, "utf-8")
	p1_line=p1_str.strip()

	if p1_line and p1_str:
		print (p1_line)
		subprocess.run(
			[
				"mqtt-simple",
				"-h",
				"XXXservernaam",
				"-p",
				"XXXtopic",
				"-m",
				str(p1_line),
			]
		)

#Close port and show status
try:
	ser.close()
except:
	sys.exit ("Oops %s. Programma afgebroken." % ser.name )  

