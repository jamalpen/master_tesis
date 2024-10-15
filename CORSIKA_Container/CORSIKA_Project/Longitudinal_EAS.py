import glob
import re
import numpy as np
import matplotlib.pyplot as plt

# Pattern to match your files
filenames = glob.glob("0-90deg_002000_*.shw")

observation_levels = []  # x-axis data
number_of_particles = []  # y-axis data

for filename in filenames:
    with open(filename, 'r') as file:
        lines = file.readlines()

        # Ensure there are enough lines in the file
        if len(lines) < 2:
            print(f"File {filename} does not have enough lines.")
            continue

        # Extract the second line
        second_line = lines[1].strip()

        # Extract observation level using regex
        obs_match = re.search(r'observation level is (\d+\.?\d*) m a\.s\.l\.', second_line)
        if obs_match:
            obs_level = float(obs_match.group(1))
        else:
            print(f"Could not find observation level in {filename}.")
            continue

        # Extract the last line
        last_line = lines[-1].strip()

        # Extract number of particles using regex
        particles_match = re.search(r'particles:\s*(\d+)', last_line)
        if particles_match:
            particles = int(particles_match.group(1))
        else:
            print(f"Could not find number of particles in {filename}.")
            continue

        # Append the extracted data to the lists
        observation_levels.append(obs_level)
        number_of_particles.append(particles)
        
# Check if data was collected
if not observation_levels or not number_of_particles:
    print("No data collected to plot.")
else:
    # Sort the data based on observation levels
    sorted_data = sorted(zip(observation_levels, number_of_particles))
    sorted_observation_levels, sorted_number_of_particles = zip(*sorted_data)

    # Plot the graph
    plt.figure(figsize=(10, 6))
    plt.plot(sorted_observation_levels, sorted_number_of_particles, marker='o', linestyle='-')
    plt.title('Number of Particles vs. Observation Level')
    plt.xlabel('Observation Level (m a.s.l.)')
    plt.ylabel('Number of Particles')
    plt.grid(True)
    #plt.show()
    plt.savefig('particles_vs_observation_level.png')
    plt.close()
    
    
