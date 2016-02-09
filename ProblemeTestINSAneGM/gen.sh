#!/bin/bash
COMP="g++"

[ $# -eq 0 ] && echo "Rentrez au moins un numero"
[ "$1" == "clean" ] && rm -f *.out && exit 0

for num in $*
do
    if [ -e v$num.* ]
    then
        echo "Version $num"
        $COMP v$num.* -o launch
        for inFile in *.in
        do
            name=$(basename -s .in $inFile)
            echo -n "  Test $name..."
            out=$(cat $inFile | ./launch | uniq)
            echo "$out" | wc -l > v$num\_$name.out
            cat v$num\_$name.out
            echo "$out" >> v$num\_$name.out
        done
    else
        echo "Fichier v$num.* non trouvé"
    fi
done

rm -f launch
