# 'make' command executes only first target
#  - if first target needs some dependencies, than 'make' looks for other targets
#    and executes them
#  - hence, when running 'make' command, target 'clean' is not executed

make.exe: obj/main.o obj/Message.o | bin
	g++ obj/main.o obj/Message.o -o bin/main.exe

obj/main.o: main.cpp | obj
	g++ -c main.cpp -o obj/main.o

obj/Message.o: Message.cpp Message.hpp | obj
	g++ -c Message.cpp -o obj/Message.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf obj bin
