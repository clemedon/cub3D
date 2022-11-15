#!/bin/bash

FILES=maps/error_maps
for f in $FILES
do
    echo "Processing $f..."
    make asan && ./cub3D $f
done
