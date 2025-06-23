from machine import Pin,UART

uart=UART(0,baudrate=9600 ,tx=Pin(0) ,rx=Pin(1))
while True:
    if uart.any():
        message=uart.read().decode()
        print(message)
    