#!/bin/bash

# ./run_extractShapes.sh 

alpha_true_values=(0.25)
widths=('0p015' '0p05' '0p1')
types=('NOMINAL' 'JESup' 'JESdown' 'JERup')

for element1 in "${alpha_true_values[@]}"
do
   for element2 in "${widths[@]}"
   do
   
      for element3 in "${types[@]}"
      do

         alpha_true=$element1
         width=$element2
         type=$element3

         alphap=$(echo "scale=0; ($alpha_true*100)/1" | bc  ) 

         echo "Performing interpolation for alpha true = "$alpha_true" (0p"$alphap"), width = "$width" and type = "$type""


         echo "Doing inclusive case (alpha>0.1) "

         ./extractShapes.py -i /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha0p"$alphap"/InputShapes_"$type"_alpha0p"$alphap"_W-"$width"_alphagt0p1.root > /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha0p"$alphap"/input_shapes_"$type"_alpha0p"$alphap"_W-"$width"_alphagt0p1.py


         for ibin in {1..13}
         do

            echo "Doing alpha bin "$ibin" "
         
            ./extractShapes.py -i /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha0p"$alphap"/InputShapes_"$type"_alpha0p"$alphap"_W-"$width"_alphabin"$ibin".root > /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/interpolation/inputs/alpha0p"$alphap"/input_shapes_"$type"_alpha0p"$alphap"_W-"$width"_alphabin"$ibin".py

         done

      done
   done
done
