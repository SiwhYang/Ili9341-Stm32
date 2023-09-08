import csv
import matplotlib.pyplot as plt
import numpy as np

with open('./GammaData/NewGammaevent.csv', newline='') as f:
    reader = csv.reader(f)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_grayscale = []
temp_brightness = []
temp_x = []


for i in res :
    temp_grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))
    temp_x.append(float(i[2]))

max_brigthness = np.max(temp_brightness)
min_brigthness = np.min(temp_brightness)


idea_y = [] # max_brigthness*(temp_grayscale/255)**2.2

for gray in temp_grayscale :
    idea_y.append( (max_brigthness*(gray/255)**2.2) + min_brigthness*(1 - (gray/255)**2.2)  )
    

plt.scatter(temp_grayscale,temp_brightness,s=5)
plt.scatter(temp_grayscale, idea_y,s=5)
plt.show()



