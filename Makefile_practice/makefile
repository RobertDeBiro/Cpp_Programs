make.exe: main.o Message.o
	g++ main.o Message.o -o main.exe

main.o: main.cpp
	g++ -c main.cpp

Message.o: Message.cpp Message.hpp
	g++ -c Message.cpp

clean:
	rm *.o main.exe

# Makefile syntax:
# target: prerequisites
#    action
#
# target:
#	- name of the file created or updated after executing action
#	- file creation and update depends on 2 things:
#       - if file doesn't exist, it will be created
#		- if file already exists, it will be updated if prerequisites were changed in the meantime
#	- if non of the conditions are true, file won't be changed, i.e. action won't be triggered
# prerequisites:
#	- files which existance is necessary before creating/updating the target
#	- when one of those files are changed, the make function will trigger action and update target
# action
#	- command that is run after make is executed, and all conditions are satisfied