#include "BatallaDigital.h"


BatallaDigital::BatallaDigital()
{
	this->tableroJuego = NULL;
	//this->dimensionesTablero = {0, 0, 0};
	this->cantidadJugadores = 0;

	this->listaDeJugadores = NULL;

	// Se imprime por consola el mensaje de bienvenida
	imprimirMensajeBienvenida();

	// Se solicita la cantidad de jugadores
	ingresarNumeroJugadores();

	// Se crea la lista de jugadores

	// Se solicita que se ingresen las dimensiones del tablero
	ingresarDimensionesTablero();

	// Se crea el tablero
	crearTablero();
}

void BatallaDigital::ingresarNumeroJugadores()
{
	int num = 0;

	while(num < CANT_MIN_JUGADORES || num > CANT_MAX_JUGADORES)
	{
		std::cout  << STRING_INGRESE_CANT_JUGADORES ;
		std::cin >> num ;
		std::cout  << std::endl;

		if(num < CANT_MIN_JUGADORES || num > CANT_MAX_JUGADORES)
		{
			std::cout  << STRING_ERROR_CANT << CANT_MIN_JUGADORES <<" y " << CANT_MAX_JUGADORES << std::endl;
		}
	}

	this->cantidadJugadores = (unsigned int)num;


}

void BatallaDigital::ingresarDimensionesTablero()
{
	int num = 0;

	while(num < DIM_MIN_X_Y)
	{
		std::cout  << STRING_DIM_X ;
		std::cin >> num ;
		std::cout  << std::endl;

		if(num < DIM_MIN_X_Y)
		{
			std::cout  << STRING_ERROR_DIM << DIM_MIN_X_Y << std:: endl;
		}
	}

	this->dimensionesTablero[0] = (unsigned int)num ;
	num = 0;

	while(num < DIM_MIN_X_Y)
	{
		std::cout  << STRING_DIM_Y ;
		std::cin >> num ;
		std::cout  << std::endl;

		if(num < DIM_MIN_X_Y)
		{
			std::cout  << STRING_ERROR_DIM << DIM_MIN_X_Y << std:: endl;
		}
	}

	this->dimensionesTablero[1] = (unsigned int)num ;
	num = 0;

	while(num < DIM_MIN_Z)
	{
		std::cout  << STRING_DIM_Z ;
		std::cin >> num ;
		std::cout  << std::endl;

		if(num < DIM_MIN_Z)
		{
			std::cout  << STRING_ERROR_DIM << DIM_MIN_Z << std:: endl;
		}
	}

	this->dimensionesTablero[2] = (unsigned int)num ;


}

void BatallaDigital::crearTablero()
{
	// 1 generacion del tablero
	tableroJuego = new Tablero(this->dimensionesTablero[0],this->dimensionesTablero[1],this->dimensionesTablero[2]);

	std::cout << "Se generó un tablero con dimensiones (" << this->dimensionesTablero[0] <<", " << this->dimensionesTablero[1] << ", " << this->dimensionesTablero[2] <<")" << std::endl;

}

void BatallaDigital::crearListaJugadores()
{
	// 2 generacion lista jugadores
	this->listaDeJugadores = new Lista<Jugador*>();

	for(int i = 0; i < this->cantidadJugadores; i++){
		int aux = i + 1;
		std::string nombre = "Jugador " + std::to_string(aux);
		Jugador* jugador = new Jugador(i+1, nombre);
		this->listaDeJugadores->agregar(jugador);
	}
}

void BatallaDigital::imprimirMensajeBienvenida()
{
	std::cout <<  STRING_BIENVENIDA << std::endl;
	std::cout <<  STRING_ALUMNO_1 << std::endl;
	std::cout <<  STRING_ALUMNO_2 << std::endl;
	std::cout <<  STRING_ALUMNO_3 << std::endl;
	std::cout <<  STRING_ALUMNO_4 << std::endl;
	std::cout <<  STRING_ALUMNO_5 << std::endl;
	std::cout <<  STRING_ALUMNO_6 << std::endl;
}


void BatallaDigital::vincularFichaYCasillero(Casillero * casillero , Ficha * ficha)
{
	casillero->setFichaCasillero(ficha);
	ficha->setCasilleroFicha(casillero);
}

void BatallaDigital::desvincularFicha(Ficha * ficha)
{
	ficha->desvincularFichaDeCasillero();
}


void desvincularCasillero(Casillero * casillero)
{
	casillero->vaciarCasillero();
}
