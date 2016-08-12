#!/bin/bash
make clean OPT=dbg  LPS=spx IPOPT=true ZIMPL=false -j 8
make OPT=dbg  LPS=spx IPOPT=true ZIMPL=false  -j 8
