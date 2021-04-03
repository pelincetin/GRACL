#!/bin/sh

# clean the directory and make the targets again
make clean
make all

out_dir="outputs"

for i in $(find . -perm +111 -type f);  
    do $i > "$out_dir"/"$i"_output.txt
    if cmp -s "$out_dir"/"$i"_output.txt "$out_dir"/"$i"_example.txt; then
        echo " $i ....SUCCESS"
    else
        echo " $i ....FAILURE" 
    fi
done
