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
# function definitions 
function usage {
 echo "Usage: $SCRIPTNAME [-h] [-v] [-o arg] file ..." >&2
 echo "Removes scip headers from source files in current directory"
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
#if (( $# < 1 )) ; then
# echo "At least one argument required." >&2
# usage $EXIT_ERROR
#fi
# Loop over all arguments
for ARG ; do
 if [[ $VERBOSE = y ]] ; then
     echo -n "Argument: "
     cho $ARG
 fi
done


searchstring="SCIP is distributed under the terms of the ZIB Academic License."
files=`grep -l "$searchstring" *`

endstring="1----+----2----+----3"



for i in $files ; do
    linenr=`grep -n "$endstring" $i | cut -f 1 -d ":"`
    if [[ $linenr == "" ]] ; then
	echo "no end line found in "$i;
    else
	echo Deleting lines 1 - $linenr in $i
	nextline=$(($linenr+1))
	tail -n +$nextline $i > temp.txt
	cp temp.txt $i
    fi

done

exit $EXIT_SUCCESS
