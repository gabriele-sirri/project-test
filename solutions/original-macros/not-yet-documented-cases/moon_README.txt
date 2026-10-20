
1. MAKE THE MODEL

gab@VAIO-GAB:/mnt/c/WORKSPACE/CERNBox/teaching/AnalisiStatisticaDati-Common/solutions$ root -l moon_make_model.cpp
root [0]
Processing moon_make_model.cpp...
root [1] .q

2. FIT AND PLOT THE MODEL

gab@VAIO-GAB:/mnt/c/WORKSPACE/CERNBox/teaching/AnalisiStatisticaDati-Common/solutions$ root -l moon_model.root
root [0]
Attaching file moon_model.root as _file0...
root [1] .L moon_make_model.cpp
root [2] plot2d(*w)
root [3] .q

3. EVAL SIGNIFICANCE

gab@VAIO-GAB:/mnt/c/WORKSPACE/CERNBox/teaching/AnalisiStatisticaDati-Common/solutions$ root -l
root [0] .L $ROOTSYS/tutorials/roostats/StandardHypoTestDemo.C
root [1] optHT.useProof = true
root [2] StandardHypoTestDemo("moon_model.root", "w", "ModelConfig_HT", "", "data", 0, 3, 10000, false)
root [3] .q

4. INTERVALS (to be confirmed)

gab@VAIO-GAB:/mnt/c/WORKSPACE/CERNBox/teaching/AnalisiStatisticaDati-Common/solutions$ root -l
root [0] .L $ROOTSYS/tutorials/roostats/StandardProfileLikelihoodDemo.C
root [1] StandardProfileLikelihoodDemo("moon_model.root", "w", "ModelConfig_POS", "data")
root [2] .q
