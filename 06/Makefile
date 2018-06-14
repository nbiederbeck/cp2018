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

build/main.pdf: src/main.tex replace_matrices build/plot1c.png build/plot1b.png | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

replace_matrices: run
	sed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/T0_cpp.tex > build/T0.tex
	sed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/T1_cpp.tex > build/T1.tex
	sed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/q0_cpp.tex > build/q0.tex
	sed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/q1_cpp.tex > build/q1.tex

build/plot1c.png: build/task1c.txt src/1c.py
	python src/1c.py

build/plot1b.png: build/task1b.txt src/1b.py
	python src/1b.py

build/task1c.txt: run
build/task1b.txt: run

run: bin/01.out bin/02.out
	./bin/01.out
	./bin/02.out

archive.tar.gz: src/01.cpp src/02.cpp build/main.pdf Makefile
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean end run replace_matrices
