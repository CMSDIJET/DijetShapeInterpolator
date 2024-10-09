#!/bin/bash

widths=(0.0043 0.015 0.05 0.1)
alpha_true_values=(0.25)
Suu_masses=(8400)
alpha_bins=(0 1 2 3 4 5 6 7 8 9 10 11 12 13)

for element1 in "${widths[@]}"
do
    for element2 in "${alpha_true_values[@]}"
    do
        for element3 in "${Suu_masses[@]}"
        do
            for element4 in "${alpha_bins[@]}"
            do

                width=$element1
                alpha_true=$element2
                Suu=$element3
                alpha_bin=$element4

                root -l -q -b -x "plot_simulated_vs_interpolated.C($width, $alpha_true, $Suu, $alpha_bin)"
            done
        done
    done
done
