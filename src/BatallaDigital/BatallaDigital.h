#ifndef BATALLA_DIGITAL_H_
#define BATALLA_DIGITAL_H_

#include <cstddef>
#include "../Tablero/tablero.h"
#include "../Ficha/Ficha.h"
#include "../Utils/LinkedList_T.h"
#include "../Jugador/Jugador.h"

#define CANT_INICIAL_SOLDADOS_POR_JUGADOR 4

#define CANT_MIN_JUGADORES 2
#define CANT_MAX_JUGADORES 5

#define DIM_MIN_X_Y 8
#define DIM_MIN_Z 6

#define STRING_BIENVENIDA "||||||||||\t------------BATALLA DIGITAL V2.0------------\t||||||||||"
#define STRING_ALUMNO_1   "-----------------Abraham, Tomás\t\t\t-------- Padron 100770\t--------------"
#define STRING_ALUMNO_2   "-----------------Baratta, Facundo\t\t-------- Padron 104886\t--------------"
#define STRING_ALUMNO_3   "-----------------Chinuri, Christian Gabriel\t-------- Padron 90888\t--------------"
#define STRING_ALUMNO_4   "-----------------Lisdero Scaffino, Rafael\t-------- Padron 100871\t--------------"
#define STRING_ALUMNO_5   "-----------------Ponce, Santiago\t\t-------- Padron 101017\t--------------"

#define STRING_INGRESE_CANT_JUGADORES "Ingrese la cantidad de jugadores que jugaran Batalla Digital V2.0: "
#define STRING_ERROR_CANT "Error en el ingreso. Por favor ingrese un numero entero entre "

#define STRING_DIM_X "Ingrese la dimension del tablero en el eje X: "
#define STRING_DIM_Y "Ingrese la dimension del tablero en el eje Y: "
#define STRING_DIM_Z "Ingrese la dimension del tablero en el eje Z: "
#define STRING_ERROR_DIM "La dimension ingresada es incorrecta. Debe ser un numero entero mayor o igual a "

#define STRING_INGRESO_SOLDADO "Vas a agregar un soldado al mapa."
#define STRING_PEDIR_POS_X_SOLDADO "Ingresá la posición en X: "
#define STRING_PEDIR_POS_Y_SOLDADO "Ingresá la posición en Y: "

#define STRING_INGRESO_SOLDADO_CAS_NULO "Error casillero nulo."
#define STRING_INGRESO_SOLDADO_ERROR_DIMENSIONES "La coordenada ingresada no es parte del mapa."
#define STRING_INGRESO_SOLDADO_ERROR_OBSTACULO "No es posible posicionar un soldado en ese casillero porque está inactivo u ocupado."
#define STRING_INGRESO_SOLDADO_ERROR_AGUA "No es posible posicionar un soldado en ese casillero porque es del tipo agua."

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

        // Pre: -
        // Pos: crea una lista con la cantidad de jugadores especificadas y la deja apuntada con el atributo de la clasee
        void crearListaJugadores();

        // Pre: -
        // Pos: crea un tablero con dimensiones especificadas y lo deja apuntado con el atributo de la clase
        void crearTablero();

    public:
        // Constructor
        // Pre: -
        // Pos: pregunta cantidad y genera una lista con la cantidad de jugadores
        //      pregunta dimensiones y genera un tablero y deja su puntero apuntando a él
        BatallaDigital();

        //Otro constructor
        // Pre: recibe cantidad de jugadores y dimensiones del tablero
        // Pos: genera lista con jugadores con la cantidad recibida y un tablero con las dimensiones especificadas
        BatallaDigital(unsigned int cantidadJugadores,unsigned int dimX,unsigned int dimY,unsigned int dimZ);

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
        // Pos: muestra la geografía del tablero
        void mostrarGeografiaTablero();

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

        // Pre: recibe como argumentos el tipo de ficha y la posicion a vincular en el tablero
        // Pos: crea una ficha del tipo solicitado y la vincula con la posicion especificada del tablero
        Ficha * crearFicha(t_ficha tipoFicha, int x, int y, int z, int jugador);

        // Segunda implementacion, cambio la posicion del jugador por un puntero al jugador
        // Pre: recibe como argumentos el tipo de ficha y la posicion a vincular en el tablero
        // Pos: crea una ficha del tipo solicitado y la vincula con la posicion especificada del tablero
        Ficha * crearFicha(t_ficha tipoFicha, int x, int y, int z, Jugador * jugador);


        // Pre: recibe como argumentos una ficha, un tipo de movimiento y una cantidad de casilleros a mover
        // Pos: si la trayectoria es limpia la mueve
        //		si la trayectoria cae fuera del mapa avisa
        // 		si la trayectoria pasa por un tipo de terreno incompatible, avisa
        // 		si la trayectoria cruza por un campo con obstaculos, realiza alguna accion (explosion o lo que fuere)
        void moverFicha(Ficha * fichaMover , tipoMovimiento_t tipoMovimiento , int cantCasilleros);

        //Recibe un puntero al jugador que pone la mina, y una posicion en coordenadas x,y,z
        //Si la posicion es valida entonces coloca la mina. Una posicion es valida si el casillero esta activo
        //y el terreno es tierra
        void minarCasillero(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador);

        void avanzarTurno(Jugador * jugador);


        void iniciarJuego(void);

        // Pre: debe haber una lista de jugadores con sus respectivas fichas
        // Pos: devuelve true si hay solo un jugador con al menos una ficha 'soldado' activa.
        bool hayGanador();

        // Pre: -
        // Pos: pregunta por las fichas iniciales de los jugadores y las posiciona en el mapa
        void colocarFichasIniciales();

        // Pre: necesita un tipo de casillero para pedir en la coordenada
        // Pos: le pide al jugador una coordenada (X e Y) y valida que sea del tipo buscado
        //		retorna la coordenada que el jugador ingrese completando en Z con el nivel max de tierra
        Coordenada<int> pedirXYJugador(tipoCasillero_t tipoCasillero);

        
};


#endif
