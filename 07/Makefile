# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=../Eigen

temporary: build/kepler.png
all: archive.tar.gz

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

bin/02.out: src/02.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

build:
	mkdir -p build

build/euler.txt: bin/01.out
	./bin/01.out

build/kepler/r_i.txt: bin/02.out
	./bin/02.out

build/kepler.png: build/kepler/r_i.txt src/plot_2.py
	python src/plot_2.py

build/euler.png: src/plot_1.py build/euler.txt
	python src/plot_1.py

build/main.pdf: src/main.tex build/euler.png | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

archive.tar.gz: build/main.pdf Makefile $(wildcard src/*)
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean end run replace_matrices
