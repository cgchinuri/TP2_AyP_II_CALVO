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
#include "../../Jugador/Jugador.h"

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
    BMP imagenTrincheraJugador;
    BMP imagenTrincheraEnemigo;
    BMP imagenFuego;
    BMP imagenError;

    //PRE: Recibe la posicion x, y, el alto del tablero, y el elemento a graficar
    //POS: Grafica el elemento en la posicion (x, y) del tablero
    void dibujar(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero);

    //PRE: Recibe la posicion x, y, el alto del tablero, y el elemento a graficar
    //POS: Grafica el elemento en la posicion (x, y) del tablero ignorando el color de transparencia definido en el constructor
    void dibujarTransparente(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero);

    //PRE: Recibe el color de la letra y el alto del tablero
    //POS: Grafica las coordenadas del tablero
    void dibujarCoordenadas(RGBApixel colorLetra, unsigned int altoTablero);

    //PRE: Recibe un casillero y jugador validos, y el alto del tablero
    //POS: Grafica el terreno del casillero y su ficha si corresponde
    void dibujarCasillero(Casillero *casillero, Jugador *jugador, unsigned int altoTablero);

    //PRE: Recibe un tablero y jugador validos, y el nivel Z a graficar
    //POS: Grafica la capa Z y escribe un archivo (nuevo)
    void dibujarCapa(Tablero *tablero, Jugador *jugador, unsigned int nivelZ);


public:

    //CONSTRUCTOR
    //PRE: Recibe las dimensiones del tablero
    //POS: Devuelve una nueva instancia de la clase encargada de dibujar el tablero por capa
    BitmapBatallaDigital(unsigned int anchoTablero, unsigned int altoTablero);

    //PRE: Recibe un tablero valido. Si el jugador es nulo, grafica todas las fichas
    //POS: Dibuja el tablero por capas
    void dibujarTablero(Tablero *tablero, Jugador *jugador);

    //DESTUCTOR - PRE: - POS: Destruye la instancia de la clase
    ~BitmapBatallaDigital() {};

};

#endif // BITMAP_H