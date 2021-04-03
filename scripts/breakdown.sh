#!/bin/sh
LLC="llc"
CC="cc"
GRACL="./gracl.native"

name=$1

Run() {
    echo $* 1>>"${name}.breakdown"
    eval $* || {
	return 1
    }
}

filename="./tests/test-$1.grc"
basename=`echo ${filename} | sed 's/.*\\///
                             s/.grc//'`
Run "make debugclean" ">> discard.out" &&
Run "make" ">> discard.out" &&
rm discard.out &&
echo "\n${filename}"  >> "$1.breakdown" &&
cat "${filename}" >> "$1.breakdown" &&
echo "\n"  >> "$1.breakdown" &&
Run "$GRACL" "-a" "${filename}" ">> $1.breakdown"&&
echo "\n" >> "$1.breakdown" &&
Run "$GRACL" "-s" "${filename}" ">> $1.breakdown"&&
echo "\n" >> "$1.breakdown" &&
Run "$GRACL" "-c" "${filename}" ">> $1.breakdown"&&
echo "\n" >> "$1.breakdown" &&
Run "$GRACL" "${filename}" ">" "${basename}.ll" &&
Run "$LLC" "-relocation-model=pic" "${basename}.ll" ">" "${basename}.s" &&
Run "$CC" "-o" "${basename}.exe" "${basename}.s" "node.o"&& #link in standard library in C
echo "\n" >> "$1.breakdown" &&
Run "./${basename}.exe" ">> $1.breakdown" &&
echo "Please look at ${name}.breakdown"
