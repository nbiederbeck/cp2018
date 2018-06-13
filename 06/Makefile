# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=../Eigen

all: archive.tar.gz

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

bin/02.out: src/02.cpp | bin
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

build:
	mkdir -p build

build/main.pdf: src/main.tex | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

archive.tar.gz: src/01.cpp src/02.cpp build/main.pdf Makefile
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean end run
