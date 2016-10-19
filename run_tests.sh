#!/bin/bash
# Bash script template, based on http://www.pro-linux.de/artikel/2/111/ein-shellskript-template.html
# modifications by Ingmar Vierhaus <mail@ingmar-vierhaus.de>
set -o nounset
set -o errexit
# Script: new_script
# Global variables
SCRIPTNAME=$(basename $0 .sh)
EXIT_SUCCESS=0
EXIT_FAILURE=1
EXIT_ERROR=2
EXIT_BUG=10
# Initialize Variables defined by option switches
VERBOSE=n
FORCE=n
QUICK=n
OPTFILE=""
# function definitions 
function usage {
 echo "Usage: $SCRIPTNAME [-h] [-v] [-o arg] file ..." >&2
 echo "Run tests"
 echo ""
 echo "Options: "
 echo " -h        show this help"
 echo " -v        verbose mode"
 echo " -q        quick tests"
 echo " -f        force: dont check repos "
 [[ $# -eq 1 ]] && exit $1 || exit $EXIT_FAILURE
}
# List of Arguments. Option flags followed by a ":" require an option, flags not followed by an ":" are optionless
while getopts ':o:vhqf' OPTION ; do
 case $OPTION in
 v) VERBOSE=y
 ;;
 f) FORCE=y
 ;;
 q) QUICK=y
 ;;
 o) OPTFILE="$OPTARG"
 ;;
 h) usage $EXIT_SUCCESS
 ;;
 \?) echo "Option \"-$OPTARG\" not recognized." >&2
 usage $EXIT_ERROR
 ;;
 :) echo "Option \"-$OPTARG\" requires an argument." >&2
 usage $EXIT_ERROR
 ;;
 *) echo "Something impossible happened, stand by for implosion of space time continuum."
>&2
 usage $EXIT_BUG
 ;;
 esac
done
# Shift over used up arguments
shift $(( OPTIND - 1 ))
# Test for valid number of arguments
#if (( $# < 1 )) ; then
# echo "At least one argument required." >&2
# usage $EXIT_ERROR
#fi
# Loop over all arguments
for ARG ; do
 if [[ $VERBOSE = y ]] ; then
     echo -n "Argument: "
     echo $ARG
 fi
done




if [ -z ${FLAGS+x} ]; then
    FLAGS="OPT=dbg LPS=cpx IPOPT=true ZIMPL=false"
fi

log="logs/tests_current.log"
if [ $QUICK = y ]; then
    log="logs/tests_quick_current.log"
fi

echo "Writing log to "$log


# Check if repos are clean
if [[ $FORCE = n ]] ; then
    dirtyrepos=`sd_repo_summary.sh | grep "scip" | grep '(dirty)'` || true
    if [ "$dirtyrepos" != "" ] ; then
	echo "Dirty repo detected:"
	echo $dirtyrepos
	read -p "Continue with tests? " yn
	if [ $yn == "n" ] ; then
	    exit
	fi
    fi
fi

# Write repo status to log
echo "Getting repo_summary"
sd_repo_summary.sh | tee $log

make test TEST=simulate SETTINGS=simulate $FLAGS | tee -a $log
#read -p "Done with testset __simulate__. Press enter to continue" yn

make test TEST=propODE SETTINGS=propODE  TIME=10 $FLAGS  | tee -a $log
#read -p "Done with testset __simulate__. Press enter to continue" yn

if [[ $QUICK = n ]]; then
    make test TEST=obra SETTINGS=obra  $FLAGS  | tee -a $log
else
    make test TEST=obra_quick SETTINGS=obra  $FLAGS  | tee -a $log   
fi
#read -p "Done with testset __simulate__. Press enter to continue" yn


exit $EXIT_SUCCESS
