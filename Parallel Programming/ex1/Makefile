all: build

./build/%.o: ./%.c 
	$(CC) -c -o $@ $< -I./include

build: ./build/fila.o ./build/mandel-tiles-graphic.o
	gcc -o prog mandel-tiles-graphic.c fila.c -I./include -lpthread -lm

run: build
	./prog $(ARGS)

clean: 
	/bin/rm -f ./build/*.o prog
