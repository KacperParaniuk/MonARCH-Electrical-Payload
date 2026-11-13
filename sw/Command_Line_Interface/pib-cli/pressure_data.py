import numpy as np 
import matplotlib.pyplot as plt


FILENAME = "pressure_tank_test_1.csv"


import pandas as pd 

data = pd.read_csv(FILENAME)

time = data['timestamp']
t = time - time[0]

pressure_1 = data['pressure_1']


pressure_good = {
    0: 0, 5: 2.3, 10: 2.3, 15: 2.48, 20:2.5, 25: 5.0, 30: 5.01,
    35: 5.1, 40: 6.0, 45: 7.2, 50: 7.5, 55: 7.8, 60: 9.8,
    65: 10.0, 70: 10.5, 75: 10.8, 80: 11.0, 85: 11.1, 90: 11.3, 95: 11.4,
    100: 11.4, 105: 11.7, 110: 11.5, 115: 10, 120: 10, 121: 9.9, 122: 9.8, 123: 5, 124: 2.5, 125: 2.5, 130: 2.3       
}

temp1 = np.array(pressure_1)


for i in range (temp1.size-1):
        if(pressure_1[i]==pressure_1[i+1]):
            pressure_1.pop(i)
            t.pop(i)


time_pressure_good = list(pressure_good.keys())
pressure_values = pressure_good.values()


# conversion_H2O_PSI= 0.03613 # psi / inH₂O  
# readings = np.array([10.25,9.25,8.5, 7.8, 3.4, 3, 3.5]) # inches of water 


fig, ax = plt.subplots()

ax.scatter(t, pressure_1, s=25, color = 'g', linestyle='dashed', marker = 'o', label = "PIB Pressure Reading")
ax.scatter(time_pressure_good, pressure_values, s=25, color = 'r', label = "Pressure Regulator Reading")
ax.tick_params(axis='both', labelsize=20)
ax.set_xlabel('time (s)', fontsize=30)
ax.set_ylabel('Pressure (psi)', fontsize=30)
plt.title('Pressure vs. Time in a Nitrogen Tank System', fontsize = 40)
ax.grid()
ax.legend(prop={'size': 25})
plt.show()



