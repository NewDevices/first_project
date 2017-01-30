# author: Hendrik Werner s4549775

import serial
import argparse

arg_parser = argparse.ArgumentParser()
arg_parser.add_argument("usbport")
arg_parser.add_argument("baud")

args = arg_parser.parse_args()

reader = serial.Serial("/dev/ttyUSB{}".format(args.usbport), args.baud)

while True:
	print(reader.readline())
