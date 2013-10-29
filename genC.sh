#!/bin/sh

name=$1

if [ -e $name ]
then
    echo "Error: file already exists. Please edit file directly or choose another name for the new file."
else
    echo "/*" >> $name
    echo " * Program: $name" >> $name
    echo " * Usage:" >> $name
    echo " * CS241 hw6" >> $name
    echo " * Author Shiying Zheng and Ben Stern" >> $name
    echo -n " * " >> $name
    date >> $name
    echo " */" >> $name
    shift
    while [ $# -gt 0 ]
    do
	echo "#include <$1>" >> $name
	shift
    done
fi

echo "\n" >> $name
echo "int main(){" >> $name
echo "  //to be implemented" >> $name
echo "}" >> $name