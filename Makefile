# "make gracl.native" compiles the compiler
#
# The _tags file controls the operation of ocamlbuild, e.g., by including
# packages, enabling warnings
#
# See https://github.com/ocaml/ocamlbuild/blob/master/manual/manual.adoc
.PHONY : all
all : gracl.native graclstdlib.o

stdlib : graclstdlib.c
	cc -o graclstdlib -pthread graclstdlib.c

gracl.native :
	opam config exec -- \
	ocamlbuild -use-ocamlfind gracl.native

.PHONY: gracllib
gracllib: gracllib.c 
	gcc -g -Wall -pthread -o gracllib gracllib.c

.PHONY : codegen
codegen: 
	ocamlc ast.ml
	ocamlc -c sast.ml ast.cmo
	ocamlfind ocamlc -c -w +a-4 -package llvm -package llvm.analysis -o functions.cmo functions.ml
	ocamlfind ocamlc -c -w +a-4 -package llvm -package llvm.analysis -o codegen.cmo codegen.ml

.PHONY : semant
semant:
	ocamlc ast.ml
	ocamlc -c sast.ml ast.cmo
	ocamlfind ocamlc -c -w +a-4 -package llvm -package llvm.analysis -o functions.cmo functions.ml
	ocamlc -c semant.ml ast.cmo sast.cmo functions.cmo

.PHONY : helloworld
helloworld:
	./scripts/breakdown.sh helloWorld 

# "make clean" removes all generated files

.PHONY : clean
clean :
	ocamlbuild -clean
<<<<<<< HEAD
	rm -rf testall.log ocamlllvm *.diff *.mli graclparser.ml gracllib *.output gracl.native *.cmi *.cmo *.out *.ll *.s *.err *.exe *.breakdown
=======
	rm -rf *.o testall.log ocamlllvm *.diff *.mli graclparser.ml *.output gracl.native *.cmi *.cmo *.out *.ll *.s *.err *.exe *.breakdown
>>>>>>> main

# removes some generated files while keeping those useful for debugging
.PHONY : debugclean
debugclean:
	ocamlbuild -clean
	rm -rf ocamlllvm *.mli graclparser.ml *.output gracl.native *.cmi *.cmo *.out *.s *.exe 