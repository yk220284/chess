CXX = clang++
CXXFLAGS = -Wall -g -std=c++17

chess: ChessMain.o ChessBoard.o board.o piece.o util.o player.o
	$(CXX) $(CXXFLAGS) -o chess ChessMain.o ChessBoard.o board.o piece.o util.o player.o
ChessMain.o: ChessMain.cpp ChessBoard.h board.hpp piece.hpp util.hpp player.hpp
	$(CXX) $(CXXFLAGS) -c ChessMain.cpp

ChessBoard.o : ChessBoard.h board.hpp piece.hpp util.hpp player.hpp 

# test: test.o board.o piece.o util.o player.o
# 	$(CXX) $(CXXFLAGS) -o test test.o board.o piece.o util.o player.o
# test.o: test.cpp board.hpp piece.hpp util.hpp player.hpp
# 	$(CXX) $(CXXFLAGS) -c test.cpp

board.o: board.hpp piece.hpp util.hpp

player.o: player.hpp util.hpp board.hpp

piece.o: piece.hpp util.hpp

util.o:util.hpp

clean:
	rm *.o chess
	echo clean is done%