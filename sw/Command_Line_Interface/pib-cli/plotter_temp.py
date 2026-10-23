import matplotlib.pyplot as plt
import csv
import numpy as np 
from sklearn.metrics import r2_score 



FILENAME = "voltage.csv"



import pandas as pd 


# implement reading a CSV file into a bunch of arrays 


data = pd.read_csv("heat_test_power_supply.csv")

time = data['timestamp']

t = time - time[0]
voltage_3V3 = data['3V3_VA']
temp1 = data['temperature_1']
temp1_cj = data['cj_temperature_1']
pressure1 = data['pressure_1']


temp_good = {
    0: 22.5, 2: 22.5, 3: 22.5, 4: 22.8, 6: 24.7, 8: 28.2, 10: 34.1,
    12: 40.2, 14: 48.5, 16: 55.9, 18: 65.1, 20: 72.9, 22: 80.8,
    24: 86.7, 26: 88.9, 28: 90, 30: 90.3, 32: 89.7, 34: 88.7,
    36: 87, 38: 85.3, 40: 83.1, 42: 81.6,
}

# temp_good = [0]*len(t)

# temp_good[0]=22.5
# temp_good[2]=22.5
# temp_good[3]=22.5
# temp_good[4]=22.8
# temp_good[6]=24.7
# temp_good[8]=28.2
# temp_good[10]=34.1
# temp_good[12]=40.2
# temp_good[14]=48.5
# temp_good[16]=55.9
# temp_good[18]=65.1
# temp_good[20]=72.9
# temp_good[22]=80.8
# temp_good[24]=86.7
# temp_good[26]=88.9
# temp_good[28]=90
# temp_good[30]=90.3
# temp_good[32]=89.7
# temp_good[34]=88.7
# temp_good[36]=87
# temp_good[38]=85.3
# temp_good[40]=83.1
# temp_good[42]=81.6


# plot all graphs from subsquent arrays & the time array


# plt.plot(temp1, t, color = 'g', linestyle = 'dashed',
#          marker = 'o',label = "Temperature vs Time")


# 1.26 A  12 Volts 
# 15.12 W
# legend  >> pib temp sensor was closer to the heatsink injector 
# Handheld Readout >> further from the injector (heat sink) closer 

temp = np.array(temp1)


for i in range (temp.size-1):
        if(temp1[i]==temp1[i+1]):
            temp1.pop(i)
            t.pop(i)



ref_t = list(temp_good.keys())

# print(t)

fig, ax = plt.subplots()

ax.scatter(t, temp1, s=16, label="PIB Measured Temperature Closer to Heatsink (Injector)")
ax.scatter(ref_t, temp_good.values(), s=20, color='r', label="Handheld Readout Further from Heatsink")  # different times



ax.set_xlabel("Time (s)")
ax.set_ylabel("Temperature (°C)")
plt.title('15.12 Watt Chemical Thruster Heat Test', fontsize = 20)

ax.legend()
ax.grid(True)
plt.show()



# plt.scatter(t, temp1, s=2)
# plt.scatter(t,temp_good)
# plt.show()
# fig, ax = plt.subplots(2,2)

# ax[0,0].plot(t, voltage_3V3); ax[0,0].set_title("3V3 vs Time")
# ax[0,1].plot(t, temp1); ax[0,1].set_title("Temperature vs Time")
# ax[1,0].plot(t, temp1_cj); ax[1,0].set_title("Cold Junction Temperature vs Time")


# units, label every axis, capacitance across accumulators (what's experiment being run)
# need to mention water

# volume = [.5, .55,.6,.65,.7,.75,.8,.85,.9]

# c1 = ((.404835+.404781+.404710+.404894+.404850)/5)
# c2 = (.404863+.404913+.404973+.405005+.404949)/5
# c3 = (.404699+.404930+.404940+.404843+.404796)/5
# c4 = (.405025+.404939+.404905+.404863+.404939)/5
# c5 = (.405091+.404990+.404938+.404972+.404966)/5
# c6 = (.404991+.405022+.405113+.405038+.405053)/5
# c7 = (.405074+.405109+.405142+.405146+.405017)/5
# c8 = (.405197+.405021+.405044+.405100+.405160)/5
# c9 = (.405124+.405101+.405046+.405151+.405125)/5

# readings = np.array([
#     [.404835, .404781, .404710, .404894, .404850],
#     [.404863, .404913, .404973, .405005, .404949],
#     [.404699, .404930, .404940, .404843, .404796],
#     [.405025, .404939, .404905, .404863, .404939],
#     [.405091, .404990, .404938, .404972, .404966],
#     [.404991, .405022, .405113, .405038, .405053],
#     [.405074, .405109, .405142, .405146, .405017],
#     [.405197, .405021, .405044, .405100, .405160],
#     [.405124, .405101, .405046, .405151, .405125],
# ])



# # 3 
# # 6 


