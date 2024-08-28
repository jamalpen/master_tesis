import sys

def count_particles_in_area(shw_file, dist_x, dist_y, area_size):
    # Read the .shw file
    with open(shw_file, 'r') as file:
        lines = file.readlines()
    
    # Initialize counters
    particle_count_in_area = 0
    total_particle_count = 0
    
    # Define the original origin (0,0) for the data
    origin_x = 0
    origin_y = 0
    
    # Define the new origin based on the distance (dist) and convert to meters
    new_origin_x = origin_x - (dist_x * 1000)  # Convert distance_x from km to meters
    new_origin_y = origin_y - (dist_y * 1000)  # Convert distance_y from km to meters
    
    # Define the area of interest around the new origin
    area_half_size = area_size / 2  # Half the size of the area to simplify limit calculations
    
    # Process the lines of the file, skipping the header and the last line
    for line in lines[5:-1]:  # Skip the first 5 header lines and the last line
        data = line.split()
        
        try:
            x = float(data[4])
            y = float(data[5])
        except ValueError:
            continue
        
        # Count the particle
        total_particle_count += 1
        
        # Check if the particle is in the area of interest relative to the new origin
        if (new_origin_x - area_half_size <= x <= new_origin_x + area_half_size and
            new_origin_y - area_half_size <= y <= new_origin_y + area_half_size):
            particle_count_in_area += 1
            #print("Particle within the area of interest:")
            #print("x:", x, "y:", y)
    return particle_count_in_area, total_particle_count

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: python count_particles.py <file.shw> <dist_x> <dist_y> <area_size>")
        sys.exit(1)
    
    shw_file = sys.argv[1]
    dist_x = float(sys.argv[2])
    dist_y = float(sys.argv[3])
    area_size = float(sys.argv[4])
    
    particle_count_in_area, total_particle_count = count_particles_in_area(shw_file, dist_x, dist_y, area_size)
    print(particle_count_in_area)


