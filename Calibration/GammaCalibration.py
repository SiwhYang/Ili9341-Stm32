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


init_Gamma_setting = [0x0F,0x28,0x29,0x0D,0x11,0x09,0x54,\
					 0xA8,0x46,0x0F,0x1A,0x0E,0x14,0x0C,0x00, \
					 0x00,0x1B,0x1E,0x07,0x13,0x07,0x2A,0x47, \
					 0x39,0x03,0x09,0x0C,0x35,0x3D,0x0F ]			

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
    data = list(ser.readline(30))
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
    WriteGamma_setting(init_Gamma_setting)
    Gammasetting = LoadGamma_setting() # // load initial gamma setting, prepare to be modified
    GammaLen = (len(Gammasetting)) # // GammaLen = 30
    OneSide_GammaLen = int (GammaLen/2) # // OneSide_GammaLen = 15
    GammaLen = GammaLen - 1 # // GammaLen = 29 for index
    for i in range(0, OneSide_GammaLen): # // modify gamma setting
        BGammasetting = Gammasetting.copy()
        for j in range (0,3): # // modify gamma for 0 ~ 3 times    
                BGammasetting[i] = (Gammasetting[i]+j*5)
                # BGammasetting[OneSide_GammaLen+i] = (Gammasetting[OneSide_GammaLen+i]+j*5) # // for +- gamma alignment
                BGammasetting[GammaLen-i] = (Gammasetting[GammaLen-i]+j*5)  # // for inverse +- gamma alignment
                WriteGamma_setting(BGammasetting) # // apply modified gamma setting
                AGammasetting = LoadGamma_setting() # // load modified gamma setting
                for k in range(0,len(AGammasetting)): # // turn modified gamma setting to hex and store in csv
                    AGammasetting[k] = (hex(AGammasetting[k]))
                # print("modified gamma index = ",i)
                # print(AGammasetting)
                Filename = str(i) + '_' + str(j) + '_' + 'Gamma'
                filename = Filename + '.csv'
                full_path = os.path.join('GammaData',filename)
                with open(full_path, 'a') as fd:
                    writer = csv.writer(fd)
                    writer.writerow(AGammasetting)
                Gamma.measure(2,full_path)
