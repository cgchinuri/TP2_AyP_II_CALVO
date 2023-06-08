PROGRAM=BATALLADIGITAL
CC=g++
CFLAGS=-Wall -std=c++98 -pedantic -ansi -g
LDFLAGS=
OBJ=tablero.o casillero.o EasyBMP.o Ficha.o main.o BatallaDigital.o Jugador.o BitmapBatallaDigital.o cartaBatallaDigital.o

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROGRAM) $(LDFLAGS)

tablero.o: Tablero/tablero.h Tablero/casillero.h
	$(CC) $(CFLAGS) -c Tablero/tablero.cpp

casillero.o: Tablero/casillero.h Utils/Coordenada.h Ficha/Ficha.h
	$(CC) $(CFLAGS) -c Tablero/casillero.cpp

Ficha.o: Ficha/Ficha.h
	$(CC) $(CFLAGS) -c Ficha/Ficha.cpp

Jugador.o: Jugador/Jugador.h Carta_Mazo/cartaBatallaDigital.h
	$(CC) $(CFLAGS) -c Jugador/Jugador.cpp

cartaBatallaDigital.o: Carta_Mazo/cartaBatallaDigital.h 
	$(CC) $(CFLAGS) -c Carta_Mazo/cartaBatallaDigital.cpp

BitmapBatallaDigital.o: Utils/Bitmap/BitmapBatallaDigital.h Ficha/Ficha.h Utils/Bitmap/EasyBMP_1.06/EasyBMP.h Utils/Bitmap/EasyBMP_1.06/EasyBMP_Font.h
	$(CC) $(CFLAGS) -c Utils/Bitmap/BitmapBatallaDigital.cpp

EasyBMP.o: Utils/Bitmap/EasyBMP_1.06/EasyBMP.h
	$(CC) $(CFLAGS) -c Utils/Bitmap/EasyBMP_1.06/EasyBMP.cpp

BatallaDigital.o: BatallaDigital/BatallaDigital.h
	$(CC) $(CFLAGS) -c BatallaDigital/BatallaDigital.cpp

main.o: Tablero/tablero.h Utils/Bitmap/BitmapBatallaDigital.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -vf *.o $(PROGRAM)