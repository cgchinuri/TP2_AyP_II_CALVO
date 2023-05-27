#ifndef BATALLA_DIGITAL_H_
#define BATALLA_DIGITAL_H_

#include "../tablero.h"
#include "../Ficha/Ficha.hpp"
#include "../Utils/Lista/LinkedList_T.hpp"
#include "../Jugador/Jugador.hpp"

#define CANT_MIN_JUGADORES 2
#define CANT_MAX_JUGADORES 5

#define DIM_MIN_X_Y 8
#define DIM_MIN_Z 6

#define STRING_BIENVENIDA "||||||||||------------ BATALLA DIGITAL V2.0 ------------||||||||||"
#define STRING_ALUMNO_1   "----------------- ALUMNO 1 -------- PADRON ALUMNO 1 --------------"
#define STRING_ALUMNO_2   "----------------- ALUMNO 2 -------- PADRON ALUMNO 2 --------------"
#define STRING_ALUMNO_3   "----------------- ALUMNO 3 -------- PADRON ALUMNO 3 --------------"
#define STRING_ALUMNO_4   "----------------- ALUMNO 4 -------- PADRON ALUMNO 4 --------------"
#define STRING_ALUMNO_5   "----------------- ALUMNO 5 -------- PADRON ALUMNO 5 --------------"
#define STRING_ALUMNO_6   "----------------- ALUMNO 6 -------- PADRON ALUMNO 6 --------------"

#define STRING_INGRESE_CANT_JUGADORES "Ingrese la cantidad de jugadores que jugaran Batalla Digital V2.0: "
#define STRING_ERROR_CANT "Error en el ingreso. Por favor ingrese un numero entero entre "

#define STRING_DIM_X "Ingrese la dimension del tablero en el eje X: "
#define STRING_DIM_Y "Ingrese la dimension del tablero en el eje Y: "
#define STRING_DIM_Z "Ingrese la dimension del tablero en el eje Z: "
#define STRING_ERROR_DIM "La dimension ingresada es incorrecta. Debe ser un numero entero mayor o igual a "

class BatallaDigital
{
    private:

        // La cantidad de jugadores que van a jugar
        unsigned int cantidadJugadores;

        // Dimensiones del tablero
        unsigned int dimensionesTablero [3];

        // Lista de jugadores
        Lista<Jugador*> * listaDeJugadores;
        // Puntero al tablero
        Tablero * tableroJuego;

    public:
        // Constructor
        // Pre: -
        // Pos: pregunta cantidad y genera una lista con la cantidad de jugadores
        //      pregunta dimensiones y genera un tablero y deja su puntero apuntando a él
        BatallaDigital();

        // Pre: -
        // Pos: imprime un mensaje de bienvenida
        void imprimirMensajeBienvenida();

        // Pre: se debe ingresar por consola el numero de jugadores que jugaran
        //		minimo y maximo en macros
        // Pos: carga el atributo de la clase
        void ingresarNumeroJugadores();

        // Pre: se deben ingresar por consola las dimensiones del tablero
        // 		minimo en macros
        // Pos: carga el atributo de la clase
        void ingresarDimensionesTablero();

        // Pre: -
        // Pos: crea un tablero con dimensiones especificadas y lo deja apuntado con el atributo de la clase
        void  crearTablero();

        // Pre: -
        // Pos: crea una lista con la cantidad de jugadores especificadas y la deja apuntada con el atributo de la clasee
        void crearListaJugadores();

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
