#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 5 ]; then
  echo "Usage: $0 <image_width> <image_height> <cols> <rows> <output_file>"
  exit 1
fi

# Assign arguments to variables
image_width=$1
image_height=$2
cols=$3
rows=$4
output_file=$5

# Extract the suffix from the output file name
base_name=$(basename "$output_file")
suffix=${base_name##*_}
suffix=${suffix%.*}

# Calculate sprite width and height
sprite_width=$((image_width / cols))
sprite_height=$((image_height / rows))

# Validate dimensions
if ((image_width % cols != 0 || image_height % rows != 0)); then
  echo "Error: Image dimensions are not evenly divisible by the number of columns and rows."
  exit 1
fi

# Ask user for delay and loop values
read -p "Enter delay (in milliseconds): " delay
read -p "Enter loop (0 for no loop, 1 for loop): " loop

# Initialize variables
counter=1
sequence_numbers=()

# Clear or create the output file
echo -n > "$output_file"

# Generate sprite data
for ((row=0; row<rows; row++)); do
  for ((col=0; col<cols; col++)); do
    x=$((col * sprite_width))
    y=$((row * sprite_height))
    echo "$suffix$counter = $x, $y, $sprite_width, $sprite_height" >> "$output_file"
    sequence_numbers+=($counter)
    counter=$((counter + 1))
  done
done

echo "Sprite data has been written to $output_file."

# Generate .sqx file
sqx_file="${output_file%.*}.sqx"
echo '<?xml version="1.0" encoding="UTF-8"?>' > "$sqx_file"
echo "" >> "$sqx_file"
echo "<sequences>" >> "$sqx_file"
echo "  <sequence name=\"$suffix\" delay=\"$delay\" loop=\"$loop\">" >> "$sqx_file"
sequence_string=$(IFS=,; echo "${sequence_numbers[*]}")
echo "    $sequence_string" >> "$sqx_file"
echo "  </sequence>" >> "$sqx_file"
echo "</sequences>" >> "$sqx_file"

echo "Sequence XML has been written to $sqx_file."
