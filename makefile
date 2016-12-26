
usage:
	@echo "usage:"
	@echo "make run<return> :To execute"
	@echo "make build<return> :To build project"

run:
	./run.out

build:
	gcc -o run.out main.c brelese.c buf.c getblk.c
