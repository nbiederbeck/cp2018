# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=../Eigen

all: archive.tar.gz

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

bin/02.out: src/02.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

build:
	mkdir -p build

build/pendulum_data_b.txt: bin/01.out
	./bin/01.out

build/pendulum_b.png build/pendulum_xy_b.png: src/plot_pendulum_b.py build/pendulum_data_b.txt
	python $<


build/main.pdf: src/main.tex FORCE | build
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
