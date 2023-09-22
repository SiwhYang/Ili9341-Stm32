import csv
import matplotlib.pyplot as plt
import numpy as np
import glob
import os

# datapath = os.path.join('GammaData','Inverse_alignment')
datapath = os.path.join('GammaData','alignment')
csvfilepath = glob.glob(os.path.join(datapath, '*.csv'))

def data_loading (path):
    for csvfile in path:
        with open(csvfile, newline='') as f:
            reader = csv.reader(f)
            next(reader)
            data = list(reader)
            res = [ele for ele in data if ele != []]
            
            name = (csvfile.split("\\")[2]).split(".")[0] # // extract variable name from file name
            globals()['temp_grayscale_' + str(name)] = []
            globals()['temp_brightness_' + str(name)]= []
            globals()['temp_x_' + str(name)] = []
            for i in res :
                globals()['temp_grayscale_' + str(name)].append(float(i[0]))
                globals()['temp_brightness_' + str(name)].append(float(i[1]))
                globals()['temp_x_' + str(name)].append(float(i[2]))

temp_grayscale = np.arange(0,255)
idea_max_brigthness = 150 # np.max(temp_brightness)
idea_min_brigthness = 0 # np.min(temp_brightness)
idea_y = [] # max_brigthness*(temp_grayscale/255)**2.2
for gray in temp_grayscale :
    idea_y.append( (idea_max_brigthness*(gray/255)**2.2) + idea_min_brigthness*(1 - (gray/255)**2.2)  )

data_loading(csvfilepath)



for i in range(8,9): # // first
    for j in range(55,65): #// second
        plt.scatter(globals()['temp_grayscale_' + str(i) + '_' +str(j) + '_Gamma'] \
        ,globals()['temp_brightness_' + str(i) + '_' +str(j) + '_Gamma' ],s=5, label = str(i) + '_' +str(j) )
        plt.legend()
    print(i)
 
# plt.scatter(temp_grayscale_0_5_Gamma,temp_brightness_0_5_Gamma,s=5)
plt.scatter(temp_grayscale, idea_y,s=5)
plt.show()









