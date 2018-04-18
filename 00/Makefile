FILENAME = roundings
COMPILER = g++

all: run

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
	rm -rf bin/

.PHONY: all clean run touch
