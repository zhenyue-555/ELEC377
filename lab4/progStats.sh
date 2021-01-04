#!/bin/sh

if (($# != 1)); then
  echo "Usage: $0 DIRECTORY" 
  exit 1
fi

#hasMainFile=1 
if [ -d $1 ]; then
hasMainFile=1
echo "Main file:"
for file in `find "$1" -name '*c' `;do
	if `grep -q "int main" "$file"`; then
            fprintfvar=`grep -c "fprintf" $file`
	    printfvar=`grep -c "printf" $file`
	    printfvari=$((printfvar - fprintfvar))
	    hasMainFile=0 
            echo $file: $printfvari, $fprintfvar

	fi
	done

if(($hasMainFile!=0));then
    echo "No main file"
fi
hasModuleFile=1 

#if(($hasModuleFile!=0));then
#	echo "No module file"
#fi
echo -e "\nModule Files:"
    for file in `find "$1" -name '*.c' `; do
	if `grep -q "init_module" "$file"` ; then
       		lineNumber=`grep -n "printk" $file | sed -e 's/:.*\;//' | tr [:space:] ','| tr -s ','` 
       		echo $file: " ${lineNumber%?} "
		hasModuleFile=0;
        fi

	done
	
if(($hasModuleFile!=0));then
	echo "No module file"
fi

else
echo "$1 not found"

fi


