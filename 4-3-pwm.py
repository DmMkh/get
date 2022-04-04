import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(22, GPIO.OUT)

try:
  D = 0
  PWM = GPIO.PWM(22, 100)
  while True:
    PWM.start(D)
    D = int(input())
    print(3.3 * D / 100)
    PWM.stop()
finally:
  GPIO.output(22, 0)
  GPIO.cleanup()
