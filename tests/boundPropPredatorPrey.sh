#!/bin/bash

#backup sdscip.set
cd ..
cp sdscip.set tests/sdscip.set.bak
cp tests/boundPropPredatorPrey.set sdscip.set


#run scip
bin/sdscip -b batch/solPredatorPrey.bat

#visualize
boundsParser.awk -v xstart=0 -v xend=199  tests_boundPropPredatorPrey_20.cip temp  Predator Prey

#clean up
rm tests_boundPropPredatorPrey_20.cip
rm temp.*

cp tests/sdscip.set.bak sdscip.set

cd -