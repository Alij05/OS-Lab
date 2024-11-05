#!/bin/bash

echo -n "Enter The Number: "
read -r num

while [ "$num" -gt 0 ]; do
	echo -n "$((num%10))"
	num=$((num / 10))
done

