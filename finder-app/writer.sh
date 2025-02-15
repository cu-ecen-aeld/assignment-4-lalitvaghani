#!/bin/bash
	
if [ "$#" -ne 2 ]; then
    echo "Error: Please provide exactly two arguments."
    exit 1
fi

# Assign the arguments to variables for easier use
writefile="$1"
writestr="$2"

# Check if each argument is non-empty
if [ -z "$writefile" ]; then
    echo "Error: write file path is empty."
    exit 1
fi

if [ -z "$writestr" ]; then
    echo "Error: write string is empty."
    exit 1
fi

# Create the directory path if it doesn't exist
sudo mkdir -p "$(dirname "$writefile")" || {
    echo "Error: Unable to create directory path."
    exit 1
}

# Write content to the file, overwriting if it exists
echo "$writestr" > "$writefile" || {
    echo "Error: Unable to create or write to the file '$writefile'."
    exit 1
}
