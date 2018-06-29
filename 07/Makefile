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

bin/02.out: src/02.cpp $(wildcard src/*.h) | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

build:
	mkdir -p build

build/.01.data.new: bin/01.out | build
	./bin/01.out
	touch build/.01.data.new

build/.02.data.new: bin/02.out | build
	./bin/02.out
	touch build/.02.data.new

build/.01.plot.new: build/.01.data.new src/plot_1.py
	python src/plot_1.py
	touch build/.01.plot.new

build/.02.plot.new: build/.02.data.new src/plot_2.py src/plot_2d.py
	python src/plot_2.py
	python src/plot_2d.py
	touch build/.02.plot.new

# build/euler.txt: bin/01.out
# 	./bin/01.out
#
# build/kepler/r_i.txt: bin/02.out
# 	./bin/02.out
#
# build/kepler.png: build/kepler/r_i.txt src/plot_2.py
# 	python src/plot_2.py
#
# build/kepler_moon/r_i.txt: bin/02.out
# 	./bin/02.out
#
# build/kepler_moon.png: build/kepler_moon/r_i.txt src/plot_2d.py
# 	python src/plot_2d.py
#
# build/euler.png: src/plot_1.py build/euler.txt
# 	python src/plot_1.py

build/main.pdf: src/main.tex build/.01.plot.new build/.02.plot.new FORCE | build
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
