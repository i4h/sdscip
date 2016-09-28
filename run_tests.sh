#!/bin/bash

if [ -z ${FLAGS+x} ]; then
    FLAGS="OPT=dbg LPS=cpx IPOPT=true ZIMPL=false"
fi

log="logs/tests_current.log"

cat /dev/null > $log

make test TEST=simulate SETTINGS=simulate $FLAGS | tee -a $log
#read -p "Done with testset __simulate__. Press enter to continue" yn

make test TEST=propODE SETTINGS=propODE  TIME=10 $FLAGS  | tee -a $log
#read -p "Done with testset __simulate__. Press enter to continue" yn

make test TEST=obra SETTINGS=obra  $FLAGS  | tee -a $log
#read -p "Done with testset __simulate__. Press enter to continue" yn

