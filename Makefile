all: obj/ build/ obj/main.o build/physics 

clean:
	rm -r obj/ build/ 
.PHONY: clean

obj/:
	mkdir -p obj/

build/:
	mkdir -p build/

ifndef damp2
damp2 := 0.2
endif
ifndef damp
damp := 0.2
endif
obj/main.o: src/main.cpp
	${CXX} src/main.cpp -c -o obj/main.o -Ddamp2=${damp2} -Ddamp=${damp} 

build/physics: obj/main.o 
	${CXX} obj/main.o  -o build/physics -lsfml-graphics -lsfml-window -lsfml-system 

