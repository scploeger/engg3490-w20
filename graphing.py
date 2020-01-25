import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as poly

#read in temp curve csv
db = pd.read_csv("temp_data.csv", encoding = "ISO-8859-1")
a=db.values
deg_c = a[:,0]
analog_value = a[:,1]

print(analog_value)


#read in step response csv
data = pd.read_csv("step.csv", encoding = "ISO-8859-1")
b=data.values

sensor_values = b[128:,2] #the sensor was dunked at approx sample #128
time = b[128:,1]#row 128-end, column 1

#switch to figure 1
plt.figure(1)

#title and axis labels
plt.title('Step Response of Thermister When Submerged in Ice Water')
plt.xlabel("time (ms)")
plt.ylabel("analogRead Value")

#plot raw data
plt.scatter(time,sensor_values, label = "Sensor Data")

#line of best fit 1
coeffs1 = poly.polyfit(time, sensor_values, 1)
ffit = poly.polyval(time, coeffs1)
plt.plot(time, ffit, 'm', label = '1st Degree Polynomial')

#line of best fit 2
coeffs2 = poly.polyfit(time, sensor_values, 2)
ffit = poly.polyval(time, coeffs2)
plt.plot(time, ffit, 'k',  label = '2nd Degree Polynomial')

#add a legend
plt.legend()

#save the figure
plt.savefig('response.png')


#display the plot
plt.show()


#switch to figure 1
plt.figure(2)

#title and axis labels
plt.title('AnalogRead Curve From Sensor')
plt.xlabel("degree C")
plt.ylabel("analogRead Value")

#plot raw data
plt.scatter(deg_c,analog_value, label = "Sensor Data")

#line of best fit 3
coeffs3 = poly.polyfit(deg_c, analog_value, 3)
ffit = poly.polyval(deg_c, coeffs3)
plt.plot(deg_c, ffit, 'm', label = '3st Degree Polynomial')
print(coeffs3)

#add a legend
plt.legend()

#save the figure
plt.savefig('curve.png')


#display the plot
plt.show()
