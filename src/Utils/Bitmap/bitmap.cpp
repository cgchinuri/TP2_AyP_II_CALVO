#include <string>
#include "bitmap.h"
#include "EasyBMP_1.06/EasyBMP.h"
#include "EasyBMP_1.06/EasyBMP_Font.h"

#include "../../Tablero/tablero.h"
#include "../../Tablero/casillero.h"
#include "../../Ficha/Ficha.h"
#include "../LinkedList_T.h"

void iniciarBitmap(unsigned int anchoTablero, unsigned int altoTablero, struct Imagenes *imagenes) {
    SetEasyBMPwarningsOff();
    imagenes->tablero.SetSize(anchoTablero * RESOLUCION, altoTablero * RESOLUCION);
    imagenes->pasto.ReadFromFile("Utils/Bitmap/bitmaps/pasto.bmp");
    imagenes->tierra.ReadFromFile("Utils/Bitmap/bitmaps/tierra.bmp");
    imagenes->agua.ReadFromFile("Utils/Bitmap/bitmaps/agua.bmp");
    imagenes->soldadoJugador.ReadFromFile("Utils/Bitmap/bitmaps/soldadoJugador.bmp");
    imagenes->soldadoEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/soldadoEnemigo.bmp");
    imagenes->quimicos.ReadFromFile("Utils/Bitmap/bitmaps/quimicos.bmp");
    imagenes->minaJugador.ReadFromFile("Utils/Bitmap/bitmaps/minaJugador.bmp");
    imagenes->minaEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/minaEnemigo.bmp");
    imagenes->avionJugador.ReadFromFile("Utils/Bitmap/bitmaps/avionJugador.bmp");
    imagenes->avionEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/avionEnemigo.bmp");
    imagenes->barcoJugador.ReadFromFile("Utils/Bitmap/bitmaps/barcoJugador.bmp");
    imagenes->barcoEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/barcoEnemigo.bmp");
    imagenes->submarinoJugador.ReadFromFile("Utils/Bitmap/bitmaps/submarinoJugador.bmp");
    imagenes->submarinoEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/submarinoEnemigo.bmp");
    imagenes->error.ReadFromFile("Utils/Bitmap/bitmaps/error.bmp");
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

void dibujarCasillero(unsigned int altoTablero, Casillero *casillero, struct Imagenes *imagenes) {
    unsigned int posX = casillero->getCoordenada()->obtenerX() - 1;
    unsigned int posY = casillero->getCoordenada()->obtenerY() - 1;
    unsigned int posZ = casillero->getCoordenada()->obtenerZ() - 1;

    switch (casillero->getTipoCasillero())
    {
    case tierra:
        if(posZ < 4) {
            dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->tierra);
        }
        else {
            dibujar(posX, posY, altoTablero, imagenes->tablero, imagenes->pasto);
        }
        break;
    case agua:
        if(posZ < 4) {
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

void dibujarCapa(Lista<Lista<Casillero*>* >*  piso, unsigned int nivelZ, unsigned int anchoTablero, unsigned int altoTablero, struct Imagenes *imagenes) {
    Lista<Casillero*>* columnasRecorrer=NULL;
    for(int y = 1 ; y <= altoTablero ; y++)
    {
        columnasRecorrer=piso->get(y);
        for(int x = 1 ; x <= anchoTablero ; x++)
        {
            dibujarCasillero(altoTablero, columnasRecorrer->get(x), imagenes);
        }
    }
    
    // ESTO ESCIBRE EL NOMBRE DE LA CAPA
    char ruta[20] = "tableroNivel";
    char numero[4];
    sprintf(numero, "%d", nivelZ);
    strcat(ruta, numero);
    strcat(ruta, ".bmp");
    imagenes->tablero.WriteToFile(ruta);
}

void dibujarTablero(Tablero *tablero, struct Imagenes *imagenes) {
    unsigned int profundidadTablero = tablero->getDimZ();
    unsigned int anchoTablero = tablero->getDimX();
    unsigned int altoTablero = tablero->getDimY();

	for(int z = 1 ; z <= profundidadTablero ; z++) {
		dibujarCapa(tablero->getTableroJuego()->get(z), z, anchoTablero, altoTablero, imagenes);
    }	
}


//SetEasyBMPwarningsOff();

