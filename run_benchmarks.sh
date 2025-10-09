#!/bin/bash

# ===========================
# RTL Benchmark Runner Script
# ===========================

BINARY="./bin/RTLBenchmarkApp"
LOGFILE="./benchmark_runs.log"

# Clear old log file
: > "$LOGFILE"

echo "Starting benchmark runs..." | tee -a "$LOGFILE"
echo "Binary: $BINARY" | tee -a "$LOGFILE"
echo "Log: $LOGFILE" | tee -a "$LOGFILE"
echo "===================================" | tee -a "$LOGFILE"

# Helper: run workload N times
run_benchmark() {
    local scale=$1
    local reps=$2
    for i in $(seq 1 "$reps"); do
        echo "[$(date '+%Y-%m-%d %H:%M:%S')] >>> Run $i: workload scale = $scale" | tee -a "$LOGFILE"
        if ! "$BINARY" "$scale" >> "$LOGFILE" 2>&1; then
            echo "[ERROR] Binary failed at scale=$scale (run $i)" | tee -a "$LOGFILE"
        fi
        echo "-----------------------------------" | tee -a "$LOGFILE"
    done
}

# ---------------------------
# Phase 1: Baseline runs (scale 0, 10 reps)
# ---------------------------
run_benchmark 0 10

# ---------------------------
# Phase 2: Scales 1 → 50
# ---------------------------
SCALES_PHASE2=(1 5 10 15 20 25 30 35 40 45 50)
for SCALE in "${SCALES_PHASE2[@]}"; do
    run_benchmark "$SCALE" 5
done

# ---------------------------
# Phase 3: Scales 58 → 90 (step 8)
# ---------------------------
for SCALE in $(seq 58 8 90); do
    run_benchmark "$SCALE" 5
done

# ---------------------------
# Phase 4: Final higher scales
# ---------------------------
for SCALE in 100 120 150; do
    run_benchmark "$SCALE" 5
done

echo "All benchmarks completed." | tee -a "$LOGFILE"
