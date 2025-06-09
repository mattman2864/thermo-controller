import machine
import time
import math

p15 = machine.Pin(15)
pwm15 = machine.PWM(p15)
FREQ = 1000
pwm15.freq(FREQ)
t = 0
while 1:
    pwm15.duty(sinusoidal(t))
    time.sleep(0.001)
    t += 1

def sinusoidal(t):
    return int(math.sin(t/1000 * math.pi) * 512) + 512