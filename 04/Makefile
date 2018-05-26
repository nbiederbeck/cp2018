.NOTPARALLEL:
all: bin/01 

EIGENPATH= /home/maximilian/Dokumente/01-Uni/09-Comp.-Phy./04-Dependence/eigen

# C++ Binaries
build/q_2.txt: src/01q2.cpp | bin build
	g++ -O2 -o bin/01q2 \
			-I $(EIGENPATH) \
			-std=c++11 \
		src/01q2.cpp
	./bin/01q2

build/q_3.txt: src/01q3.cpp | bin build
	g++ -O2 -o bin/01q3 \
			-I $(EIGENPATH) \
			-std=c++11 \
		src/01q3.cpp
	./bin/01q3

build/q_6.txt: src/01q6.cpp | bin build
	g++ -O2 -o bin/01q6 \
			-I $(EIGENPATH) \
			-std=c++11 \
		src/01q6.cpp
	./bin/01q6

build/q_20.txt: src/01q20.cpp | bin build
	g++ -O2 -o bin/01q20 \
			-I $(EIGENPATH) \
			-std=c++11 \
		src/01q20.cpp
	./bin/01q20

bin:
	mkdir -p bin

build/q_2_0.pdf: src/plot_lattice.py | build/q_2.txt  build/q_3.txt
	python src/plot_lattice.py

build/q_3_0.pdf: src/plot_lattice.py | build/q_3.txt  build/q_2.txt
	python src/plot_lattice.py

build/energy2.pdf: src/plot_energy.py | build/energie.txt
	python src/plot_energy.py

build/energy3.pdf: src/plot_energy.py | build/energie3.txt
	python src/plot_energy.py

build/energy6.pdf: src/plot_energy.py | build/energie6.txt
	python src/plot_energy.py

build/energy20.pdf: src/plot_energy.py | build/energie20.txt
	python src/plot_energy.py

build/magn2.pdf: src/plot_magn.py | build/magn.txt
	python src/plot_magn.py

build/magn3.pdf: src/plot_magn.py | build/magn3.txt
	python src/plot_magn.py

build/magn6.pdf: src/plot_magn.py | build/magn6.txt
	python src/plot_magn.py

build/magn20.pdf: src/plot_magn.py | build/magn20.txt
	python src/plot_magn.py

buildfiles = build/q_2_0.pdf \
		build/q_3_0.pdf \
		build/energy2.pdf \
		build/energy3.pdf \
		build/energy6.pdf \
		build/energy20.pdf\
		build/magn2.pdf\
		build/magn3.pdf\
		build/magn6.pdf\
		build/magn20.pdf\


# LaTeX PDF
build/main.pdf: $(buildfiles)
build/main.pdf: src/main.tex | build
	lualatex --output-directory=build \
		src/main.tex

build:
	mkdir -p build

# Abgabe
abgabe.tar.gz: build/main.pdf src/01.cpp 
	mkdir -p abgabe/
	cp build/main.pdf src/01.cppabgabe/
	printf "all:\n\tg++ -O2 -o 01.out 01.cpp" >> abgabe/Makefile
	tar czf abgabe.tar.gz abgabe/*
	rm -rf abgabe/

# Make
clean:
	rm -rf bin build abgabe.tar.gz abgabe

.PHONY: all clean
