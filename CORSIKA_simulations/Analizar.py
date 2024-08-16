import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# File path and output prefix passed as arguments
file_path = sys.argv[1]
output_prefix = sys.argv[2]
dist = float(sys.argv[3])
area_size = float(sys.argv[4])

# Initialize lists to store the data
x = []
y = []
z = []

# Read the file line by line
with open(file_path, 'r') as file:
    for line in file:
        # Skip header lines that start with #
        if line.startswith('#'):
            continue
        # Split the line into columns
        columns = line.split()
        # Extract the relevant columns (x, y, and z)
        x.append(float(columns[4]))  # Column x is the 5th (index 4)
        y.append(float(columns[5]))  # Column y is the 6th (index 5)
        z.append(float(columns[6]))  # Column z is the 7th (index 6)

# Convert lists to numpy arrays for easier handling
x = np.array(x)
y = np.array(y)
z = np.array(z)

# Determine the min and max values for x, y, and z
x_min, x_max = x.min(), x.max()
y_min, y_max = y.min(), y.max()
z_min, z_max = z.min(), z.max()

# Print the min and max values for verification
print(f'X min: {x_min}, X max: {x_max}')
print(f'Y min: {y_min}, Y max: {y_max}')
print(f'Z min: {z_min}, Z max: {z_max}')

# Calculate the histogram of z
num_bins_for_z = 300
z_hist, z_bins = np.histogram(z, bins=num_bins_for_z, density=False)
# To improve the resolution of the histogram, increase the number of bins to have finer bins.
# Calculate the bin width
z_bin_width = (z_max - z_min) / num_bins_for_z
print(f'Bin width of z: {z_bin_width}')
z_bin_centers = 0.5 * (z_bins[:-1] + z_bins[1:])
max_z_bin = z_bin_centers[np.argmax(z_hist)]
print(f'Value of z with highest concentration: {max_z_bin}')

# Create the scatter plot
plt.figure(figsize=(10, 10))
plt.scatter(x, y, s=5, c='red', alpha=0.5)
plt.xlabel('X axis (m)')
plt.ylabel('Y axis (m)')
plt.title('Lateral distribution of particles at detector level')
plt.grid(True)
plt.axis([x_min, x_max, y_min, y_max])
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
plt.xlim(x_min, x_max)

plt.subplot(1, 2, 2)
plt.hist(y, bins=50, density=True, alpha=0.6, color='b')
plt.title('Histogram of y')
plt.xlabel('y (m)')
plt.ylabel('Density')
plt.xlim(y_min, y_max)

plt.tight_layout()
plt.savefig(f'{output_prefix}_histograms.png')
plt.show()

# Create histogram for z
plt.figure(figsize=(20, 10))
plt.hist(z, bins=num_bins_for_z, density=False, alpha=0.6, color='purple')
# Change density to True if you want the probability density instead of selected particles
plt.title('Histogram of z')
plt.xlabel('z (m)')
plt.ylabel('Count')
plt.axvline(max_z_bin, color='r', linestyle='dashed', linewidth=1)
plt.text(max_z_bin, max(z_hist) * 0.9, f'Mode: {max_z_bin:.2f}', color='r')
plt.xlim(z_min, z_max * 1.1) # Extend the x limit by 10 % of z_max
plt.savefig(f'{output_prefix}_histogram_z.png')
plt.show()

# Create a 3D scatter plot for x, y, z
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, s=5, c='red', alpha=0.5)
ax.set_xlabel('X axis (m)')
ax.set_ylabel('Y axis (m)')
ax.set_zlabel('Z axis (m)')
ax.set_title('3D Scatter Plot of Particles')
ax.set_xlim([x_min, x_max])
ax.set_ylim([y_min, y_max])
ax.set_zlim([z_min, z_max])
plt.savefig(f'{output_prefix}_3D_scatter.png')
plt.show()

# Define the area of interest around the new origin
origin_x = 0
origin_y = 0
new_origin_x = origin_x - (dist * 1000)  # Convert distance from km to meters
new_origin_y = origin_y
area_half_size = area_size / 2

# Filter particles within the area of interest
within_area = (new_origin_x - area_half_size <= x) & (x <= new_origin_x + area_half_size) & (new_origin_y - area_half_size <= y) & (y <= new_origin_y + area_half_size)
x_within = x[within_area]
y_within = y[within_area]

# Count the number of particles within the area of interest
particles_in_area = len(x_within)
print(f'Number of particles in the area of interest: {particles_in_area}')

# Create the scatter plot for the area of interest
plt.figure(figsize=(10, 10))
plt.scatter(x_within, y_within, s=5, c='blue', alpha=0.5)
# s parameter is to have a bigger point in blue
plt.xlabel('X axis (m)')
plt.ylabel('Y axis (m)')
plt.title(f'Particle distribution in the area of interest\nNumber of particles: {particles_in_area}')
plt.grid(True)
plt.axis([new_origin_x - area_half_size, new_origin_x + area_half_size, new_origin_y - area_half_size, new_origin_y + area_half_size])
plt.axis('equal')
plt.savefig(f'{output_prefix}_area_distribution.png')
plt.show()
