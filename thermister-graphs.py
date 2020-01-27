import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as poly

#read in middle of room csv
db = pd.read_csv("thermister-middle.csv", encoding = "ISO-8859-1")
a=db.values
time = a[:,0]
thermistor_value1 = a[:,1]

#read in window csv
db = pd.read_csv("thermister-window.csv", encoding = "ISO-8859-1")
b=db.values
time = b[:,0]
thermistor_value2 = b[:,1]

#read in doorway csv
db = pd.read_csv("thermister-dooraway.csv", encoding = "ISO-8859-1")
c=db.values
time = c[:,0]
thermistor_value3 = c[:,1]

#read in power supply fan csv
db = pd.read_csv("thermister-fan.csv", encoding = "ISO-8859-1")
d=db.values
time = d[:,0]
thermistor_value4 = d[:,1]



#switch to figure 1
plt.figure(1)

#title and axis labels
plt.title('Thermistor analogRead() Values from Middle of Room')
plt.xlabel("time [s]")
plt.ylabel("analogRead() Value")

#find std deviation
std_dev = np.std(thermistor_value1)
e = np.full((len(time), 1), std_dev)
print(std_dev)

#plot data
plt.scatter(time,thermistor_value1, label = "Thermistor Data")
plt.plot(time, [thermistor_value1.mean()]*len(time), 'r', label = "Mean = {}".format(thermistor_value1.mean()), linestyle = '--')
plt.errorbar(time, thermistor_value1, e, 0, 'k', label = "Standard Deviation = {}".format(std_dev), linestyle='None', marker='None')

#add a legend
plt.legend()

#save the figure
plt.savefig('thermister-middle.png')


#display the plot
plt.show()

#switch to figure 2
plt.figure(2)

#title and axis labels
plt.title('Thermistor analogRead() Values from near a Window')
plt.xlabel("time [s]")
plt.ylabel("analogRead() Value")

#find std deviation
std_dev = np.std(thermistor_value2)
e = np.full((len(time), 1), std_dev)
print(std_dev)

#plot data
plt.scatter(time,thermistor_value2, label = "Thermistor Data")
plt.plot(time, [thermistor_value2.mean()]*len(time), 'r', label = "Mean = {}".format(thermistor_value2.mean()), linestyle = '--')
plt.errorbar(time, thermistor_value2, e, 0, 'k', label = "Standard Deviation = {}".format(std_dev), linestyle='None', marker='None')

#add a legend
plt.legend()

#save the figure
plt.savefig('thermister-window.png')


#display the plot
plt.show()

#switch to figure 3
plt.figure(3)

#title and axis labels
plt.title('Thermistor analogRead() Values from in a Doorway')
plt.xlabel("time [s]")
plt.ylabel("analogRead() Value")

#find std deviation
std_dev = np.std(thermistor_value3)
e = np.full((len(time), 1), std_dev)
print(std_dev)

#plot data
plt.scatter(time,thermistor_value3, label = "Thermistor Data")
plt.plot(time, [thermistor_value3.mean()]*len(time), 'r', label = "Mean = {}".format(thermistor_value3.mean()), linestyle = '--')
plt.errorbar(time, thermistor_value3, e, 0, 'k', label = "Standard Deviation = {}".format(std_dev), linestyle='None', marker='None')

#add a legend
plt.legend()

#save the figure
plt.savefig('thermister-doorway.png')


#display the plot
plt.show()


#switch to figure 4
plt.figure(4)

#title and axis labels
plt.title('Thermistor analogRead() Values from in Front of a Power Supply Fan')
plt.xlabel("time [s]")
plt.ylabel("analogRead() Value")

#find std deviation
std_dev = np.std(thermistor_value4)
e = np.full((len(time), 1), std_dev)
print(std_dev)

#plot data
plt.scatter(time,thermistor_value4, label = "Thermistor Data")
plt.plot(time, [thermistor_value4.mean()]*len(time), 'r', label = "Mean = {}".format(thermistor_value4.mean()), linestyle = '--')
plt.errorbar(time, thermistor_value4, e, 0, 'k', label = "Standard Deviation = {}".format(std_dev), linestyle='None', marker='None')

#add a legend
plt.legend()

#save the figure
plt.savefig('thermister-fan.png')


#display the plot
plt.show()



