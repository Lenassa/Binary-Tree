GPP = g++ -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra -std=c++11

all : test.exe

test.exe : test.o descendants.o ancetres.o individu.o
	$(GPP) test.o descendants.o ancetres.o individu.o -o test.exe

test.o : test.cpp descendants.hpp ancetres.hpp individu.hpp
	$(GPP) -c test.cpp

descendants.o : descendants.cpp descendants.hpp 
	$(GPP) -c descendants.cpp

ancetres.o : ancetres.cpp ancetres.hpp
	$(GPP) -c ancetres.cpp

individu.o : individu.cpp individu.hpp
	$(GPP) -c individu.cpp

clean : 
	rm *.o test.exe
