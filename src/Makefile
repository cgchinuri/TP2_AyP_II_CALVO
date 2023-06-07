PROGRAM=BATALLADIGITAL
CC=g++
CFLAGS=-Wall -std=c++98 -pedantic -ansi -g
LDFLAGS=
OBJ=tablero.o bitmap.o casillero.o EasyBMP.o main.o

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROGRAM) $(LDFLAGS)

tablero.o: Tablero/tablero.h Tablero/casillero.h
	$(CC) $(CFLAGS) -c Tablero/tablero.cpp

casillero.o: Tablero/casillero.h Utils/Coordenada.h Ficha/Ficha.h
	$(CC) $(CFLAGS) -c Tablero/casillero.cpp

Ficha.o: Ficha/ficha.h Tablero/casillero
	$(CC) $(CFLAGS) -c Ficha/ficha.cpp

bitmap.o: Utils/Bitmap/bitmap.h Ficha/Ficha.h Utils/Bitmap/EasyBMP_1.06/EasyBMP.h Utils/Bitmap/EasyBMP_1.06/EasyBMP_Font.h
	$(CC) $(CFLAGS) -c Utils/Bitmap/bitmap.cpp

EasyBMP.o: Utils/Bitmap/EasyBMP_1.06/EasyBMP.h
	$(CC) $(CFLAGS) -c Utils/Bitmap/EasyBMP_1.06/EasyBMP.cpp

main.o: Tablero/tablero.h Utils/Bitmap/bitmap.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -vf *.o $(PROGRAM)