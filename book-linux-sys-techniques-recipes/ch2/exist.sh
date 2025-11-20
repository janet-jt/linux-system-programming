#!/bin/bash

#Check if the user supplied exactly one argument
if [ "$#" -ne 1 ]; then
	echo "You must supply exactly one argument."
	echo "Example: $0 /etc"
	exit 1 # Return 1
fi

#Check if the file/dir exists
test -e "$1"
if [ "$?" -eq 0 ]; then
	echo "File or dir exists"
elif [ "$?" -eq 1 ]; then
	echo "File or dir does not exist"
	exit 3 #Return with a special code so other programs can use the value to see if a file doesn't exist
else
	echo "Unknown return value from test.."
	exit 1
fi
exit 0
