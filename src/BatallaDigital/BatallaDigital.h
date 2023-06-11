#ifndef BATALLA_DIGITAL_H_
#define BATALLA_DIGITAL_H_

#include <cstddef>
#include "../Tablero/tablero.h"
#include "../Ficha/Ficha.h"
#include "../Utils/LinkedList_T.h"
#include "../Jugador/Jugador.h"
#include "../Utils/TipoMovimiento.h"
#include "../Utils/Bitmap/BitmapBatallaDigital.h"

#define CANT_INICIAL_SOLDADOS_POR_JUGADOR 1

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

#define STRING_INGRESO_COORDENADA_ERROR_DIMENSIONES "La coordenada ingresada es inválida."

#define STRING_INGRESO_SOLDADO_CAS_NULO "Error casillero nulo."
#define STRING_INGRESO_SOLDADO_ERROR_OBSTACULO "No es posible posicionar un soldado en ese casillero porque está inactivo u ocupado."
#define STRING_INGRESO_SOLDADO_ERROR_AGUA "No es posible posicionar un soldado en ese casillero porque es del tipo agua."

#define STRING_INGRESO_MINA_ERROR_AGUA "El casillero que se intentó minar es del tipo agua. "
#define STRING_INGRESO_MINA_ERROR_AIRE "El casillero que se intentó minar es del tipo aire. "

#define STRING_INGRESO_MINA_ERROR_CAS_INACTIVO "El casillero que se intentó minar se encuentra inactivo."



#define STRING_TURNO_DE_P1 " - - - - - - - - - - - Es el turno de: "
#define STRING_TURNO_DE_P2 ".  - - - - - - - - - - -"

#define RADIO_EXPLOSION_POR_CHOQUE_SOLDADOS 1
#define RADIO_EXPLOSION_POR_CHOQUE_MINA_SOLDADO 2
#define RADIO_EXPLOSION_POR_CHOQUE_MINAS 3

