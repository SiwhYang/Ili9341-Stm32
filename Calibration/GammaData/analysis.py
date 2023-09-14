import csv
import matplotlib.pyplot as plt
import numpy as np
import glob
import os

datapath = os.path.join('GammaData','Firstrecord')
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
idea_max_brigthness = 125 # np.max(temp_brightness)
idea_min_brigthness = 0 # np.min(temp_brightness)
idea_y = [] # max_brigthness*(temp_grayscale/255)**2.2
for gray in temp_grayscale :
    idea_y.append( (idea_max_brigthness*(gray/255)**2.2) + idea_min_brigthness*(1 - (gray/255)**2.2)  )

data_loading(csvfilepath)



for i in range(1,4):
    for j in range(0,2):
        plt.scatter(globals()['temp_grayscale_' + str(i) + '_' +str(j) + '_Gamma'] \
        ,globals()['temp_brightness_' + str(i) + '_' +str(j) + '_Gamma' ],s=5)

# plt.scatter(temp_grayscale_1_0_Gamma,temp_brightness_1_0_Gamma,s=5)
# plt.scatter(temp_grayscale_1_1_Gamma,temp_brightness_1_1_Gamma,s=5)
# plt.scatter(temp_grayscale_1_2_Gamma,temp_brightness_1_2_Gamma,s=5)
# plt.scatter(temp_grayscale_2_0_Gamma,temp_brightness_2_0_Gamma,s=5)
# plt.scatter(temp_grayscale_2_1_Gamma,temp_brightness_2_1_Gamma,s=5)

plt.scatter(temp_grayscale, idea_y,s=5)
plt.show()






# with open('./GammaData/1_1_Gamma.csv', newline='') as f:
#     reader = csv.reader(f)
#     next(reader)
#     data = list(reader)
#     res = [ele for ele in data if ele != []]
  
# temp_grayscale = []
# temp_brightness = []
# temp_x = []

# for i in res :
#     temp_grayscale.append(float(i[0]))
#     temp_brightness.append(float(i[1]))
#     temp_x.append(float(i[2]))

# max_brigthness = np.max(temp_brightness)
# min_brigthness = np.min(temp_brightness)

# idea_y = [] # max_brigthness*(temp_grayscale/255)**2.2

# for gray in temp_grayscale :
#     idea_y.append( (max_brigthness*(gray/255)**2.2) + min_brigthness*(1 - (gray/255)**2.2)  )
    

# plt.scatter(temp_grayscale,temp_brightness,s=5)
# plt.scatter(temp_grayscale, idea_y,s=5)
# plt.show()



