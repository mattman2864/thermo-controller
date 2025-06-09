# For temperature reading
from utime import sleep_ms, sleep_us
from machine import Pin
from time import sleep
import onewire, ds18x20

#originally based off of DS1820
#https://iopress.info/index.php/books/programming-the-raspberry-pi-pico-in-micropython/9-programs/55-picopythonprograms
#Page 245

#modified from forum post by ajevtic
#https://forum.micropython.org/viewtopic.php?t=12679


# using builtin scan function may be needed if getting crc error
ow = onewire.OneWire(Pin(33))
ds = ds18x20.DS18X20(ow)
roms = ds.scan()

class MAX31850:
    def __init__(self, pin):
        self.pin = Pin(pin, mode=Pin.IN)
        self.pin.on()

    def presence(self): #initialization handshake
        self.pin.init(mode=Pin.OUT)
        self.pin.on()
        sleep_ms(1)
        self.pin.off()
        sleep_us(480)
        self.pin.init(mode=Pin.IN)
        sleep_us(70)
        b = self.pin.value()
        sleep_us(410)
        return b

    @micropython.native  #writing bits 
    def writeBit(self, b):
        if b == 1:
            delay1 = 1
            delay2 = 30
        else:
            delay1 = 30
            delay2 = 0
        self.pin.off()
        for i in range(delay1):
            pass
        self.pin.on()
        for i in range(delay2):
            pass

    def writeByte(self, byte):  #will write the off eight bits of an  int to the device 
        self.pin.init(mode=Pin.OUT)
        for i in range(8):
            self.writeBit(byte & 1)
            byte = byte >> 1
        self.pin.init(mode=Pin.IN)

    @micropython.native  #reading bits 
    def readBit(self):
        self.pin.init(mode=Pin.OUT)
        self.pin.off()
        self.pin.on()
        self.pin.init(mode=Pin.IN)
        b = self.pin.value()
        sleep_us(60)
        return b

    def readByte(self): #make a byte 
        byte = 0
        for i in range(8):
            byte = byte | self.readBit() << i
        return byte

    def convert(self): #start conversion
        self.writeByte(0x44)
        for i in range(500):
            sleep_ms(10)
            if self.readBit() == 1:
                j = i
                break
        return j

    def crc8(self, data, len): #cyclic redundancy checksum
        crc = 0
        for i in range(len):
            databyte = data[i]
            for j in range(8):
                temp = (crc ^ databyte) & 0x01
                crc >>= 1
                if temp:
                    crc ^= 0x8C
                databyte >>= 1
        return crc

    def getTemp(self):
        if self.presence() == 1:
            return -1000 #no device 
        self.writeByte(0xCC)
        if self.convert() == 500:
            return -3000 #device faild to provide data 
        self.presence()
        
        self.writeByte(0xCC) #skip ROM read
        self.writeByte(0xBE) #read scratchpad
        data = []
        for i in range(9):
            data.append(self.readByte())
        if self.crc8(data, 9) != 0:
            return -2000 #crc error
        
        t1 = data[0]
        t2 = data[1]
        t3 = data[2]
        t4 = data[3]
        
        t2 = t2 << 8
        temp1 = t2 | t1
        temp1 = temp1 >> 2 #remove fault detection, comment when using test data 

        if (temp1 >> 13 != 1):
            temp1 = temp1 * 0.25
        else:  
            temp1 = temp1 - 0b100000000000000
            temp1 = temp1 * 0.25         
        

        t4 = t4 << 8
        temp2 = t4 | t3
        temp2 = temp2 >> 4 #remove fault detection, comment when using test data
        if (temp2 >> 11 != 1):
            temp2 = temp2 * 0.0625
        else:
            temp2 = temp2 - 0b1000000000000
            temp2 = temp2 * 0.0625
            
        return temp1


max31850 = MAX31850(33)
target = 25.0

while True:
    max31850.presence()
    temp = max31850.getTemp()
    if temp <= -1000:
        print(f"({temp})", end=" ")
        if temp == -1000:
            print("no device")
        elif temp == -2000:
            print("crc error")
        elif temp == -3000:
            print("device failed to provide data")
    else:
        print(f"Temp: {temp}")
    sleep_ms(750)