# # https://www.geeksforgeeks.org/python/errorbar-graph-in-python-using-matplotlib/ 

# c_uncert = [np.std(readings[0]), np.std(readings[1]), np.std(readings[2]), np.std(readings[3]), np.std(readings[4]), np.std(readings[5]), np.std(readings[6]), np.std(readings[7]), np.std(readings[8])]/(np.sqrt(5))

# c_uncert_3_6 = [np.std(readings[3]), np.std(readings[4]), np.std(readings[5]), np.std(readings[6])]


# capacitor = [((.404835+.404781+.404710+.404894+.404850)/5),(.404863+.404913+.404973+.405005+.404949)/5, (.404699+.404930+.404940+.404843+.404796)/5,(.405025+.404939+.404905+.404863+.404939)/5,(.405091+.404990+.404938+.404972+.404966)/5,(.404991+.405022+.405113+.405038+.405053)/5,(.405074+.405109+.405142+.405146+.405017)/5,(.405197+.405021+.405044+.405100+.405160)/5, (.405124+.405101+.405046+.405151+.405125)/5]


# volume = volume[3:7]
# capacitor = capacitor[3:7]
# slope, intercept = np.polyfit(volume, capacitor, 1)
# slope_print = slope

# volume = np.array(volume)

# fit_line = slope * volume + intercept # y predicted 

# r2 = r2_score(capacitor, fit_line)

# print(r2)

# equation = f"y = {slope:.8f} * x + {intercept:.2f}" # https://medium.com/@saicoumar/fitting-a-mathematical-function-to-a-dataset-with-python-56c9a9143470 



# plt.plot(volume, capacitor, color = 'g', linestyle = 'dashed',
#          marker = 'o',label = "FDC2214 Capacitance vs Volume")

# plt.plot(volume, fit_line, color="k", lw=2.5)

# text_x = .7  # x-coordinate
# text_y = .40494  # y-coordinate

# plt.text(text_x, text_y, equation, fontsize=10, color='red',
#          bbox={'facecolor': 'white', 'alpha': 0.7, 'edgecolor': 'gray'})


# plt.errorbar(volume, capacitor,
#              yerr = c_uncert_3_6,
#              fmt ='o')

# #plt.xticks(rotation = 25)
# plt.xlabel('Volume (mL)')
# plt.ylabel('Capacitance (pF)')
# plt.title('FDC2214 Experiment Readings', fontsize = 20)
# plt.grid()
# plt.legend()
# plt.show()

# implement all the graphs in one view: 

# plt.show()



# implement fsm switch graphs


# import pandas as pd










# df = pd.read_json('data.json')
# df.to_csv('data2.csv', index=False)



# with open('data_file.csv', newline='') as csvfile:
#     spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
#     print(spamreader["temperature_1"])

#     for row in spamreader:
#         print(row)
# #         # print(', '.join(row))


    
# x = []
# y = []

# with open('voltage.csv','r') as csvfile:
#     lines = csv.reader(csvfile, delimiter=',')
#     for row in lines:
#         print(row['temperature_1'])
#         x.append(row[0])
#         y.append(int(row[1]))

# plt.plot(x, y, color = 'g', linestyle = 'dashed',
#          marker = 'o',label = "Weather Data")

# plt.xticks(rotation = 25)
# plt.xlabel('Dates')
# plt.ylabel('Temperature(°C)')
# plt.title('Weather Report', fontsize = 20)
# plt.grid()
# plt.legend()
# plt.show()



# VOLTAGE_COLS = ["12VA_VA", "12VA_VB", "12VB_VA", "12VB_VB",
#                 "3V3_VA", "3V3_VB", "VBAT_VA", "VBAT_VB"]

# time_data = []
# voltages = {col: [] for col in VOLTAGE_COLS}




# with open(FILENAME, "r", newline="") as f:
#     reader = csv.DictReader(f)
#     for row in reader:
#         try:
#             t = float(row["timestamp"])
#             vals = {col: float(row[col]) for col in VOLTAGE_COLS}
#         except (ValueError, KeyError, TypeError):
#             continue  # skip blank or corrupted rows
#         time_data.append(t)
#         for col in VOLTAGE_COLS:
#             voltages[col].append(vals[col])

# fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(9, 7))

# ax1.plot(time_data, voltages["12VA_VA"], color='g', linestyle='dashed',
#          marker='o', label="12VA_VA")
# ax1.set_ylabel("Voltage (V)")
# ax1.set_title("12 V Rail", fontsize=14)
# ax1.grid()
# ax1.legend()

# ax2.plot(time_data, voltages["3V3_VA"], color='b', linestyle='dashed',
#          marker='s', label="3V3_VA")
# ax2.set_xlabel("Time (s)")
# ax2.set_ylabel("Voltage (V)")
# ax2.set_title("3.3 V Rail", fontsize=14)
# ax2.grid()
# ax2.legend()

# fig.tight_layout()
# plt.show()
