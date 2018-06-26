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

build/main.pdf: src/main.tex replace_matrices build/plot1c.png build/plot1b.png build/plot2b.png build/plot2d.png | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

replace_matrices: run
	gsed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/T0_cpp.tex > build/T0.tex
	gsed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/T1_cpp.tex > build/T1.tex
	gsed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/q0_cpp.tex > build/q0.tex
	gsed --expression="s/  */ \& /2g" --expression="s/$$/ \\\\\\\\/"  build/q1_cpp.tex > build/q1.tex

build/plot1c.png: build/task1c.txt src/1c.py
	python src/1c.py

build/plot1b.png: build/task1b.txt src/1b.py
	python src/1b.py

build/plot2b.png: build/task2b.txt src/2b.py
	python src/2b.py

build/plot2d.png: build/task2d.txt src/2d.py
	python src/2d.py

build/task1c.txt: run
build/task1b.txt: run
build/task2b.txt: run
build/task2d.txt: run

run: bin/01.out bin/02.out build
	./bin/01.out
	./bin/02.out

archive.tar.gz: build/main.pdf Makefile $(wildcard src/*)
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean end run replace_matrices
