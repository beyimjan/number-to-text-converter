#!/bin/sh

prog=./number-to-text-converter

[ -f $prog ] || { echo Couldn\'t find the program to test! >&2 ; exit 1 ; }

cat tests.txt | while read question && read answer; do
    result=`$prog $question`
    if [ "$result" != "$answer" ]; then
        echo TEST "'$question'" FAILED!
        echo EXPECTED: "'$answer'"
        echo GOT: "'$result'"
        echo "----------------------------------------"
    fi
done
