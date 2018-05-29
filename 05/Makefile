# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=~/Downloads/Eigen

all: run

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin
	c++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

bin/02.out: src/02.cpp | bin
	c++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

build:
	mkdir -p build

build/main.pdf: src/main.tex | build
	lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

archive.tar.gz: src/01.cpp src/02.cpp build/main.pdf Makefile
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

end: archive.tar.gz

run: bin/01.out bin/02.out
	./bin/01.out
	./bin/02.out

.PHONY: all clean end run
