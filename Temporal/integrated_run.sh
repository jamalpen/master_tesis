#!/bin/bash

# Path to the base directory
base_dir="/opt/arti"

# Data file
data_file="/opt/datos.txt"

# Directory of CORSIKA
corsika_dir="/opt/corsika-77402/run"

# Output file for timings and logs
output_file="/opt/output.txt"

# Column separator
IFS=$'\t'

# Path to the python script
python_script="/opt/Analizar.py"

do_sims="/opt/arti/sims/do_sims.sh"
do_showers="/opt/arti/analysis/do_showers.sh"

# Cleanup script file
cleanup_dir="/opt/cleanup_simulation_data.sh"

# Write the header to the output file only if it doesn't already exist
if [ ! -f "$output_file" ]; then
    echo "#Time/height/distance/theta/simulation_time/selected_particles" > "$output_file"
fi

tail -n +2 "$data_file" | while read -r time height dist theta; do
    # Check if all variables are set (non-empty)
    if [ -z "$time" ] || [ -z "$height" ] || [ -z "$dist" ] || [ -z "$theta" ]; then
        echo "Warning: Skipping incomplete line in $data_file"
        continue
    fi

    # Record the start time
    start_time=$(date +%s)

    # Run do_sims.sh using a here document to automate the input
    cd "$base_dir"
    if [ "$theta" -eq 0 ]; then
        $do_sims -w "$corsika_dir" -p "${theta}-90deg" -s quie -v 77402 -t "$time" -m "$theta" -n 90 -i 10000 -b -1 -y <<EOF
0
EOF
    else
        $do_sims -w "$corsika_dir" -p "${theta}-90deg" -s quie -v 77402 -t "$time" -m "$theta" -n 90 -i 10000 -b -1 -y
    fi
    sleep 7

    # Run restriccion_polar.sh
    cd "$corsika_dir"
    if [ ${#time} -eq 3 ]; then
        ./restriccion_polar.sh -d "${theta}-90deg_000${time}/" -m -90 -n 90
    elif [ ${#time} -eq 4 ]; then
        ./restriccion_polar.sh -d "${theta}-90deg_00${time}/" -m -90 -n 90
    else
        echo "Error: incorrect time format."
        exit 1
    fi
    sleep 15

    # Run rungo.sh
    if [ ${#time} -eq 3 ]; then
        ./rungo.sh "${theta}-90deg_000${time}"
    else
        ./rungo.sh "${theta}-90deg_00${time}"
    fi

    # Wait for previous processes to finish
    while pgrep -x "corsika77402Lin" || pgrep -x "bzip2"; do
        sleep 35
    done

    # Run do_showers.sh
    cd "$base_dir"
    if [ ${#time} -eq 3 ]; then
        $do_showers -o "$corsika_dir/${theta}-90deg_000${time}/" -k "${height}" -t "$time" -l
    elif [ ${#time} -eq 4 ]; then
        $do_showers -o "$corsika_dir/${theta}-90deg_00${time}/" -k "${height}" -t "$time" -l
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
        sim_dir="/opt/arti/${theta}-90deg_000${time}"
        bz2_file="${theta}-90deg_000${time}.shw.bz2"
    else
        sim_dir="/opt/arti/${theta}-90deg_00${time}"
        bz2_file="${theta}-90deg_00${time}.shw.bz2"
    fi
    sleep 40

    cd "$sim_dir"
    bzip2 -d "$bz2_file" # Decompress the file


    # Extract the number of selected particles from the last line of the decompressed file
    shw_file="${bz2_file%.bz2}"
    last_line=$(tail -n 1 "$shw_file")
    selected_particles=$(echo "$last_line" | grep -oP '(?<=Selected particles: )\d+')
    echo "Selected particles: ${selected_particles}"
    sleep 60

    # Run the Python script with the decompressed file as an argument
    python3 "$python_script" "$shw_file" "selected_particles_${selected_particles}"
    sleep 40

    # Check if the Python script executed successfully
    if [ $? -ne 0 ]; then
        echo "Error: Python script failed."
        exit 1
    fi

    # Create the analysis directory in /opt
    analysis_dir="/opt/analisis"
    mkdir -p "$analysis_dir"

    # Copy the generated files if they exist
    pattern="${sim_dir}/selected_particles_${selected_particles}_*.png"
    echo "Pattern: $pattern"
    sleep 40

    files=($pattern)
    echo "${files[@]}"
    if [ ${#files[@]} -gt 0 ]; then
        for file in "${files[@]}"; do
            cp "${files[@]}" "$analysis_dir"
        done
    else
        echo "Warning: No files to move for selected_particles_${selected_particles}"
    fi
    sleep 40

    # Run cleanup.sh
    #"$cleanup_dir" "${theta}" "${time}"
    #sleep 40

    # Record the end time
    end_time=$(date +%s)

    # Calculate the elapsed time 
    elapsed_time=$((end_time - start_time))

    # Append the data to the output file
    echo "${time}/${height}/${dist}/${theta}/${elapsed_time}/${selected_particles}" >> "$output_file"

    sleep 30
done
