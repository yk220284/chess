CXX = clang++
CXXFLAGS = -Wall -g -std=c++17

test: test.o board.o piece.o util.o player.o
	$(CXX) $(CXXFLAGS) -o test test.o board.o piece.o util.o player.o
test.o: test.cpp board.hpp piece.hpp util.hpp player.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

board.o: board.hpp piece.hpp util.hpp

player.o: player.hpp util.hpp board.hpp

piece.o: piece.hpp util.hpp

util.o:util.hpp

clean:
	rm *.o test
	echo clean is done%