# make command executes only first target
#  - if first target needs some dependencies, than make looks for other targets
#    and executes them
#  - hence, when running "make" command, target "clean" is not executed

make.exe: main.o Message.o
	g++ main.o Message.o -o main.exe
	mv Message.o main.o main.exe Output_files

main.o: main.cpp
	g++ -c main.cpp

Message.o: Message.cpp Message.hpp
	g++ -c Message.cpp

clean:
	rm *.o main.exe