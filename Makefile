# "make gracl.native" compiles the compiler
#
# The _tags file controls the operation of ocamlbuild, e.g., by including
# packages, enabling warnings
#
# See https://github.com/ocaml/ocamlbuild/blob/master/manual/manual.adoc

gracl.native :
	opam config exec -- \
	ocamlbuild -use-ocamlfind gracl.native

# "make clean" removes all generated files

.PHONY : clean
clean :
	ocamlbuild -clean
	rm -rf testall.log ocamlllvm *.diff *.mli graclparser.ml *.output gracl.native *.cmi *.cmo *.out
