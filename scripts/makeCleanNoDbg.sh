#!/bin/bash
make clean  LPS=cpx IPOPT=true  -j 8
make  LPS=cpx IPOPT=true  -j 8
