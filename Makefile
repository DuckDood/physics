all: obj/ build/ obj/main.o build/physics 

clean:
	rm -r obj/ build/ 
.PHONY: clean

obj/:
	mkdir -p obj/

build/:
	mkdir -p build/

obj/main.o: src/main.cpp
	${CXX} src/main.cpp -c -o obj/main.o 

build/physics: obj/main.o 
	${CXX} obj/main.o  -o build/physics -lsfml-graphics -lsfml-window -lsfml-system 

