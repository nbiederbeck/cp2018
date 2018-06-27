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

all: archive.tar.gz

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

bin/02.out: src/02.cpp | bin build
	g++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $<

build:
	mkdir -p build

build/pendulum_data_b.txt build/pendulum_data_c_plus.txt build/pendulum_data_c_minus.txt: bin/01.out
	./bin/01.out

build/pendulum_b.png build/pendulum_xy_b.png: src/plot_pendulum_b.py build/pendulum_data_b.txt
	python $<

build/pendulum_c_plus.png build/pendulum_c_minus.png build/pendulum_xy_c_minus.png build/pendulum_xy_c_plus.png: src/plot_pendulum_c.py build/pendulum_data_c_plus.txt build/pendulum_data_c_minus.txt
	python $<


build/main.pdf: src/main.tex $(PLOTS1) FORCE | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

FORCE:

archive.tar.gz: build/main.pdf Makefile $(wildcard src/*) $(wildcard build/*data*)
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

.PHONY: all clean FORCE
