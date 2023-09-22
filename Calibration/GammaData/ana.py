import csv
import matplotlib.pyplot as plt
import numpy as np








with open('./GammaData/4_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '4')


with open('./GammaData/5_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '5')

with open('./GammaData/6_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '6')


with open('./GammaData/7_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '7')


with open('./GammaData/8_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '8')

with open('./GammaData/9_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '9')



with open('./GammaData/10_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '10')



with open('./GammaData/11_Gamma.csv', newline='') as f:
    reader = csv.reader(f)
    next(reader)
    data = list(reader)
    res = [ele for ele in data if ele != []]
  
temp_Grayscale = []
temp_brightness = []


for i in res :
    temp_Grayscale.append(float(i[0]))
    temp_brightness.append(float(i[1]))

plt.scatter(temp_Grayscale,temp_brightness,s=5,label = '11')

temp_grayscale = np.arange(0,255)
idea_max_brigthness = 150 # np.max(temp_brightness)
idea_min_brigthness = 0 # np.min(temp_brightness)
idea_y = [] # max_brigthness*(temp_grayscale/255)**2.2
for gray in temp_grayscale :
    idea_y.append( (idea_max_brigthness*(gray/255)**2.2) + idea_min_brigthness*(1 - (gray/255)**2.2)  )



plt.scatter(temp_grayscale, idea_y,s=5)
plt.legend()
plt.show()