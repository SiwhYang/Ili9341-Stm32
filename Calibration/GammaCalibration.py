import serial 
import os
import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time
from csv import writer
import csv
import sys
from GammaMeasurement import Gamma_class

Gammasetting = []
Gamma = Gamma_class()


def MCU_Reset():
    ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)
    command_array = [0xff]
    byte_array = bytearray(command_array)
    time.sleep(0.01)
    ser.write(byte_array)
    ser.flushInput()
    ser.flushOutput()  
    ser.close()  

def LoadGamma_setting():
    ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  
    command_array = [0x9f]
    byte_array = bytearray(command_array)
    time.sleep(0.01)
    ser.write(byte_array)
    data = list(ser.readline(15))
    ser.flushInput()
    ser.flushOutput()  
    ser.close()  
    return data

def WriteGamma_setting(Gammasetting):
    ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  
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
    command_array = [send_show]
    byte_array = bytearray(command_array)
    time.sleep(0.1)
    ser.write(byte_array)    
    ser.flushInput()
    ser.flushOutput()  
    ser.close() 

def Calibration_process():
    

    return



if __name__ == '__main__':
    MCU_Reset()
    time.sleep(1)
    Gamma = Gamma_class()
    Gammasetting = LoadGamma_setting() # // load initial gamma setting, prepare to be modified
    BGammasetting = Gammasetting
    for j in range (0,3): # // modify gamma for 0 ~ 200 times
        for i in range(0,len(Gammasetting)): # // modify gamma setting
            BGammasetting[i] = (Gammasetting[i]+j*5)
        # Gammasetting[0] + j
            WriteGamma_setting(BGammasetting) # // apply modified gamma setting
            AGammasetting = LoadGamma_setting() # // load modified gamma setting
            for i in range(0,len(AGammasetting)): # // turn modified gamma setting to hex adn store in csv
                AGammasetting[i] = (hex(AGammasetting[i]))
            Filename = str(j) + '_' + 'Gamma'
            filename = Filename + '.csv'
            full_path = os.path.join('GammaData',filename)
            with open(full_path, 'a') as fd:
                writer = csv.writer(fd)
                writer.writerow(AGammasetting)
            Gamma.measure(2,full_path)
        