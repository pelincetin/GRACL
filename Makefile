# "make gracl.native" compiles the compiler
#
# The _tags file controls the operation of ocamlbuild, e.g., by including
# packages, enabling warnings
#
# See https://github.com/ocaml/ocamlbuild/blob/master/manual/manual.adoc

gracl.native :
	opam config exec -- \
	ocamlbuild -use-ocamlfind gracl.native

.PHONY : codegen
codegen: 
	ocamlc ast.ml
	ocamlc -c sast.ml ast.cmo
	ocamlfind ocamlc -c -w +a-4 -package llvm -package llvm.analysis -o codegen.cmo codegen.ml
# "make clean" removes all generated files

.PHONY : clean
clean :
	ocamlbuild -clean
	rm -rf testall.log ocamlllvm *.diff *.mli graclparser.ml *.output gracl.native *.cmi *.cmo *.out *.ll *.s *.diff *.err
