#!/bin/bash
make test TEST=simulate SETTINGS=simulate  OPT=dbg LPS=cpx IPOPT=true
read -p "Done with testet __simulate__. Press enter to continue" yn


make test TEST=propODE SETTINGS=propODE  TIME=10  OPT=dbg LPS=cpx IPOPT=true
