#!/bin/bash

# Config
BINARY="./bin/RTLBenchmarkApp"
LOGFILE="./benchmark_runs.log"

# Clear old log file
: > "$LOGFILE"

echo "Starting benchmark runs..." | tee -a "$LOGFILE"
echo "Binary: $BINARY" | tee -a "$LOGFILE"
echo "Log: $LOGFILE" | tee -a "$LOGFILE"
echo "===================================" | tee -a "$LOGFILE"

# First handle scale=0, 10 times
SCALE=0
for i in $(seq 1 10); do
    echo ">>> Run $i: workload scale = $SCALE" | tee -a "$LOGFILE"
    "$BINARY" "$SCALE" >> "$LOGFILE" 2>&1
    echo "-----------------------------------" | tee -a "$LOGFILE"
done

# Now handle scales 25, 50, ... 200, each 5 times
for SCALE in $(seq 25 25 200); do
    for i in $(seq 1 5); do
        echo ">>> Run $i: workload scale = $SCALE" | tee -a "$LOGFILE"
        "$BINARY" "$SCALE" >> "$LOGFILE" 2>&1
        echo "-----------------------------------" | tee -a "$LOGFILE"
    done
done

echo "All benchmarks completed." | tee -a "$LOGFILE"
