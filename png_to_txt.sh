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

# Initialize variables
counter=1

# Clear or create the output file
echo -n > "$output_file"

# Generate sprite data
for ((row=0; row<rows; row++)); do
  for ((col=0; col<cols; col++)); do
    x=$((col * sprite_width))
    y=$((row * sprite_height))
    echo "$suffix$counter = $x $y $sprite_width $sprite_height" >> "$output_file"
    counter=$((counter + 1))
  done
done

echo "Sprite data has been written to $output_file."
