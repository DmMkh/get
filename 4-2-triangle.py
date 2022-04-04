import Rpi.GPIO as GPIO
import time

def decimal2binary(value):
  return [int(element) for element in bin(value)[2:].zfill(8)]

dac = [26, 19, 13, 6, 5, 11, 9, 10]

GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT)

try:
  print("Enter value ")
  x = input()
  while True:
    if x.isdigit() == 0:
      print("Value is not integer")
    else:
      if int(x) < 0:
        print("unreal time")
      else:
        t = int(x) / (1000 * 2 * 255)
        for i in range(0, 255)
          arr = decimal2binary(i)
          GPIO.output(dac, arr)
          time.sleep(t)
        for i in range(0, 255)
          arr = decimal2binary(255-i)
          GPIO.output(dac, arr)
          time.sleep(t)
finally:
  GPIO.output(dac, 0)
  GPIO.cleanup()
