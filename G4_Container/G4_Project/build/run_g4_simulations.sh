#!/bin/bash

# Number of times to repeat the simulation
n=6

# Loop to run the simulation n times
for i in $(seq 1 $n); do
  echo "Running simulation iteration $i"
  ./sim -m input.in -t 1
done