#define TURNOS_INACTIVIDAD_POR_EXPLOSION_SOLDADOS 3
#define TURNOS_INACTIVIDAD_POR_EXPLOSION_MINA_SOLDADO 4
#define TURNOS_INACTIVIDAD_POR_EXPLOSION_MINAS 5

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

        // Puntero a la instancia de logica de bitmap
        BitmapBatallaDigital *bitmap;

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

        // Pre: recibe una  frase para imprimir por consola
        // Pos: imprime la frase por consola y recibe una entrada por cin
        //		devuelve -1 si es errónea o el numero entero positivo si está ok
        int ingresoNumeroEnteroPositivoConsola(std::string oracionPedido);

        // Pre: -
        // Pos: imprime un mensaje de bienvenida
        void imprimirMensajeBienvenida();

        // Pre: se debe ingresar por consola el numero de jugadores que jugaran
        //		minimo y maximo en macros
        // Pos: carga el atributo de la clase
        void ingresarNumeroJugadores();

        // Pre: debe haber una lista de jugadores creada
        // Pos: devuelve el primer elemento de la lista
        Jugador * obtenerPrimerJugador();

        // Pre: debe haber una lista de jugadores creada
        // Pos: devuelve el elemento siguiente relativo al ID que se envió, o el primero si estaba en el último
        Jugador * obtenerSiguienteJugador(int identificadorJugadorAnterior);

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
        //      devuelve true si se pudo hacer el movimiento y false si se dio alguno de los casos anteriores
        bool moverFicha(Ficha * fichaMover , tipoMovimiento_t tipoMovimiento , unsigned int cantCasilleros);

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

        // Pre: debe existir un juego iniciado con un tablero y la geografía que éste posea
        //      recibe el jugador que puede ver el tablero o toma por defecto que se muestra todo
        // Pos: genera un bitmap por cada nivel del tablero mostrando las fichas y geografía del jugador que corresponda o todo el tablero
        void mostrarTablero(Jugador *jugador);

        // Pre: debe existir un juego iniciado con una cantidad dada de jugadores
        // Pos: devuelve la cantidad de jugadores del juego
        unsigned int cantidadDeJugadores();

        // Pre: debe existir un juego iniciado y una lista de jugadores
        // Pos: devuelve el número del jugador correspondiente en dicha lista
        Jugador * obtenerJugadorNumero(unsigned int jugador);

        // Pre: recibe el casillero a desactivar y los turnos de inactividad para configurar
        // Pos: desactiva el casillero con los turnos que se pasan como parametro, ademas si tuviera alguna ficha en el la desactiva
        void desactivarCasillero(Casillero * casillero , int turnosInactividad);

        // Pre: recibe como argumentos un puntero a un casillero, una cantidad de turnos inactivo para el casillero central (min 3)
        //      y el radio que tendrá la explosión (entre 1 y 3)
        // Pos: desactiva el casillero indicado con los turnos de inactividad especificados.
        //      desactiva los casilleros que lo rodean, tantos como indique el radio de explosión
        //      va decrementando un turno de inactividad por capa
        //      desactiva fichas involucradas
        void explosionEnTablero (Casillero * casilleroCentral , int turnosInactividadEpicentro , int radioExplosion );


        // Recibe un puntero al casillero a minar y otro al jugador dueño de la mina
        // Coloca la mina si el casillero estaba vacio o genera una explosión si había algo en él
        void minarCasillero(Casillero * casillero ,Jugador * jugador);


        // Pre: -
        // Post: devuelve true si el jugador ingreso por consola una respuesta afirmativa, de lo contrario devuelve false
        bool jugadorQuiereMover();

        // Pre: -
        // Post: devuelve true si el jugador ingreso por consola una respuesta afirmativa, de lo contrario devuelve false
        bool jugadorQuiereUsarCarta();

        // Pre: -
        // Post: pregunta al usuario por un tipo de movimiento, devolviendolo si el input es válido
        tipoMovimiento_t obtenerMovimiento();

        // Pre: -
        // Pos: pregunta al usuario la cantidad de casilleros a mover, devolvíendolo si el input es válido
        int obtenerCantidadCasilleros();

        //Pre: El jugador no puede ser nulo
        //Post:Se ejecuta un turno en el juego
        void avanzarTurno(Jugador * jugador);


        //Pre: Jugador y avionRadar no pueden ser nulos
        //Post:Retorna una lista de casilleros donde se detectaron enemigos
        Lista<Casillero *> * EscanearTerreno(Jugador * jugador,Ficha * avionRadar);

        //Pre: Recibe una coordenada x y z
        //Post:Si la coordenada es valida para las dimensiones del tablero retorna true
        //MetodoPrivado
        bool _esPosicionValida(int x,int y, int z);

        //Pre: -
        //Pos: valida la coordena a ingresar por el usuario
        void validarCoordenada(Coordenada<int>* &objetivo);

        // Pre: recibe como argumento un puntero a un jugador
        // Pos: imprime por consola un mensaje indicando que es su turno
        void imprimirTurnoDe(Jugador * jugador);

        //Recibe un puntero al jugador que ubica el barco, y una posicion en coordenadas x,y,z
        //Si la posicion es valida entonces coloca el barco. Una posicion es valida si el casillero esta activo
        //y el terreno es agua
        void ubicarBarco(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador);

        //Pre: recibe como parametro el id del jugador que va a jugar la carta
        //Pos: juega la carta barco, puede disparar un misil o un torpedo
        //     misil puede eliminar un aviones, barcos o soldados esten atrincherados o no
        //     torpedo puede eliminar solo submarinos
        void jugarCartaBarco(unsigned int idJugador);

        //Recibe un puntero al jugador que ubica el avion, y una posicion en coordenadas x,y,z
        //Si la posicion es valida entonces coloca el avion. Una posicion es valida si el casillero esta activo
        //y el terreno es aire
        void ubicarAvion(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador);

        //Pre: recibe como parametro el id del jugador que va a jugar la carta
        //Pos: juega la carta avion, puede disparar un misil o un torpedo
        //     misil puede eliminar un aviones, barcos o soldados esten atrincherados o no
        //     torpedo puede eliminar solo submarinos
        void jugarCartaAvion(unsigned int idJugador);

        //Recibe un puntero al jugador que ubica el submarino, y una posicion en coordenadas x,y,z
        //Si la posicion es valida entonces coloca el submarino. Una posicion es valida si el casillero esta activo
        //y el terreno es agua
        void ubicarSubmarino(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador);

        //Pre: recibe como parametro el id del jugador que va a jugar la carta
        //Pos: juega la carta submarino, puede disparar un torpedo
        //     torpedo puede eliminar solo submarinos o barcos
        void jugarCartaSubmarino(unsigned int idJugador);

        //Recibe un puntero al jugador que ubica el refuerzo, y una posicion en coordenadas x,y,z
        //Si la posicion es valida entonces coloca el refuerzo. Una posicion es valida si el casillero esta activo
        //y el terreno es tierra
        void ubicarRefuerzoSoldado(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador);

        //Pre: recibe como parametro el id del jugador que va a jugar la carta
        //Pos: juega la carta refuerzo, agrega un refuerzo al jugador
        void jugarCartaRefuerzoSoldado(unsigned int idJugador);

        //Pre: recibe como parametro el id del jugador que va a jugar la carta
        //Pos: juega la carta trinchera, atrinchera un soldado
        void jugarCartaTrinchera(unsigned int idJugador);

};


#endif
