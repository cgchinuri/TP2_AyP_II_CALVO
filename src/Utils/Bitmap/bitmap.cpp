#include "EasyBMP_1.06/EasyBMP.h"
#include "TP2_AyP_II_CALVO/src/Tablero/tablero.h"

#define RESOLUCION 50 // pixeles

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
    RGBApixel transparent = {.Blue = 0, .Green = 0, .Red = 0}; // NEGRO
    unsigned int moverX = x * RESOLUCION;
    unsigned int moverY = RESOLUCION * (altoTablero - 1 - y);
    for (size_t i = 0; i < RESOLUCION; i++) {
        for (size_t j = 0; j < RESOLUCION; j++) {
            PixelToPixelCopyTransparent(elemento, i, j, tablero, i + moverX, j + moverY, transparent);
        }     
    }
}

int main() {

    BMP tablero;
    unsigned int anchoTablero = 25, altoTablero = 50;
    tablero.SetSize(RESOLUCION * anchoTablero, RESOLUCION*altoTablero);
    BMP imagenTierra;
    imagenTierra.ReadFromFile("bitmaps/tierra.bmp");
    BMP imagenAgua;
    imagenAgua.ReadFromFile("bitmaps/agua.bmp");
    BMP imagenSoldadoJugador;
    imagenSoldadoJugador.ReadFromFile("bitmaps/soldadoJugador.bmp");
    BMP imagenSoldadoEnemigo;
    imagenSoldadoEnemigo.ReadFromFile("bitmaps/soldadoEnemigo.bmp");
    BMP imagenQuimicos;
    imagenQuimicos.ReadFromFile("bitmaps/quimicos.bmp");
    BMP imagenMinaJugador;
    imagenMinaJugador.ReadFromFile("bitmaps/minaJugador.bmp");
    BMP imagenMinaEnemigo;
    imagenMinaEnemigo.ReadFromFile("bitmaps/minaEnemigo.bmp");

    for (size_t i = 0; i < 25; i++)
    {
        for (size_t j = 0; j < 25; j++)
        {
            dibujar(i, j, altoTablero, tablero, imagenTierra);
        }
    }

    for (size_t i = 0; i < 25; i++)
    {
        for (size_t j = 25; j < 50; j++)
        {
            dibujar(i, j, altoTablero, tablero, imagenAgua);

        }
    }

    for (size_t i = 0; i < 25; i++)
    {    
        dibujarTransparente(i, 0, altoTablero, tablero, imagenSoldadoEnemigo);
        dibujarTransparente(i, 49, altoTablero, tablero, imagenQuimicos);
        dibujarTransparente(i, 5, altoTablero, tablero, imagenSoldadoJugador);
        dibujarTransparente(i, 2, altoTablero, tablero, imagenMinaJugador);
        dibujarTransparente(i, 1, altoTablero, tablero, imagenMinaEnemigo);
    }
    
    tablero.WriteToFile("tablero.bmp");
}