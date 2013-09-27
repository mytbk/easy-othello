CFLAGS=-g -O2 -Wall
CXXFLAGS=${CFLAGS}

MAINOBJS=operations.o main.o functions.o game_ai.o 
AIOBJ= btr_ai.o
DEBUGOBJ=debug.o
OBJS=${MAINOBJS} \
	 ${AIOBJ} \
	 ${DEBUGOBJ}

prog : $(OBJS)
	$(CXX) $(OBJS) -o prog

functions.o simple_ai.o : debug.h

#reverse.o : reverse.cpp
#	$(CXX) -c $(CXXFLAGS) reverse.cpp -o reverse.o

#main.o : main.cpp
#	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

clean :
	rm *.o prog

.PHONY : clean
