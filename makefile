# Set DEBUG to 1 to include all debugging flags and code.  Set to 0 to
# get fully optimized code.
DEBUG=1
CXX=g++

# Set compilation flags below
ifeq ($(DEBUG), 1)
#	Compilation flags for debug mode
	CXXFLAGS=-Wall -O0 -g
else
#	Compilation flags
	CXXFLAGS=-Wall -O2 -DNDEBUG
endif

# Actual compilation
#checkers: src/checkerboard.o
#	$(CXX) $(CXXFLAGS) 


chess_script: src/main.o src/chessobjs.o
	$(CXX) -o chess_script src/main.o src/chessobjs.o

src/main.o: src/main.cpp src/chessobjs.h
	$(CXX) -o $@ -c $(CXXFLAGS) src/main.cpp

src/chessobjs.o: src/chessobjs.cpp src/chessobjs.h
	$(CXX) -o $@ -c $(CXXFLAGS) src/chessobjs.cpp

clean:


