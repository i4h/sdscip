#!/bin/bash

#backup sdscip.set
cd ..
cp sdscip.set tests/sdscip.set.bak
cp tests/solMiniweltSim.set sdscip.set


#run scip
bin/sdscip -b batch/solMiniweltSim.bat

#visualize
boundsParser.awk -v xstart=0 -v xend=250  tests_boundPropMiniweltSim_0.cip temp  BEVOELKERUNG ANLAGEN UMWELTBELASTUNG

#clean up
rm tests_boundPropMiniweltSim_0.cip
rm temp.*

cp tests/sdscip.set.bak sdscip.set

cd -