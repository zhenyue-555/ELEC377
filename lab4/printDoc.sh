#!/bin/sh
//find all c and h files
for file in `find . -name '*.c' -or -name '*.h'` ; do 
//print a equal line
echo "==================================================================";  
//extract all lines start with "//+" and end with "//-"
sed  -e '/\/\/+/,/\/\/-/p' -e  'd'  $file; 
//remove "//+", "//-", and "//"
done | sed -e 's/\/\/+//' | sed -e 's/\/\/-//' | sed  -e  's/\/\///' 
