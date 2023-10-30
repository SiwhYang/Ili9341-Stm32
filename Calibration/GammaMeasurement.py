import serial 
import os
import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time
from csv import writer
import csv
import sys

class Gamma_class():


    def measure(self,times,Filename):
        for i in range(0,255,4): # (0,255) change to measure every 4 step
            j = 0
            while j <= times :
                self.measure_one_step(i,Filename)
                time.sleep(1)
                j = j + 1
            print("GrayScale = ", i)

    def measure_one_step(self,grayscale,Filename):  
        data_list = []
        self.Grayscale_send2Board_sequence(grayscale)
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
        # filename = Filename + '.csv'
        # full_path = os.path.join('GammaData',filename)
        full_path = Filename
        with open(full_path, 'a') as fd:
            writer = csv.writer(fd)
            writer.writerow(data_list)
     

    def Grayscale_send2Board_sequence(self,grayscale) :
        ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  
        RGB565_hex = self.GrayScale2RGB565(grayscale)
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
        ser.close() 

    def Color_send2Board_sequence(self,grayscale_R,grayscale_G,grayscale_B) :
        ser = serial.Serial( port='COM5', baudrate=115200, parity=serial.PARITY_NONE,\
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  
        RGB565_hex = self.Color2RGB565(grayscale_R,grayscale_G,grayscale_B)
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
        ser.close()

    



    def GrayScale2RGB565(self,grayscale):
        #  // grayscale 0 ~ 255
        temp_hex = 0
        R_hex = int(grayscale/8)
        G_hex = int(grayscale/4)
        B_hex = int(grayscale/8)
        RGB565_hex = (((((temp_hex | R_hex) << 6 ) | G_hex) << 5) | B_hex)
        return RGB565_hex

    def Color2RGB565(self,grayscale_R,grayscale_G,grayscale_B):
        #  // grayscale 0 ~ 255
        temp_hex = 0
        R_hex = int(grayscale_R/8)
        G_hex = int(grayscale_G/4)
        B_hex = int(grayscale_B/8)
        RGB565_hex = (((((temp_hex | R_hex) << 6 ) | G_hex) << 5) | B_hex)
        return RGB565_hex


if __name__ == '__main__':
    Gamma_tool = Gamma_class()
    Gamma_tool.measure(3,'newevent')




