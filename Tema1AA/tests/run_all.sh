#!/bin/bash

EXEC="../src/steiner_solver"

if [ ! -f "$EXEC" ]; then
    echo "Eroare: Nu gasesc executabilul '$EXEC'. Ai dat 'make' in folderul src?"
    exit 1
fi

echo "==============================================================================="
echo " BENCHMARK STEINER TREE (Cu Eroare Relativa)"
echo "==============================================================================="
# Capul de tabel actualizat
printf "%-20s | %-10s | %-6s | %-10s | %s\n" "TEST FILE" "ALGORITM" "COST" "TIMP (s)" "EROARE"
echo "-------------------------------------------------------------------------------"

for testfile in in/*.txt; do
    filename=$(basename "$testfile")
    
    # Acum citim 4 variabile: algo, cost, time, error
    $EXEC < "$testfile" | while IFS=, read -r algo cost time error; do
        # Formatam outputul
        printf "%-20s | %-10s | %-6s | %-10s | %s\n" "$filename" "$algo" "$cost" "$time" "$error"
    done
    
    echo "-------------------------------------------------------------------------------"
done