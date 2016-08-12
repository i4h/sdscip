#!/bin/bash
make clean OPT=dbg  LPS=cpx IPOPT=true ZIMPL=false -j 8
make OPT=dbg  LPS=cpx IPOPT=true ZIMPL=false  -j 8
