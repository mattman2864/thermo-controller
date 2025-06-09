import time
from rotary_irq_esp import RotaryIRQ

# modified example from https://www.upesy.com/blogs/tutorials/rotary-encoder-raspberry-pi-pico-on-micro-python#

r = RotaryIRQ(
    pin_num_clk=12,
    pin_num_dt=15,
    reverse=False,
    incr=1,
    range_mode=RotaryIRQ.RANGE_UNBOUNDED,
    pull_up=True,
    half_step=False,
)

val_old = r.value()
while True:
    val_new = r.value()

    if val_old != val_new:
        val_old = val_new
        print("step =", val_new)

    time.sleep_ms(50)