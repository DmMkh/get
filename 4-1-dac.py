import Rpi.GPIO as GPIO
def decimal2binary(value):
  return [int(element) for element in bin(value)[2:].zfill(8)]

dac = [26, 19, 13, 6, 5, 11, 9, 10]

GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT)

try:
  while True:
    x = input()
    if x == 'q':
      exit()
    if x.isdigit() == 0:
      print("Value is not integer")
    else:
      if int(x) > 255:
        print("More than 255")
      elif int(x) < 0:
        print("negative figure")
      else:
        arr = decimal2binary(int(x))
        GPIO.output(dac, arr)
        print(int(x)*3.3/255)
finally:
  GPIO.output(dac, 0)
  GPIO.cleanup()
