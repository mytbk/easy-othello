#CXX=clang++
CXXFLAGS=-g -Wall
OBJS=reverse.o main.o functions.o

prog : $(OBJS)
	$(CXX) $(OBJS) -o prog

#reverse.o : reverse.cpp
#	$(CXX) -c $(CXXFLAGS) reverse.cpp -o reverse.o

#main.o : main.cpp
#	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

clean :
	rm *.o prog

.PHONY : clean
