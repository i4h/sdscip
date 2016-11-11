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
CLEAN=n
CLEANONLY=n
OPTFILE=""
TARGET=""
NCORES="8"
# function definitions 
function usage {
 echo "Usage: $SCRIPTNAME [-h] [-v] [-o arg] file ..." >&2
 echo "Makes It"
 echo ""
 echo "Options: "
 echo " -c          make clean first"
 echo " -o          make clean only"
 echo " -j ncores   how many process should be launched"
 echo " -t target   make target "


 echo " -h          show this help"
 echo " -v          verbose mode"

 [[ $# -eq 1 ]] && exit $1 || exit $EXIT_FAILURE
}
# List of Arguments. Option flags followed by a ":" require an option, flags not followed by an ":" are optionless
while getopts ':j:t:vhco' OPTION ; do
 case $OPTION in
 v) VERBOSE=y
 ;;
 c) CLEAN=y
 ;;
 o) CLEANONLY=y
 ;;
 j) NCORES="$OPTARG"
 ;;
 t) TARGET="$OPTARG"
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
if (( $# != 0 )) ; then
 echo "No arguments accepted" >&2
 usage $EXIT_ERROR
fi
# Loop over all arguments
for ARG ; do
 if [[ $VERBOSE = y ]] ; then
     echo -n "Argument: "
     echo $ARG
 fi
done


file="make_flags"
makeFlags="OPT=dbg  LPS=cpx IPOPT=true ZIMPL=false"

if [ -e "$file" ]
then
    source $file
fi

echo "Making with "$makeFlags

# clean if clean flag
if [[ $CLEAN = y ]] ; then
    make -j $NCORES clean $makeFlags    
    exit $?
fi

# clean if cleanonly flag
if [[ $CLEANONLY = y ]] ; then
    make -j $NCORES clean $makeFlags    
    exit $?
fi

# Make if not cleanonly
if [[ $CLEANONLY = n ]] ; then
    echo "make -j $NCORES $TARGET $makeFlags "

    make -j $NCORES $TARGET $makeFlags    
    exit $?
fi

exit $EXIT_SUCCESS
test
