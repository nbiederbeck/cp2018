all: bin/01 bin/02

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
