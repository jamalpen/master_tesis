#!/bin/bash

# Path to the base directory
base_dir="/opt/arti"

# Data file
data_file="/home/datos.txt"

# Directory of CORSIKA
corsika_dir="/opt/corsika-77402/run"

# Output file for timings and logs
output_file="/home/output.txt"

# Column separator
IFS=$'\t'

# Path to the python script
python_script="/home/Analyzer.py"
count_particles_script="/home/count_particle.py"

# Path to the tools of ARTI
do_sims="/opt/arti/sims/do_sims.sh"
do_showers="/opt/arti/analysis/do_showers.sh"

# Cleanup script file
cleanup_dir="/home/cleanup_simulation_data.sh"

# Define the area size
area_size=1000

# The directory where integrated_run.sh is located is in /home.

# Write the header to the output file only if it doesn't already exist
if [ ! -f "$output_file" ]; then
    echo "#Time/height/distance/theta/thetamax/simulation_time/selected_particles/particles_at_detector/flux_at_detector" > "$output_file"
fi

tail -n +2 "$data_file" | while read -r time height dist theta thetamax; do
    # Check if all variables are set (non-empty)
    if [ -z "$time" ] || [ -z "$height" ] || [ -z "$dist" ] || [ -z "$theta" ] || [ -z "$thetamax" ]; then
        echo "Warning: Skipping incomplete line in $data_file"
        continue
    fi

    # Record the start time
    start_time=$(date +%s)

    # Run do_sims.sh using a here document to automate the input
    cd "$base_dir"
    if [ "$theta" -eq 0 ]; then
        $do_sims -w "$corsika_dir" -p "${theta}-${thetamax}deg" -s quie -v 77402 -t "$time" -m "$theta" -n "$thetamax" -i 10000 -b -1 -y <<EOF
