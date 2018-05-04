.NOTPARALLEL:
all: bin/01 bin/02

BUILDS_01 = $(addprefix build/, $(addsuffix .txt, \
	eins zwei drei vier 1e Eins Zwei ))
$(BUILDS_01): bin/01
	./bin/01

BUILDS_02 = $(addprefix build/, $(addsuffix .txt, \
	task1aI task2aI task2b task2c task2cI))
$(BUILDS_02): bin/02
	./bin/02


build/plot_01a.png: build/eins.txt build/zwei.txt build/drei.txt build/vier.txt src/plot_nr1_bc.py
	python src/plot_nr1_bc.py
build/plot_01b.png: build/eins.txt build/zwei.txt build/drei.txt build/vier.txt src/plot_nr1_bc.py
	python src/plot_nr1_bc.py
build/plot_01d.png: build/Eins.txt build/Zwei.txt src/plot_nr1_d.py
	python src/plot_nr1_d.py
build/plot_01e.png: build/1e.txt src/plot_nr1_e.py
	python src/plot_nr1_e.py
build/plot_02a.png: build/task2aI.txt src/plot_nr2_a.py
	python src/plot_nr2_a.py
build/plot_02b.png: build/task2b.txt src/plot_nr2_b.py
	python src/plot_nr2_b.py
build/plot_02c.png: build/task2cI.txt build/task2c.txt src/plot_nr2_c.py
	python src/plot_nr2_c.py

# C++ Binaries
bin/01: src/01.cpp | bin build
	g++ -O2 -o bin/01 \
		src/01.cpp

bin/02: src/02.cpp | bin
	g++ -O2 -o bin/02 \
		src/02.cpp

bin:
	mkdir -p bin

# LaTeX PDF
build/main.pdf: $(addprefix build/plot_0, $(addsuffix .png, \
	1a 1b 1d 1e 2a 2b ))
build/main.pdf: src/main.tex | build
	lualatex --output-directory=build \
		src/main.tex

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
