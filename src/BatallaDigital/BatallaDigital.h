#ifndef BATALLA_DIGITAL_H_
#define BATALLA_DIGITAL_H_

#include "../tablero.h"
#include "../Ficha.hpp"

class BatallaDigital
{
    private:

        // La cantidad de jugadores que van a jugar
        unsigned int cantidadJugadores;

        // Dimensiones del tablero
        unsigned int dimensionesTablero [3];

        // Aca tendria que haber una lista de jugadores

        // Puntero al tablero
        Tablero * tableroJuego;

    public:
        // Constructor
        // Pre: -
        // Pos: genera una lista con la cantidad de jugadores
        //      genera un tablero y deja su puntero apuntando a él
        BatallaDigital(unsigned int cantJugadores, unsigned int * dimTab);

        // Pre: recibe como argumento un puntero a un casillero y un puntero a una ficha
        //      ambos deben estar apuntando a null
        // Pos: los enlaza entre si
        void vincularFichaYCasillero(Casillero * casillero , Ficha * ficha);

        // Pre: recibe como argumento un puntero a una ficha
        // Pos: la deja apuntando a null en su puntero a casillero
        void desvincularFicha(Ficha * ficha);

        // Pre: recibe como argumento un puntero a un casillero
        // Pos: lo deja apuntnado a null en su puntero a ficha
        void desvincularCasillero(Casillero * casillero);

};













#endif