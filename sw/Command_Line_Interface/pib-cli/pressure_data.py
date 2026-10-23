import numpy as np 
import matplotlib.pyplot as plt


FILENAME = "pressure_tank_test_1.csv"


import pandas as pd 

data = pd.read_csv(FILENAME)

time = data['timestamp']
t = time - time[0]

pressure_1 = data['pressure_1']


# temp_good = {
#     0: 0, 5: 2.3, 10: 2.3, 15: 2.48, 20:2.5, 25: 5.0, 30: 5.01,
#     35: 5.1, 40: 6.0, 45: 7.2, 50: 7.5, 55: 7.8, 60: 9.8,
#     65: 10.0, 70: 10.5, 75: 10.8, 80: 11.0, 85: 11.1, 90: 11.3, 95: 11.4
#     100: 11.4, 105: 11.7, 110: 11.5, 115: 81.6, 120: 10, 125: 2.5, 130: 2.3       
# }

temp1 = np.array(pressure_1)


for i in range (temp1.size-1):
        if(pressure_1[i]==pressure_1[i+1]):
            pressure_1.pop(i)
            t.pop(i)


# conversion_H2O_PSI= 0.03613 # psi / inH₂O  
# readings = np.array([10.25,9.25,8.5, 7.8, 3.4, 3, 3.5]) # inches of water 


fig, ax = plt.subplots()

ax.scatter(t, pressure_1, s=16, color = 'g', linestyle='dashed', marker = 'o', label = "Pressure Over Time (Tank)")


#ax.xticks(rotation = 25)
ax.set_xlabel('time (s)')
ax.set_ylabel('Pressure (psi)')
plt.title('Pressure over Time with Nitrogen Tank', fontsize = 20)
ax.grid()
ax.legend()
plt.show()



