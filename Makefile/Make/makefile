# make command executes only first target
#  - if first target needs some dependencies, than make looks for other targets
#    and executes them
#  - hence, when running "make" command, target "clean" is not executed

make.exe: main.o Message.o
	g++ obj/main.o obj/Message.o -o main.exe
	mv main.exe bin

main.o: main.cpp
	g++ -c main.cpp
	mv main.o obj

Message.o: Message.cpp Message.hpp
	g++ -c Message.cpp
	mv Message.o obj

clean:
	rm -r obj/Message.o obj/main.o bin/main.exe