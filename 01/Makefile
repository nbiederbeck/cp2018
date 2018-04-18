FILENAME = mc_integration
COMPILER = g++

all: build/main.pdf bin/$(FILENAME)

again: touch run

touch:
	touch src/$(FILENAME).cpp

bin/$(FILENAME): bin src/$(FILENAME).cpp
	$(COMPILER) \
		-Wall \
		-o bin/$(FILENAME) \
		-O2 \
		src/$(FILENAME).cpp

run: bin/$(FILENAME)
	./bin/$(FILENAME)


bin:
	mkdir -p bin

clean:
	rm -rf bin/ build/

.PHONY: all clean run touch

build/main.pdf: src/main.tex | build
	pdflatex --output-directory=build \
		src/main.tex

build:
	mkdir -p build
