# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=../Eigen

PLOTS = $(addprefix build/pendulum_, $(addsuffix .png, \
))


all: archive.tar.gz

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

build:
	mkdir -p build

build/main.pdf: src/main.tex $(PLOTS) FORCE | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

FORCE:

archive.tar.gz: build/main.pdf Makefile $(wildcard src/*)
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean FORCE
