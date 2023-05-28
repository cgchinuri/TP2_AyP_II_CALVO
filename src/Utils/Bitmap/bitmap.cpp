#include <string>
#include "EasyBMP_1.06/EasyBMP.h"
#include "EasyBMP_1.06/EasyBMP_Font.h"

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

int main() {
    SetEasyBMPwarningsOff();
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
        dibujarTransparente(i, 40, altoTablero, tablero, imagenSoldadoEnemigo);
        dibujarTransparente(i, 36, altoTablero, tablero, imagenQuimicos);
        dibujarTransparente(i, 5, altoTablero, tablero, imagenSoldadoJugador);
        dibujarTransparente(i, 2, altoTablero, tablero, imagenMinaJugador);
        dibujarTransparente(i, 1, altoTablero, tablero, imagenMinaEnemigo);
    }
    
    RGBApixel colorLetra;
    colorLetra.Blue = colorLetra.Red = colorLetra.Green = 0;
    unsigned int altoLetra = RESOLUCION/3;
    char numero[3];
    for (size_t i = 0; i < altoTablero; i++)
    {
        sprintf(numero, "%ld", i);
        PrintString(tablero, numero, i * RESOLUCION + RESOLUCION/2, RESOLUCION * altoTablero - altoLetra, altoLetra, colorLetra);
        PrintLetter(tablero, 'A' + i, 0, (altoTablero - i - 1) * RESOLUCION, altoLetra, colorLetra);
    }

    tablero.WriteToFile("tablero.bmp");
}