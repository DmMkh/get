import RPi.GPIO as GPIO
import matplotlib.pyplot as plt
import time
from datetime import datetime

def decimal2binary(value):
  return [int(element) for element in bin(value)[2:].zfill(8)]

dac = [26, 19, 13, 6, 5, 11, 9, 10]
leds = [21, 20, 16, 12, 7, 8, 25, 24]
comp = 4
troyka = 17
data = []

GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT)
GPIO.setup(leds, GPIO.OUT)
GPIO.setup(troyka, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(comp, GPIO.IN)

def printt(val):
    binarval = decimal2binary(int(val))
    GPIO.output(leds, binarval)

def adc():
  for value in range(256):
    sig = decimal2binary(value)
    GPIO.output(dac, sig)
    time.sleep(0.001)
    compval = GPIO.input(comp)
    if compval == 0:
      printt(value)
      return value
  printt(value)
  return value

try:
    start_time = datetime.now()
    ch = 0
    GPIO.output(troyka, GPIO.HIGH)
    while ch < 246:
        one = datetime.now()
        ch = adc()
        one = datetime.now() - one
        data.append(ch)
    GPIO.output(troyka, GPIO.LOW)
    while ch > 6:
        ch = adc()
        data.append(ch)
    end_time = datetime.now()
    
    plt.plot(data)
    plt.show()
    data_str = [str(item) for item in data]
    with open("data.txt", "w") as outfile:
        outfile.write("\n".join(data_str))
    data_str = [str(item) for item in data]
    with open("settings.txt", "w") as outfile:
        outfile.write(str(3.3/255))
        outfile.write(str(one))
    print(end_time - start_time)
    print(one)
    print(3.3/255)
finally:
  GPIO.output(dac, 0)
  GPIO.output(leds, 0)
  GPIO.output(troyka, 0)
  GPIO.cleanup()