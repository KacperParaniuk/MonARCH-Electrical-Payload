import numpy as np
import matplotlib.pyplot as plt
import csv

FILENAME = "voltage.csv"

VOLTAGE_COLS = ["12VA_VA", "12VA_VB", "12VB_VA", "12VB_VB",
                "3V3_VA", "3V3_VB", "VBAT_VA", "VBAT_VB"]

# Font sizes (matched to the pressure script)
TITLE_SIZE = 40
LABEL_SIZE = 30
TICK_SIZE = 20
LEGEND_SIZE = 25

time_data = []
voltages = {col: [] for col in VOLTAGE_COLS}

with open(FILENAME, "r", newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        try:
            t = float(row["timestamp"])
            vals = {col: float(row[col]) for col in VOLTAGE_COLS}
        except (ValueError, KeyError, TypeError):
            continue  # skip blank or corrupted rows
        time_data.append(t)
        for col in VOLTAGE_COLS:
            voltages[col].append(vals[col])

# Larger figure so the bigger fonts fit
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(18, 14))

# --- 12 V rail ---
ax1.plot(time_data, voltages["12VA_VA"], color='g', linestyle='dashed',
         marker='o', label="12VA_VA")
ax1.set_ylabel("Voltage (V)", fontsize=LABEL_SIZE)
ax1.set_title("12 V Rail", fontsize=TITLE_SIZE)
ax1.tick_params(axis='both', labelsize=TICK_SIZE)
ax1.grid()
ax1.legend(prop={'size': LEGEND_SIZE})

# --- 3.3 V rail ---
ax2.plot(time_data, voltages["3V3_VA"], color='b', linestyle='dashed',
         marker='s', label="3V3_VA")

ax2.axhline(0, color='k', linestyle='--', linewidth=1, label='Ground (0 V)')

ax2.set_xlabel("Time (s)", fontsize=LABEL_SIZE)
ax2.set_ylabel("Voltage (V)", fontsize=LABEL_SIZE)
ax2.set_title("3.3 V Rail", fontsize=TITLE_SIZE)
ax2.tick_params(axis='both', labelsize=TICK_SIZE)
ax2.grid()
ax2.legend(prop={'size': LEGEND_SIZE})

fig.tight_layout()
fig.savefig("voltage_plot.png", dpi=200, bbox_inches="tight")
plt.show()