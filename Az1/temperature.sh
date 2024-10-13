#!/bin/bash

echo -n "Please Enter the Number: "
read -r temp

if(( temp < 0 )); then
	echo "The Weather is Freezing"
elif(( temp >= 0 && temp < 30 )); then
	echo "The Weather is Cool !"
else
	echo "The Weather is Hot"
fi
