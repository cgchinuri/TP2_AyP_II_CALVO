#ifndef TABLERO_H_
#define TABLERO_H_

#include "casillero.h"
#include "lista.h"

class Tablero
{
	private:
		// Tablero
		// Es una lista de listas de listas a casillero, que forman un tablero 3D
		Lista<Lista<Lista<Casillero*>*>*>* tableroJuego;

		// Lista de casilleros inactivos
		Lista<Casillero*>* listaCasillerosInactivos;

		// Pre: debe haber un tablero creado
		// Pos: vincula todos los casilleros del tablero con sus aledaños
		void vincularTablero();

		// Pre: debe haber un tablero creado
		//		recibe como argumento el nivel a vincular
		// Pos: vincula los casilleros de un mismo nivel
		//		llena los punteros antX, sigX, antY, sigY con los casilleros aledaños
		void vincularNivelTablero(int nivel);

		// Pre: debe haber un tablero creado
		// Pos: vincula los casilleros de un nivel con los de los niveles aledaños
		//		llena los punteros antZ y sigZ con los casilleros inferiores y superiores
		void vincularPisosTablero();
		
		// Dimensiones del tablero
		int dimX;
		int dimY;
		int dimZ;

	public:
		// Constructor
		// Pre: ingresar las dimensiones del tablero, numeros positivos, minimo [completar con dim min]
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


		// Función que chequea todas las filas del tablero por si tienen vínculos
		bool chequearVinculosPisosTablero();

		// Pre: insertar por argumentos las coordenadas del casillero buscado
		// Pos: devuelve un puntero a un casillero si está dentro de las dimensiones del tablero
		//		devuelve null si no está dentro de las dimensiones del tablero
		Casillero * obtenerCasillero(int x, int y, int z);

		// Destructor
		~Tablero();

};


#endif
