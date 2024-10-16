#!/bin/bash

widths=(0.015 0.05 0.1)
alpha_true_values=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.27 0.29 0.31 0.33 0.42)
types=('NOMINAL' 'JESup' 'JESdown' 'JERup')

for element1 in "${widths[@]}"
do
    for element2 in "${alpha_true_values[@]}"
    do
        for element3 in "${types[@]}"
        do
            
            width=$element1
            alpha_true=$element2
            type=$element3

            root -l -q -b -x "create_input_histos_for_interpolation.C($width, $alpha_true, (char*)\"$type\")"
            
        done
    done
done
