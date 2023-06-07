#include <string>
#include "bitmap.h"
#include "EasyBMP_1.06/EasyBMP.h"
#include "EasyBMP_1.06/EasyBMP_Font.h"

#include "../Tablero/tablero.h"
#include "../Tablero/casillero.h"
#include "../Ficha/Ficha.h"

void asignarImagenes(unsigned int anchoTablero, unsigned int altoTablero, struct Imagenes *imagenes) {
    SetEasyBMPwarningsOff();
    imagenes->tablero.SetSize(anchoTablero, altoTablero);
    imagenes->pasto.ReadFromFile("bitmaps/pasto.bmp");
    imagenes->tierra.ReadFromFile("bitmaps/tierra.bmp");
    imagenes->agua.ReadFromFile("bitmaps/agua.bmp");
    imagenes->soldadoJugador.ReadFromFile("bitmaps/soldadoJugador.bmp");
    imagenes->soldadoEnemigo.ReadFromFile("bitmaps/soldadoEnemigo.bmp");
    imagenes->quimicos.ReadFromFile("bitmaps/quimicos.bmp");
    imagenes->minaJugador.ReadFromFile("bitmaps/minaJugador.bmp");
    imagenes->minaEnemigo.ReadFromFile("bitmaps/minaEnemigo.bmp");
    imagenes->avionJugador.ReadFromFile("bitmaps/avionJugador.bmp");
    imagenes->avionEnemigo.ReadFromFile("bitmaps/avionEnemigo.bmp");
    imagenes->barcoJugador.ReadFromFile("bitmaps/barcoJugador.bmp");
    imagenes->barcoEnemigo.ReadFromFile("bitmaps/barcoEnemigo.bmp");
    imagenes->submarinoJugador.ReadFromFile("bitmaps/submarinoJugador.bmp");
    imagenes->submarinoEnemigo.ReadFromFile("bitmaps/submarinoEnemigo.bmp");
    imagenes->error.ReadFromFile("bitmaps/error.bmp");
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

const char *crearRuta(unsigned int nivelZ) {
    char ruta[20] = "tableroNivel";
    char numero[4];
    sprintf(numero, "%ld", nivelZ);
    strcat(ruta, numero);
    strcat(ruta, ".bmp");
    return ruta;
}

void dibujarCasillero(unsigned int altoTablero, Casillero *casillero, struct Imagenes *imagenes) {
    unsigned int posX = casillero->getPosX();
    unsigned int posY = casillero->getPosY();
    switch (casillero->getTipoCasillero())
    {
    case tierra:
        if(casillero->getPosZ() < 4) {
            dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->tierra);
        }
        else {
            dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->pasto);
        }
        break;
    case agua:
        if(casillero->getPosZ() < 4) {
            dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->aguaProfunda);
        }
        else {
            dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->agua);
        }
    case aire:
        dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->aire);
    default:
        dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->error); // PARA DEBUG
        break;
    }

    Ficha *ficha = casillero->getFichaCasillero();
    if (ficha == NULL) return;
    switch (ficha->obtenerTipo())
    {
    case FICHA_BARCO:
        dibujarTransparente(posX, posY, altoTablero, imagenes->tablero, imagenes->barcoJugador);
        break;
    case FICHA_SOLDADO:
        dibujarTransparente(posX, posY, altoTablero, imagenes->tablero, imagenes->soldadoJugador);
        break;
    case FICHA_AVION:
        dibujarTransparente(posX, posY, altoTablero, imagenes->tablero, imagenes->avionJugador);
        break;
    case FICHA_MINA:
        dibujarTransparente(posX, posY, altoTablero, imagenes->tablero, imagenes->minaJugador);
        break;
    
    default:
        dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->error); // PARA DEBUG
        break;
    }
}

void dibujarCapa(unsigned int nivelZ, Tablero *tablero, struct Imagenes *imagenes) {
    unsigned int anchoTablero = tablero->getDimX();
    unsigned int altoTablero = tablero->getDimY();
    Casillero *casillero = NULL;
    for (size_t i = 0; i < anchoTablero; i++) {
        for (size_t j = 0; j < altoTablero; j++) {
            casillero = tablero->obtenerCasillero(i, j, nivelZ);
            if (casillero == NULL) {
                throw "Error de casillero";
            }
            dibujarCasillero(altoTablero, casillero, imagenes);
        }
        
    }
    imagenes->tablero.WriteToFile(crearRuta(nivelZ));
}

void dibujarTablero(Tablero *tablero, struct Imagenes *imagenes) {
    unsigned int profundidadTablero = tablero->getDimZ();
    for (size_t i = 0; i < profundidadTablero; i++) {
        dibujarCapa(i, tablero, imagenes);
}

//SetEasyBMPwarningsOff();

