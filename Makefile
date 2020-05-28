.default: all

all: azul

clean:
	rm -rf azul *.o *.dSYM

azul: Driver.o Game.o Menu.o LinkedList.o Node.o BoxLid.o Factory.o Player.o Tile.o TileBag.o Mosaic.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
