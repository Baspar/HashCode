#!/bin/bash
COMP="g++"

[ $# -eq 0 ] && echo "Rentrez au moins un numero"

for num in $*
do
    $COMP v$num.* -o launch
    for inFile in *.in
    do
        name=$(basename -s .in $inFile)
        out=$(cat $inFile | ./launch)
        echo "$out" | wc -l > v$num\_$name.out
        echo "$out" >> v$num\_$name.out
    done
done

rm -f launch
