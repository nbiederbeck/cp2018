# Variables:
# $@ : target
# $? : newer prerequisites
# $^ : all prerequisites
# $< : first prerequisite

EIGENPATH=../Eigen

all: run

bin:
	mkdir -p bin

bin/01.out: src/01.cpp | bin
	c++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

bin/02.out: src/02.cpp | bin
	c++ -O2 -std=c++11 -I $(EIGENPATH) -o $@ $^

build:
	mkdir -p build

build/main.pdf: src/main.tex build/eigenvalues.png build/householder_final.txt | build
	latexmk --lualatex \
		--output-directory=build \
		--interaction=nonstopmode \
		--halt-on-error \
	$<

build/householder.txt: bin/01.out | build
	./bin/01.out

build/householder_final.txt: build/householder.txt
	sed -i 's/\,/\&/g;s/0)//g;s/(//g;' $^ && \
	sed 'a\\\\\\' $^ > $@

build/eigensolver_eigenvalues.txt: bin/01.out | build
	./bin/01.out

build/hand_eigenvalues.txt: bin/01.out | build
	./bin/01.out

build/eigenvalues.png: build/hand_eigenvalues.txt build/eigensolver_eigenvalues.txt src/plot_eigenvalues.py
	sed -i 's/,/ /g;s/[()]//g' build/eigensolver_eigenvalues.txt
	sed -i 's/,/ /g;s/[()]//g' build/hand_eigenvalues.txt
	python src/plot_eigenvalues.py

archive.tar.gz: src/01.cpp src/02.cpp build/main.pdf Makefile
	tar czf $@ $^

clean:
	rm -rf build bin archive.tar.gz

end: archive.tar.gz

run: bin/01.out bin/02.out | build
	./bin/01.out
	./bin/02.out

.PHONY: all clean end run
