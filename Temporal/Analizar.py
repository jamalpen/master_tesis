import sys
import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

# File path and output prefix passed as arguments
file_path = sys.argv[1]
output_prefix = sys.argv[2]

# Initialize lists to store the data
x = []
y = []

# Read the file line by line
with open(file_path, 'r') as file:
    for line in file:
        # Skip header lines that start with #
        if line.startswith('#'):
            continue
        # Split the line into columns
        columns = line.split()
        # Extract the relevant columns (x and y)
        x.append(float(columns[4]))  # Column x is the 5th (index 4)
        y.append(float(columns[5]))  # Column y is the 6th (index 5)

# Convert lists to numpy arrays for easier handling
x = np.array(x)
y = np.array(y)

# Create the scatter plot
plt.figure(figsize=(10, 10))
plt.scatter(x, y, s=1, c='red', alpha=0.5)
plt.xlabel('X axis (cm)')
plt.ylabel('Y axis (cm)')
plt.title('Lateral distribution of particles at detector level')
plt.grid(True)
plt.axis('equal')
plt.savefig(f'{output_prefix}_particle_distribution.png')
plt.show()

# Create histograms
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.hist(x, bins=50, density=True, alpha=0.6, color='g')
plt.title('Histogram of x')
plt.xlabel('x (m)')
plt.ylabel('Density')

plt.subplot(1, 2, 2)
plt.hist(y, bins=50, density=True, alpha=0.6, color='b')
plt.title('Histogram of y')
plt.xlabel('y (m)')
plt.ylabel('Density')

plt.tight_layout()
plt.savefig(f'{output_prefix}_histograms.png')
plt.show()

# Q-Q plots
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
stats.probplot(x, dist="norm", plot=plt)
plt.title('Q-Q plot of x')

plt.subplot(1, 2, 2)
stats.probplot(y, dist="norm", plot=plt)
plt.title('Q-Q plot of y')

plt.tight_layout()
plt.savefig(f'{output_prefix}_qq_plots.png')
plt.show()

# K-S test for normality
#x_norm = (x - np.mean(x)) / np.std(x)
#y_norm = (y - np.mean(y)) / np.std(y)

#ks_stat_x, p_value_x = stats.kstest(x_norm, 'norm')
#ks_stat_y, p_value_y = stats.kstest(y_norm, 'norm')

#print(f'KS test for x: statistic = {ks_stat_x}, p-value = {p_value_x}')
#print(f'KS test for y: statistic = {ks_stat_y}, p-value = {p_value_y}')

# Create adjusted scatter plot
plt.figure(figsize=(10, 10))
plt.scatter(x, y, s=1, c='red', alpha=0.5)
plt.xlabel('X axis (m)')
plt.ylabel('Y axis (m)')
plt.title('Lateral distribution of particles at detector level')
plt.grid(True)
plt.xlim([-1e5, 1e5])  # Adjust as necessary
plt.ylim([-1e5, 1e5])  # Adjust as necessary
plt.axis('equal')
plt.savefig(f'{output_prefix}_adjusted_particle_distribution.png')
plt.show()

