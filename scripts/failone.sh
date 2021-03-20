#!/bin/sh

#Cleanly tests one fail file

LLC="llc"
CC="cc"
GRACL="./gracl.native"
Run() {
    eval $* || {
	return 1
    }
}
filename="./tests/fail-$1.grc"
basename=`echo ${filename} | sed 's/.*\\///
                             s/.grc//'`
Run "make clean > discard.out" &&
Run "make > discard.out" &&
rm discard.out &&
Run "$GRACL" "${filename}"  