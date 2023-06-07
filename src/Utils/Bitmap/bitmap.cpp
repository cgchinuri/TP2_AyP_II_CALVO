#include <string>
#include "EasyBMP_1.06/EasyBMP.h"
#include "EasyBMP_1.06/EasyBMP_Font.h"

#include "../Tablero/tablero.h"
#include "../Tablero/casillero.h"
#include "../Ficha/Ficha.h"

#define RESOLUCION 50 // pixeles

struct Imagenes {
    BMP tableroNivelDelMar;
    BMP tableroSubterraneo;
    BMP tableroAereo;
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
};

void iniciarBitmap(unsigned int anchoTablero, unsigned int altoTablero, struct Imagenes &imagenes) {
    imagenes.tableroNivelDelMar.SetSize(RESOLUCION * anchoTablero, RESOLUCION * altoTablero);
    imagenes.tableroSubterraneo.SetSize(RESOLUCION * anchoTablero, RESOLUCION * altoTablero);
    imagenes.tableroAereo.SetSize(RESOLUCION * anchoTablero, RESOLUCION * altoTablero);
    imagenes.pasto.ReadFromFile("bitmaps/pasto.bmp");
    imagenes.tierra.ReadFromFile("bitmaps/tierra.bmp");
    imagenes.agua.ReadFromFile("bitmaps/agua.bmp");
    imagenes.soldadoJugador.ReadFromFile("bitmaps/soldadoJugador.bmp");
    imagenes.soldadoEnemigo.ReadFromFile("bitmaps/soldadoEnemigo.bmp");
    imagenes.quimicos.ReadFromFile("bitmaps/quimicos.bmp");
    imagenes.minaJugador.ReadFromFile("bitmaps/minaJugador.bmp");
    imagenes.minaEnemigo.ReadFromFile("bitmaps/minaEnemigo.bmp");
    imagenes.avionJugador.ReadFromFile("bitmaps/avionJugador.bmp");
    imagenes.avionEnemigo.ReadFromFile("bitmaps/avionEnemigo.bmp");
    imagenes.barcoJugador.ReadFromFile("bitmaps/barcoJugador.bmp");
    imagenes.barcoEnemigo.ReadFromFile("bitmaps/barcoEnemigo.bmp");
    imagenes.submarinoJugador.ReadFromFile("bitmaps/submarinoJugador.bmp");
    imagenes.submarinoEnemigo.ReadFromFile("bitmaps/submarinoEnemigo.bmp");
}

void dibujar(unsigned int x, unsigned int y, unsigned int altoTablero, BMP &tablero, BMP &elemento)
{   
    unsigned int moverX = x * RESOLUCION;
    unsigned int moverY = RESOLUCION * (altoTablero - 1 - y);
    for (size_t i = 0; i < RESOLUCION; i++) {
        for (size_t j = 0; j < RESOLUCION; j++) {
            PixelToPixelCopy(elemento, i, j, tablero, i + moverX, j + moverY);
        }     
    }
}

void dibujarTransparente(unsigned int x, unsigned int y, unsigned int altoTablero, BMP &tablero, BMP &elemento)
{   
    RGBApixel transparent;
    transparent.Blue = transparent.Green = transparent.Red = 0; // NEGRO
    unsigned int moverX = x * RESOLUCION;
    unsigned int moverY = RESOLUCION * (altoTablero - 1 - y);
    for (size_t i = 0; i < RESOLUCION; i++) {
        for (size_t j = 0; j < RESOLUCION; j++) {
            PixelToPixelCopyTransparent(elemento, i, j, tablero, i + moverX, j + moverY, transparent);
        }     
    }
}

void dibujarLetra(unsigned int altoTablero, BMP tablero, RGBApixel colorLetra) {
    unsigned int altoLetra = RESOLUCION/3;
    char numero[3];
    for (size_t i = 0; i < altoTablero; i++)
    {
        sprintf(numero, "%ld", i);
        PrintString(tablero, numero, i * RESOLUCION + RESOLUCION/2, RESOLUCION * altoTablero - altoLetra, altoLetra, colorLetra);
        PrintLetter(tablero, 'A' + i, 0, (altoTablero - i - 1) * RESOLUCION, altoLetra, colorLetra);
    }
}

//SetEasyBMPwarningsOff();    tablero.WriteToFile("tablero.bmp");

