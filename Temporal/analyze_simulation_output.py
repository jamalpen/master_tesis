import pandas as pd
import numpy as np

# Read the output.txt file
df = pd.read_csv('output.txt', sep='/', comment='#', header=None, engine='python')

# Rename the columns
df.columns = ['Time', 'Height', 'Distance', 'Theta', 'Simulation_Time', 'Selected_Particles']

# Group by the first four parameters
grouped = df.groupby(['Time', 'Height', 'Distance', 'Theta'])

# Create a list to store the results
results = []

for name, group in grouped:
	#print(f"Processing group: {name}")
	#print(group)

	sum_simulation_time = group['Simulation_Time'].sum()
	mean_selected_particles = group['Selected_Particles'].mean()
	std_selected_particles = group['Selected_Particles'].std()
	count_data_points = group['Selected_Particles'].count()

	# Format mean and std to 3 decimal places
	mean_selected_particles = round(mean_selected_particles,3)
	std_selected_particles = round(std_selected_particles, 3)

	# Add the results to a text file
	results.append(list(name) + [sum_simulation_time, mean_selected_particles, std_selected_particles, count_data_points])

# Create a DataFrame with the results
results_df = pd.DataFrame(results, columns=['Time', 'Height', 'Distance', 'Theta', 'Sum_Simulation_Time', 'Mean_Selected_Particles', 'Std_Selected_Particles', 'Count_Data_Points'])

# Print the results DataFrame to check the summarized data
print('Results DataFrame:')
print(results_df)

# Write the results to a text file
with open('output_summary.txt', 'w') as f:
	# Write the header
	f.write("Time/Height/Distance/Theta/Sum_Simulation_Time/Mean_Selected_Particles/Std_Selected_Particles/Count_Data_Points\n")
	for result in results:
		f.write('/'.join(map(str, result)) + '\n')
