make clean OPT=dbg;
cd ../../;
make clean OPT=dbg ;
cd -;
make scip OPT=dbg LPS=cpx -j 8;
make OPT=dbg LPS=cpx -j 8
