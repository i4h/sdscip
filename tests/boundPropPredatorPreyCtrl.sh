#!/bin/bash

#backup sdscip.set and subscip.set
cd ..
cp sdscip.set tests/sdscip.set.bak
cp subscip.set tests/subscip.set.bak
cp tests/boundPropPredatorPreyCtrl.set sdscip.set
cp tests/boundPropPredatorPreyCtrl_subscip.set subscip.set


#run scip
bin/sdscip -b batch/solPredatorPreyCtrl.bat

#visualize
boundsParser.awk -v xstart=0 -v xend=100  tests_boundPropPredatorPreyCtrl_20_100.cip temp  Predator Prey

#clean up
rm tests_boundPropPredatorPreyCtrl_20_100.cip
rm temp.*

cp tests/sdscip.set.bak sdscip.set
cp tests/subscip.set.bak subscip.set

cd -
