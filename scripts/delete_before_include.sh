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
OPTFILE=""
TEMPFILE=.delete_before_include.tmp
# function definitions 
function usage {
 echo "Usage: $SCRIPTNAME [-h] [-v] [-o arg] file ..." >&2
 echo "Deletes everything before the first #include in given files"
 echo ""
 echo "Options: "
 echo " -h        show this help"
 echo " -v        verbose mode"
 [[ $# -eq 1 ]] && exit $1 || exit $EXIT_FAILURE
}
# List of Arguments. Option flags followed by a ":" require an option, flags not followed by an ":" are optionless
while getopts ':o:vh' OPTION ; do
 case $OPTION in
 v) VERBOSE=y
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
if (( $# < 1 )) ; then
 echo "At least one argument required." >&2
 usage $EXIT_ERROR
fi
# Loop over all arguments
for ARG ; do
 if [[ $VERBOSE = y ]] ; then
     echo -n "Argument: "
     echo $ARG
 fi
done

for ARG ; do

    echo -n "Argument: "
    echo $ARG

    # find first #include# 
    includeline=`grep -n "#include" $ARG  | head -n 1 | cut -d ":" -f 1`
    # find guard
    guardline=`grep -n "#ifndef" $ARG  | head -n 1 | cut -d ":" -f 1`

    line=$((includeline > guardline ? includeline : guardline))

    echo $line

    if [ $line != "1" ] ; then
	line=$((line-1))
	sedstring="1,"$line"d"
	sed -i $sedstring $ARG
    fi
done




exit $EXIT_SUCCESS
