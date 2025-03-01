# DijetShapeInterpolator

## Relevant presentations

```
[https://indico.cern.ch/event/1423346/contributions/5991064/attachments/2870675/5025746/2024_06_04_DijetAnalysisMeeting_WideResonances_Interpolation_JES_JER_syst.pdf]([https://example.com](https://indico.cern.ch/event/1423346/contributions/5991064/attachments/2870675/5025746/2024_06_04_DijetAnalysisMeeting_WideResonances_Interpolation_JES_JER_syst.pdf))

[https://indico.cern.ch/event/1083909/contributions/4557836/attachments/2322649/3955487/Interpolation_RPV_nonres_05_10_2021.pdf]{https://indico.cern.ch/event/1083909/contributions/4557836/attachments/2322649/3955487/Interpolation_RPV_nonres_05_10_2021.pdf}

```

## Setup instructions

```
cmsrel CMSSW_14_1_0_pre4
cd CMSSW_14_1_0_pre4/src
cmsenv

git clone -b PairedDijetAnalysis https://github.com/CMSDIJET/DijetShapeInterpolator CMSDIJET/DijetShapeInterpolator

cd CMSDIJET/DijetShapeInterpolator

```

## Perform interpolation

Create input root files with histograms of the X distribution (X = four-jet mass / Resonance mass) for all simulated signals. Takes as input the reduced trees. It is automated to give as input the width, alpha true and type (NOMINAL, JESup, JESdown, JERup):

```
root -l create_input_histos_for_interpolation.C(0.0043, 0.25, (char*)"NOMINAL")
```

Convert these root files into py files. This will create a py with the bin contents of the X distribution (normalized to 1) for all input (simulated) signals:

```
python3 extractShapes.py -i InputShapes_xxx.root > inputs/input_shapes_xxx.py
```

The above is automised for running for multiple widths, alpha true, alpha bins and types (open and view script below):

```
./run_extractShapes.sh 
```

Perform interpolation and produce output root files with interpolated shapes. This will create the ResonanceShapes_xxx.root file with histograms of all interpolated shapes from 2000 GeV to 10000 GeV with 100 GeV step. It will use as input all simulated signals you have provided and will always pick the two signals nearest to the mass that is to be interpolated each time. The code as is produces the four-jet mass distributions in the "standard dijet binning". Add --fineBinning to the command below to create 1 GeV binned histograms instead (these are not really needed for combine, the standard dijet binning is okay):

```
python3 getResonanceShapes.py -i inputs/input_shapes_xxx.py -f qq --massrange 2000 10000 100 -o output/ResonanceShapes_XXX.root --alpha 0.25
```

The above is automised for running for multiple widths, alpha true, alpha bins and types (open and view script below):

```
./run_getResonanceShapes.py
```

## Plot closure

Plotting scripts to compare a simulated with an interpolated signal shape:

```
root -l plot_simulated_vs_interpolated.C(0.0043, 0.25, 8000, 0)
```

The above is also automised to produce many plots in a loop:

```
./run_plot_simulated_vs_interpolated.sh
```

## Write histograms in the format needed for combine

Finally, take the output ResonanceShapes_XXX.root file and write the histograms in the format of the root files we use as input for creating datacards in combine:

```
root -l write_histos_for_combine.C(0.0043, 0.25, (char*)"NOMINAL")
```

This is also automised to run in a loop:

```
./run_write_histos_for_combine.sh
```

