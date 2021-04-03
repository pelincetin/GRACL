#!/bin/sh

#Cleanly tests one test file

LLC="llc"
CC="cc"
GRACL="./gracl.native"
Run() {
    eval $* || {
	return 1
    }
}
filename="./tests/test-$1.grc"
basename=`echo ${filename} | sed 's/.*\\///
                             s/.grc//'`
Run "make clean > discard.out" &&
Run "make > discard.out" &&
Run "$GRACL" "${filename}" ">" "${basename}.ll" &&
Run "$LLC" "-relocation-model=pic" "${basename}.ll" ">" "${basename}.s" &&
Run "$CC" "-o" "${basename}.exe" "${basename}.s" "node.o" &&#link in standard library in C
Run "./${basename}.exe" &&
rm discard.out "${basename}.exe" "${basename}.s" "${basename}.ll" 