/*
 * BitmapBatallaDigital - Logica de EasyBMP_1.06 para Batalla Digital V2
 *
 *  Created on: 24 May. 2023
 *      Author: Facundo Baratta
 */

#ifndef BITMAP_H
#define BITMAP_H

#include "EasyBMP_1.06/EasyBMP.h"
#include "../../Tablero/tablero.h"

class BitmapBatallaDigital {
private:
    unsigned int resolucionImagenes;
    RGBApixel colorTransparente;

    BMP imagenTablero;
    BMP imagenPasto;
    BMP imagenTierra;
    BMP imagenAgua;
    BMP imagenAguaProfunda;
    BMP imagenAire;
    BMP imagenSoldadoJugador;
    BMP imagenSoldadoEnemigo;
    BMP imagenQuimicos;
    BMP imagenMinaJugador;
    BMP imagenMinaEnemigo;
    BMP imagenAvionJugador;
    BMP imagenAvionEnemigo;
    BMP imagenBarcoJugador;
    BMP imagenBarcoEnemigo;
    BMP imagenSubmarinoJugador;
    BMP imagenSubmarinoEnemigo;
    BMP imagenNiebla;
    BMP imagenError;

    void dibujar(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero);
    void dibujarTransparente(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero);
    void dibujarLetra(RGBApixel colorLetra, unsigned int altoTablero);
    void dibujarCasillero(Casillero *casillero, unsigned int altoTablero);
    void dibujarCapa(Tablero *tablero, unsigned int nivelZ);


public:

    //PRE: Recibe la dimension en pixeles cuadrados de los sprites a utilizar y su color de transparencia, y las dimensiones del tablero
    //POS: Devuelve una nueva instancia de la clase encargada de dibujar el tablero por capa
    BitmapBatallaDigital(unsigned int resolucionImagenes, RGBApixel colorTransparente, unsigned int anchoTablero, unsigned int altoTablero);

    //PRE: Recibe un tablero valido
    //POS: Dibuja el tablero por capas
    void dibujarTablero(Tablero *tablero);

    //DESTUCTOR - POS: Destruye la instancia de la clase
    ~BitmapBatallaDigital();

};

#endif // BITMAP_H