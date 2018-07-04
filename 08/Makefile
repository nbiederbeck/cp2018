# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=../Eigen

PLOTS1 = $(addprefix build/pendulum_, $(addsuffix .png, \
	xy_c_plus \
	xy_c_minus \
	xy_b \
	c_plus \
	c_minus \
	b \
))

PLOTS2 = $(addprefix build/poincare_, $(addsuffix .png, \
	a \
	b \
	c \
))

all: archive.tar.gz

bin:
	mkdir -p bin

bin/01.out: src/01.cpp src/physics.hpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

bin/02.out: src/02.cpp src/physics.hpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

build:
	mkdir -p build

build/pendulum_data_b.txt build/pendulum_data_c_plus.txt build/pendulum_data_c_minus.txt: bin/01.out
	./bin/01.out

build/pendulum_b.png build/pendulum_xy_b.png: src/plot_pendulum_b.py build/pendulum_data_b.txt
	python $<

build/pendulum_c_plus.png build/pendulum_c_minus.png build/pendulum_xy_c_minus.png build/pendulum_xy_c_plus.png: src/plot_pendulum_c.py build/pendulum_data_c_plus.txt build/pendulum_data_c_minus.txt
	python $<

build/poincare_data_periodic.txt build/poincare_data_quasi.txt build/poincare_data_chaos.txt build/poincare_c_1.txt build/poincare_c_10.txt build/poincare_c_70.txt: bin/02.out
	./bin/02.out

build/poincare_a.png: src/plot_poincare_a.py build/poincare_data_periodic.txt build/poincare_data_quasi.txt build/poincare_data_chaos.txt
	python $<

build/poincare_b.png: src/plot_poincare_b.py build/poincare_data_periodic.txt build/poincare_data_quasi.txt build/poincare_data_chaos.txt build/poincare_data_periodic_disturbed.txt build/poincare_data_quasi_disturbed.txt build/poincare_data_chaos_disturbed.txt
	python $<

build/poincare_c.png: src/plot_poincare_c.py build/poincare_c_1.txt build/poincare_c_10.txt build/poincare_c_70.txt
	python $<

build/main.pdf: src/main.tex $(PLOTS1) $(PLOTS2) FORCE | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

FORCE:

archive.tar.gz: build/main.pdf Makefile $(wildcard src/*) $(wildcard build/*data*) $(wildcard build/poincare_c_*.txt)
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean FORCE
