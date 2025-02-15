#!/bin/bash
	
if [ "$#" -ne 2 ]; then
    echo "Error: Please provide exactly two arguments."
    exit 1
fi

# Assign the arguments to variables for easier use
filesdir="$1"
searchstr="$2"

# Check if each argument is non-empty
if [ -z "$filesdir" ]; then
    echo "Error: path to directory is empty."
    exit 1
fi

if [ -z "$searchstr" ]; then
    echo "Error: text string is empty."
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "Given directory $filesdir doesn't exist"
    exit 1
fi

#echo "Arguments are: $filesdir and $searchstr"

# Initialize counters
file_count=0
match_count=0

# Find all files in the directory and its subdirectories
file_count=$(find "$filesdir" -type f | wc -l)
match_count=$(grep -r -w -o "$searchstr" "$filesdir" | wc -l)

# Display the results
echo "The number of files are $file_count and the number of matching lines are $match_count"

exit 0
