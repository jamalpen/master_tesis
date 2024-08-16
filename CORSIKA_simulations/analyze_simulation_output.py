import pandas as pd
import numpy as np

# Read the output.txt file
df = pd.read_csv('output.txt', sep='/', comment='#', header=None, engine='python')

# Name the columns
df.columns = ['Time', 'Height', 'Distance', 'Theta', 'Thetamax', 'Simulation_Time', 'Selected_Particles', 'Particles_At_Detector', 'Flux_At_Detector']

# Group by the first five parameters
grouped = df.groupby(['Time', 'Height', 'Distance', 'Theta', 'Thetamax'])

# Create a list to store the results
results = []

for name, group in grouped:
    # Calculate sum of simulation time, mean and std of flux at detector, and count of data points
    sum_simulation_time = group['Simulation_Time'].sum()
    mean_flux_at_detector = group['Flux_At_Detector'].mean()
    std_flux_at_detector = group['Flux_At_Detector'].std()
    mean_particles_at_detector = group['Particles_At_Detector'].mean()
    std_particles_at_detector = group['Particles_At_Detector'].std()
    count_data_points = group['Flux_At_Detector'].count()

    # Format mean and std to 3 decimal places
    mean_flux_at_detector = round(mean_flux_at_detector, 10)
    std_flux_at_detector = round(std_flux_at_detector, 10)
    mean_particles_at_detector = round(mean_particles_at_detector, 10)
    std_particles_at_detector = round(std_particles_at_detector, 10)

    # Calculate the coefficient of variability
    cv_flux_at_detector = std_flux_at_detector / mean_flux_at_detector if mean_flux_at_detector != 0 else 0
    cv_flux_at_detector = round(cv_flux_at_detector, 10)

    # Add the results to a text file
    results.append(list(name) + [sum_simulation_time, mean_flux_at_detector, std_flux_at_detector, mean_particles_at_detector, std_particles_at_detector, cv_flux_at_detector, count_data_points])

# Create a DataFrame with the results
results_df = pd.DataFrame(results, columns=['Time', 'Height', 'Distance', 'Theta', 'Thetamax', 'Sum_Simulation_Time', 'Mean_Flux', 'Std_Flux', 'Mean_Particles', 'Std_Particles', 'CV_Flux', 'Count_Data_Points'])

# Change column names for display and output purposes
display_df = results_df.rename(columns={'Theta': 'Low_Theta', 'Thetamax': 'High_Theta'})

# Print the results DataFrame to check the summarized data
print('Results DataFrame:')
print(display_df)

# Write the results to a text file
with open('output_summary.txt', 'w') as f:
    # Write the header
    f.write("#Time/Height/Distance/Low_Theta/High_Theta/Sum_Simulation_Time/Mean_Flux/Std_Flux/Mean_Particles/Std_Particles/CV_Flux/Count_Data_Points\n")
    for result in display_df.itertuples(index=False, name=None):
        f.write('/'.join(map(str, result)) + '\n')
