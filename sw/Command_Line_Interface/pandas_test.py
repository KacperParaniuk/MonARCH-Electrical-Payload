import pandas as pd 

df = pd.read_json('data.json', orient='values')
df.to_csv('data2.csv', index=False)