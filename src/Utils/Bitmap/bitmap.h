#ifndef BITMAP_H
#define BITMAP_H

#include "EasyBMP_1.06/EasyBMP.h"
#include "../../Tablero/tablero.h"

#define RESOLUCION 50 // pixeles

struct Imagenes {
    BMP tablero;
    BMP pasto;
    BMP tierra;
    BMP agua;
    BMP aguaProfunda;
    BMP aire;
    BMP soldadoJugador;
    BMP soldadoEnemigo;
    BMP quimicos;
    BMP minaJugador;
    BMP minaEnemigo;
    BMP avionJugador;
    BMP avionEnemigo;
    BMP barcoJugador;
    BMP barcoEnemigo;
    BMP submarinoJugador;
    BMP submarinoEnemigo;
    BMP error;
};

void iniciarBitmap(unsigned int anchoTablero, unsigned int altoTablero, struct Imagenes *imagenes);

void dibujarTablero(Tablero *tablero, struct Imagenes *imagenes);

#endif // BITMAP_H