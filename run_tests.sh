#!/bin/bash

if [ $FLAGS = "" ]; then
    FLAGS="OPT=dbg LPS=cpx IPOPT=true ZIMPL=false"
fi

make test TEST=simulate SETTINGS=simulate $FLAGS
#read -p "Done with testset __simulate__. Press enter to continue" yn

make test TEST=propODE SETTINGS=propODE  TIME=10 $FLAGS
#read -p "Done with testset __simulate__. Press enter to continue" yn

make test TEST=obra SETTINGS=obra  $FLAGS
#read -p "Done with testset __simulate__. Press enter to continue" yn

