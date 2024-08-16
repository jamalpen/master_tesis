#!/bin/bash

# Change to the /opt/corsika-77402/run directory
cd /opt/corsika-77402/run || { echo "Error: cannot change to the /opt/corsika-77402/run directory"; exit 1; }

# Check if the necessary arguments are provided
if [ $# -lt 3 ]; then
    echo "Usage: $0 <theta> <thetamax> <time>"
    exit 1
fi

# Take the arguments as theta, thetamax and time
theta=$1
thetamax=$2
time=$3


# Determine the pattern for files and folders based on the length of 'time'
if [ ${#time} -eq 3 ]; then
    file_pattern="go-${theta}-${thetamax}deg_000${time}-*"
    folder_pattern="${theta}-${thetamax}deg_000${time}"
elif [ ${#time} -eq 4 ]; then
    file_pattern="go-${theta}-${thetamax}deg_00${time}-*"
    folder_pattern="${theta}-${thetamax}deg_00${time}"
else
    echo "Error: The value of 'time' must be 3 or 4 digits."
    exit 1
fi

# Show the pattern that will be used for deletion
echo "File pattern used: '${file_pattern}'"
echo "Folder pattern used: '${folder_pattern}'"

# Find and delete all files matching the specified pattern
find . -type f -name "${file_pattern}" -exec rm -v {} \;

# Find and delete the folder matching the specified pattern
find . -type d -name "${folder_pattern}" -exec rm -rv {} \;

echo "All files starting with '${file_pattern}' and the folder '${folder_pattern}' have been deleted."

# Change to the /opt/arti directory
cd /opt/arti || { echo "Error: cannot change to the /opt/arti directory"; exit 1; }

# Find and delete the folder matching the specified pattern in /opt/arti
if [ -d "${folder_pattern}" ]; then
    rm -rv "${folder_pattern}"
    echo "The folder '${folder_pattern}' in /opt/arti has been deleted."
else
    echo "The folder '${folder_pattern}' does not exist in /opt/arti."
fi

# Do not forget to execute this script as follows:
# ./cleanup.sh 45 700 where the first parameter is the angle and the second is the time
# Also, this script must always be located and executed in /opt/corsika-77402/run/
