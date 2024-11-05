#!/bin/bash

level=0
max_level=10 

while [ $level -lt $max_level ]
do
  mkdir -p "level_$level"
  echo "Created directory: level_$level"
  cd "level_$level"
  ((level++))
done
