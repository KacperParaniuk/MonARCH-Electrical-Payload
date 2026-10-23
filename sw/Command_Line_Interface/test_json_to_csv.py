import json
import csv 

# JSON to CSV code. 

with open ('data.json') as jf:
    data = json.load(jf)


Ed = data[ 'value' ] # get one packet out of all the packets in the .json file. 

df = open('data_file.csv', 'w')

cw = csv.writer(df)

# Writing headers of CSV file
h = Ed.keys()
cw.writerow(h)

# Writing data of CSV file
cw.writerow(Ed.values())

df.close()

