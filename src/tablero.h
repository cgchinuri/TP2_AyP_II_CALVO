#ifndef TABLERO_H_
#define TABLERO_H_

#include "casillero.h"

class Tablero
{
	private:
		// Puntero al inicio del tablero, posicion 1,1,1
		Casillero * casilleroInicial;

		// Puntero al primer casillero de la lista de inactivos
		Casillero * listaCasillerosInactivos;

		int dimX;
		int dimY;
		int dimZ;

	public:
		// Constructor
		// Pre: -
		// Pos: genera el tablero con las dimensiones especificadas
		//		cada casillero tiene cargados sus parametros
		//		cada casillero esta enlazado con sus aledaños
		Tablero(int dimX, int dimY, int dimZ);

		// Pre: -
		// Pos: imprime el tablero por niveles
		void imprimirTablero();

		// Pre: -
		// Pos: recorre la lista de casilleros inactivos y les resta uno a todos
		//		saca un casillero de la lista si vuelve a estar activo
		//decrementarInactividad()

};


#endif
