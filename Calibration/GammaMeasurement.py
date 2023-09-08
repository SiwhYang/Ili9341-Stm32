import serial 
import os
import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time
from csv import writer
import csv
import sys

def measure_one_step(grayscale):
    data_list = []
    Grayscale_send2Board_sequence(grayscale)
    spectrum_data = subprocess.run(args=['Optimum.exe'],stdout = subprocess.PIPE)
    measure_data = spectrum_data.stdout.split()
    # measure_data = [b'Status=0', b'Brightness=2.84842567199369', b'CIEx=0.611512659639738', b'CIEy=0.347234174151531', b'CCT=2161.95536236243']
    Brightness = float(str(measure_data[1]).split('=')[1].split("'")[0])
    x = float(str(measure_data[2]).split('=')[1].split("'")[0])
    y = float(str(measure_data[3]).split('=')[1].split("'")[0])
    data_list.append(grayscale)
    data_list.append(Brightness)
    data_list.append(x)
    data_list.append(y)
    # save data
    with open('NewGammaevent.csv', 'a') as fd:
        writer = csv.writer(fd)
        writer.writerow(data_list)


def Grayscale_send2Board_sequence(grayscale) :
    RGB565_hex = GrayScale2RGB565(grayscale)
    send_usart = 0
    send_start = (send_usart | (0x60))  # // 0x60 = 96 in decimal 
    send_data1 = (send_usart | (0x10)) | ((RGB565_hex >> 0 ) & 0xF)
    send_data2 = (send_usart | (0x20)) | ((RGB565_hex >> 4 ) & 0xF)
    send_data3 = (send_usart | (0x30)) | ((RGB565_hex >> 8 ) & 0xF)
    send_data4 = (send_usart | (0x40)) | ((RGB565_hex >> 12) & 0xF)
    send_show =  (send_usart | (0x50))
    
    command_array = [send_start, send_data1,send_data2,send_data3,send_data4,send_show ]
    byte_array = bytearray(command_array)
    time.sleep(0.01)
    ser.write(byte_array) 
    # ser.close()



def GrayScale2RGB565(grayscale):
    #  // grayscale 0 ~ 255
    temp_hex = 0
    R_hex = int(grayscale/8)
    G_hex = int(grayscale/4)
    B_hex = int(grayscale/8)
    RGB565_hex = (((((temp_hex | R_hex) << 6 ) | G_hex) << 5) | B_hex)
    return RGB565_hex



ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  
# target_array = [0,100,64,255]
for i in range(0,255):
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    measure_one_step(i)
    time.sleep(1)
    print("GrayScale = ", i)


# def RGB5652grayscale(RGB565):
#     #  // grayscale 0 ~ 255
#     temp_R = (RGB565 >> 11 & 0x1F ) * 8
#     temp_G = (RGB565 >> 5  & 0x3F ) * 4
#     temp_B = (RGB565 & 0x1F ) * 8
#     return temp_R, temp_G, temp_B


# # print(hex(GrayScale2RGB565(1)))
# test_array = [ 0x00, 0x1082, 0x2104, 0x3186, 0x4208, 0x528a, 
# 0x630c, 0x738e, 0x8430, 0x94b2, 0xa534, 0xb5b6, 0xc638, 0xd6ba, 0xe73c, 0xf7be, 0xffff] 

# for grayscale in test_array :
#     print(RGB5652grayscale(grayscale))
