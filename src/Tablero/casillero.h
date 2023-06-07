#ifndef CASILLERO_H_
#define CASILLERO_H_

#include "../Utils/Coordenada.h"

const int MAX_CANTIDAD_TURNOS_INACTIVO=10;

typedef enum
{
	tierra, // Deberia ser todo mayuscula
	agua,
	aire
}tipoCasillero_t;

// Declaro la clase ficha que está descripta e implementada en Ficha.h y Ficha.cpp
class Ficha;


class Casillero
{
	private:
		// Atributos de posción (reemplazado por tda coordenada)
		int x;
		int y;
		int z;

		// Puntero a TDA coordenada
		Coordenada<int> * coordenada;

		// Punteros a casilleros aledaños
		Casillero * sigX;
		Casillero * antX;
		Casillero * sigY;
		Casillero * antY;
		Casillero * sigZ;
		Casillero * antZ;

		// Tipo del casillero
		tipoCasillero_t tipoCasillero;

		// Turnos de inactividad restantes
		int turnosInactivoRestantes;

		// Puntero a la ficha que va a estar ocupando el casillero
		Ficha * fichaOcupa ;

	public:
		// Constructor
		// Pre: recibe como argumento la posición y el tipo de casillero
		// Pos: crea el casillero, inicializa los punteros a null
		Casillero(int x, int y, int z, tipoCasillero_t tipoCasillero);

		// Pre: -
		// Pos: devuelve la posición en X
		int getPosX();
		// Pre: -
		// Pos: devuelve la posición en Y
		int getPosY();
		// Pre: -
		// Pos: devuelve la posición en Z
		int getPosZ();

		// Pre: -
		// Pos: devuelve puntero a su TDA coordenada
		Coordenada<int> * getCoordenada(void);

		// Pre: -
		// Pos: imprime la posicion del casillero
		void imprimirPos();

		// Pre: -
		// Pos: imprime el tipo del casillero
		void imprimirTipo();

		// Pre: -
		// Pos: devuelve el tipo de casillero
		tipoCasillero_t getTipoCasillero();

		// Pre: -
		// Pos: edita el tipo de casillero
		void setTipoCasillero(tipoCasillero_t tipo);

		// Pre: hay que pasarle un puntero a casillero
		// Pos: queda apuntando a ese casillero como siguiente en X
		void setSigX(Casillero * casillero);

		// Pre: hay que pasarle un puntero a casillero
		// Pos: queda apuntando a ese casillero como anterior en X
		void setAntX(Casillero * casillero);

		// Pre: hay que pasarle un puntero a casillero
		// Pos: queda apuntando a ese casillero como siguiente en Y
		void setSigY(Casillero * casillero);

		// Pre: hay que pasarle un puntero a casillero
		// Pos: queda apuntando a ese casillero como anterior en Y
		void setAntY(Casillero * casillero);

		// Pre: hay que pasarle un puntero a casillero
		// Pos: queda apuntando a ese casillero como siguiente en Z
		void setSigZ(Casillero * casillero);

		// Pre: hay que pasarle un puntero a casillero
		// Pos: queda apuntando a ese casillero como anterior en Z
		void setAntZ(Casillero * casillero);

		// Pre: -
		// Pos: devuelve el puntero al casillero siguiente en x
		Casillero * getSigX();

		// Pre: -
		// Pos: devuelve el puntero al casillero anterior en x
		Casillero * getAntX();

		// Pre: -
		// Pos: devuelve el puntero al casillero siguiente en Y
		Casillero * getSigY();

		// Pre: -
		// Pos: devuelve el puntero al casillero anterior en Y
		Casillero * getAntY();

		// Pre: -
		// Pos: devuelve el puntero al casillero siguiente en Z
		Casillero * getSigZ();

		// Pre: -
		// Pos: devuelve el puntero al casillero anterior en Z
		Casillero * getAntZ();


		// Pre: -
		// Pos: apunta a NULL el puntero a ficha que ocupa al casillero
		void vaciarCasillero();

		// Pre: recibe como argumento un puntero a una ficha
		// Pos: cambia la dirección a donde apunta el casillero en su parámetro fichaOcupa
		void setFichaCasillero(Ficha * fichaOcupa);

		// Pre: -
		// Pos: devuelve la dirección de memoria de la ficha donde apunta el casillero
		//		o NULL si es nula
		Ficha * getFichaCasillero();

		// Pre: -
		// Pos: retorna true si el puntero a ficha del casillero está apuntando a algo
		//		retorna false si el puntero a ficha del casillero está apuntando a null
		bool estaOcupado();
		
		// Pre: -
		// Pos: retorna true si el casillero está activo, false en caso contrario
		bool estaActivo(void);

		//Pos: Desactiva el casillero
		void desactivar(void);

		void decrementarInactividad(void);

		// Pre: recibe un puntero a un casillero con vínculos a los casilleros adyacentes del mismo piso
		// Pos: retorna la cantidad de casilleros con agua adyacentes al casillero recibido
		int casillerosAguaAdyacentes(Casillero* casilleroActual);

		// Destructor
		~Casillero();

};

#endif // CASILLERO_H_
