import sys
import matplotlib.pyplot as plt

# Verify that the file argument is passed
if len(sys.argv) != 2:
    print("Usage: python3 saturation_finder.py output_summary.txt")
    sys.exit(1)

# File to read
file_name = sys.argv[1]

# Initialize lists to store the data
times = []
cv_flux = []

# Read the file and extract necessary data
with open(file_name, 'r') as file:
    for line in file:
        # Skip commented lines
        if line.startswith("#"):
            continue
        # Split the line into columns
        data = line.split('/')
        # Extract time (first column) and coefficient of variability (second to last column)
        time = float(data[0])
        cv = float(data[-2])
        
        times.append(time)
        cv_flux.append(cv)
        
# Plotting the data
plt.figure(figsize=(8, 6))
plt.plot(times, cv_flux, marker='o', linestyle='-', color='b')
plt.xlabel('Simulation Time (s)')
plt.ylabel('Coefficient of Variability (CV)')
plt.title('Coefficient of Variability vs Simulation Time')
plt.grid(True)
plt.savefig('variability_vs_time.png')