0
EOF
    else
        $do_sims -w "$corsika_dir" -p "${theta}-${thetamax}deg" -s quie -v 77402 -t "$time" -m "$theta" -n "$thetamax" -i 10000 -b -1 -y
    fi
    sleep 7

    # Run polar_condition.sh
    cd "$corsika_dir"
    if [ ${#time} -eq 3 ]; then
        ./polar_condition.sh -d "${theta}-${thetamax}deg_000${time}/" -m -90 -n 90
    elif [ ${#time} -eq 4 ]; then
        ./polar_condition.sh -d "${theta}-${thetamax}deg_00${time}/" -m -90 -n 90
    else
        echo "Error: incorrect time format."
        exit 1
    fi
    sleep 15

    # Run rungo.sh
    if [ ${#time} -eq 3 ]; then
        ./rungo.sh "${theta}-${thetamax}deg_000${time}"
    else
        ./rungo.sh "${theta}-${thetamax}deg_00${time}"
    fi

    # Wait for previous processes to finish
    while pgrep -x "corsika77402Lin" || pgrep -x "bzip2"; do
        sleep 35
    done

    # Run do_showers.sh
    cd "$base_dir"
    if [ ${#time} -eq 3 ]; then
        $do_showers -o "$corsika_dir/${theta}-${thetamax}deg_000${time}/" -k "${height}" -t "$time" -l
    elif [ ${#time} -eq 4 ]; then
        $do_showers -o "$corsika_dir/${theta}-${thetamax}deg_00${time}/" -k "${height}" -t "$time" -l
    else
        echo "Error: incorrect time format."
        exit 1
    fi

    # Wait for previous processes to finish
    while pgrep -x "lagocrkread" || pgrep -x "bzip2" || pgrep -x "analysis"; do
	echo "Waiting for lagocrkread, bzip2, or analysis processes to finish..."
        sleep 60 # Pause for 60 seconds and recheck if processes are still running
    done

    # Change to the appropriate directory and decompress the file
    if [ ${#time} -eq 3 ]; then
        sim_dir="/opt/arti/${theta}-${thetamax}deg_000${time}"
        bz2_file="${theta}-${thetamax}deg_000${time}.shw.bz2"
    elif [ ${#time} -eq 4 ]; then
        sim_dir="/opt/arti/${theta}-${thetamax}deg_00${time}"
        bz2_file="${theta}-${thetamax}deg_00${time}.shw.bz2"
    fi
    sleep 5

    cd "$sim_dir"
    bzip2 -d "$bz2_file" # Decompress the file
    sleep 10

    # Extract the number of selected particles from the last line of the decompressed file
    shw_file="${bz2_file%.bz2}"
    last_line=$(tail -n 1 "$shw_file")
    selected_particles=$(echo "$last_line" | grep -oP '(?<=Selected particles: )\d+')
    echo "Selected particles: ${selected_particles}"
    sleep 5

    # Verify if the .shw file exists before copying
    if [ ${#time} -eq 3 ]; then
        shw_filepath="${sim_dir}/${theta}-${thetamax}deg_000${time}.shw"
        dst_filepath="${sim_dir}/${theta}-${thetamax}deg_000${time}.dst"
    elif [ ${#time} -eq 4 ]; then
        shw_filepath="${sim_dir}/${theta}-${thetamax}deg_00${time}.shw"
        dst_filepath="${sim_dir}/${theta}-${thetamax}deg_00${time}.dst"
    fi

    # Create the results directory in /home
    result_dir="/home/results"
    mkdir -p "$result_dir"

    if [ -f "$shw_filepath" ]; then
        cp "$shw_filepath" "$result_dir"
    else
        echo "Warning: ${shw_filepath} does not exist."
    fi

    if [ -f "$dst_filepath" ]; then
        cp "$dst_filepath" "$result_dir"
    else
        echo "Warning: ${dst_filepath} does not exist."
    fi

    # Rename the files in the results directory
    cd "$result_dir"
    if [ ${#time} -eq 3 ]; then
        if [ -f "${theta}-${thetamax}deg_000${time}.shw" ]; then
            mv "${theta}-${thetamax}deg_000${time}.shw" "${theta}-${thetamax}deg_000${time}_${selected_particles}.shw"
        fi
        if [ -f "${theta}-${thetamax}deg_000${time}.dst" ]; then
            mv "${theta}-${thetamax}deg_000${time}.dst" "${theta}-${thetamax}deg_000${time}_${selected_particles}.dst"
        fi
    elif [ ${#time} -eq 4 ]; then
        if [ -f "${theta}-${thetamax}deg_00${time}.shw" ]; then
            mv "${theta}-${thetamax}deg_00${time}.shw" "${theta}-${thetamax}deg_00${time}_${selected_particles}.shw"
        fi
        if [ -f "${theta}-${thetamax}deg_00${time}.dst" ]; then
            mv "${theta}-${thetamax}deg_00${time}.dst" "${theta}-${thetamax}deg_00${time}_${selected_particles}.dst"
        fi
    fi

    # Run the Python script with the decompressed file as an argument
    cd "$sim_dir"
    python3 "$python_script" "$shw_file" "${theta}-${thetamax}deg_${time}_${selected_particles}" "$dist" "$area_size"
    sleep 15

    # Check if the Python script executed successfully
    if [ $? -ne 0 ]; then
        echo "Error: Python script failed."
        exit 1
    fi

    # Create the analysis directory in /home
    analysis_dir="/home/analisis"
    mkdir -p "$analysis_dir"

    # Copy the generated files if they exist
    pattern="${sim_dir}/${theta}-${thetamax}deg_${time}_${selected_particles}_*.png"
    echo "Pattern: $pattern"
    sleep 10

    files=($pattern)
    echo "${files[@]}"
    if [ ${#files[@]} -gt 0 ]; then
        for file in "${files[@]}"; do
            cp "${files[@]}" "$analysis_dir"
        done
    else
        echo "Warning: No files to move for ${theta}-${thetamax}deg_${time}_${selected_particles}"
    fi
    sleep 10

    # Run the count_particles.py script and capture its output
    particles_at_detector=$(python3 "$count_particles_script" "$shw_filepath" "$dist" "$area_size" | head -n 1)
    # head is to get the first output of the python script. In this case, the first output is particle_count_in_area. Check the python script.

    # Calculate flux at detector
    flux_at_detector=$(echo "scale=10; $particles_at_detector / ($area_size * $time)" | bc -l) # bc is needed to be installed
    sleep 10

    # Record the end time
    end_time=$(date +%s)

    # Calculate the elapsed time
    elapsed_time=$((end_time - start_time))

    # Append the data to the output file
    echo "${time}/${height}/${dist}/${theta}/${thetamax}/${elapsed_time}/${selected_particles}/${particles_at_detector}/${flux_at_detector}" >> "$output_file"
    sleep 5

    # Run cleanup.sh
    "$cleanup_dir" "${theta}" "${thetamax}" "${time}"
    sleep 30
done
