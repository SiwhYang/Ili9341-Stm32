import serial 
import os
import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time
from csv import writer
import csv
import sys

ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  

Gammasetting = []


def LoadGamma_setting():
    command_array = [0x9f]
    byte_array = bytearray(command_array)
    time.sleep(0.01)
    ser.write(byte_array)
    data = list(ser.readline(15))
    return data

def WriteGamma_setting(Gammasetting):
    send_usart = 0x00
    command_array = []
    for i in range(0,len(Gammasetting)):  # // 0x60 = 96 in decimal 
        send_data1 = (send_usart | (0xA0)) | ((Gammasetting[i] >> 0 ) & 0xF)
        send_data2 = (send_usart | (0xB0)) | ((Gammasetting[i] >> 4 ) & 0xF)
        send_save =  (send_usart | (0xD0))
        
        command_array = [send_data1,send_data2,send_save]
        byte_array = bytearray(command_array)
        time.sleep(0.1)
        ser.write(byte_array)     
    
    send_show =  (send_usart | (0xC0))
    command_array = [send_save]
    byte_array = bytearray(command_array)
    time.sleep(0.1)
    ser.write(byte_array)    



if __name__ == '__main__':
    Gammasetting = LoadGamma_setting()
    print("Before",Gammasetting)
    for i in range(0,len(Gammasetting)):
        Gammasetting[i] = Gammasetting[i]-20
     
    WriteGamma_setting(Gammasetting)
    AGammasetting = LoadGamma_setting()
    print("After",AGammasetting)