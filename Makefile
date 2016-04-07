CCFLAGS = -std=c++0x -pedantic -Wextra -O3

all: compare-containers

compare-containers: MyDS.cpp compare.cpp 
	g++ $(CCFLAGS) -o compare-containers MyDS.cpp compare.cpp

clean: 
	rm -rf *.o *~ *.x

