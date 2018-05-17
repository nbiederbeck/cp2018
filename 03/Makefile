all: bin/01 bin/02

BUILDS_01 = $(addprefix build/, $(addsuffix .txt, \
			01_b ))
$(BUILDS_01): bin/01
	./bin/01

BUILDS_02 = $(addprefix build/, $(addsuffix .txt, \
			))
$(BUILDS_02): bin/02
	./bin/02


# C++ Binaries
bin/01: src/01.cpp | bin build
	g++ -O2 -o bin/01 \
		src/01.cpp

bin/02: src/02.cpp | bin build
	g++ -O2 -fopenmp -o bin/02 \
		src/02.cpp

bin:
	mkdir -p bin

# LaTeX PDF
build/main.pdf: build/plot_01_b.png src/main.tex | build
	latexmk --lualatex --output-directory=build \
		src/main.tex

preview: build/plot_01_b.png src/main.tex | build
	latexmk --lualatex --output-directory=build \
		src/main.tex --pvc

build/plot_01_b.png: src/plot_01_b.py build/01_b.txt
	python src/plot_01_b.py

build:
	mkdir -p build

# Abgabe
abgabe.tar.gz: build/main.pdf src/01.cpp src/02.cpp
	mkdir -p abgabe/
	cp build/main.pdf src/01.cpp src/02.cpp abgabe/
	printf "all:\n\tg++ -O2 -o 01.out 01.cpp\n\tg++ -O2 -o 02.out 02.cpp" >> abgabe/Makefile
	tar czf abgabe.tar.gz abgabe/*
	rm -rf abgabe/

# Make
clean:
	rm -rf bin build abgabe.tar.gz abgabe

.PHONY: all clean
