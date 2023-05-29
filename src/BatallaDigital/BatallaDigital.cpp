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
	crearListaJugadores();

	// Se solicita que se ingresen las dimensiones del tablero
	ingresarDimensionesTablero();

	// Se crea el tablero
	crearTablero();
}


BatallaDigital::BatallaDigital(unsigned int cantidadJugadores,unsigned int dimX,unsigned int dimY,unsigned int dimZ){
	
	if(cantidadJugadores>CANT_MAX_JUGADORES || cantidadJugadores<CANT_MIN_JUGADORES)	{
        throw std::invalid_argument("La cantidad de jugadores no es valida");
	}
	
	this->cantidadJugadores=cantidadJugadores;
	this->tableroJuego=new Tablero(dimX,dimY,dimZ);
	this->listaDeJugadores=new Lista<Jugador*>();

	for(size_t i=0;	i<cantidadJugadores;i++){
		std::ostringstream oss;
		oss<<"Jugador"<<i+1;	//HARDCODEO
		std::string aux=oss.str();
		Jugador * nuevoJugador=new Jugador(i+1,aux);
		this->listaDeJugadores->add(nuevoJugador);
		oss.clear();
	}


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
	// generacion del tablero
	tableroJuego = new Tablero(this->dimensionesTablero[0],this->dimensionesTablero[1],this->dimensionesTablero[2]);

	std::cout << "Se generó un tablero con dimensiones (" << this->dimensionesTablero[0] <<", " << this->dimensionesTablero[1] << ", " << this->dimensionesTablero[2] <<")" << std::endl;

}

void BatallaDigital::crearListaJugadores()
{
	// generacion lista jugadores
	this->listaDeJugadores = new Lista<Jugador*>();

	for(unsigned int i = 0; i < this->cantidadJugadores; i++){
		int aux = i + 1;
		std::string nombre = "Jugador " + aux;//FALTA ACA LO DEL ID DEL JUGADOR
		Jugador* jugador = new Jugador(i+1, nombre);
		this->listaDeJugadores->add(jugador);
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


Ficha * BatallaDigital::crearFicha(t_ficha tipoFicha, int x, int y, int z)
{

	Ficha * nuevaFicha = new Ficha(tipoFicha, x, y , z);
	Casillero * casilleroVinculacion = this->tableroJuego->obtenerCasillero(x,y,z);

	vincularFichaYCasillero(casilleroVinculacion, nuevaFicha);

	// No estaría mal agregar la ficha a la lista de fichas del jugador antes de terminar la función


	return nuevaFicha;

}


void BatallaDigital::moverFicha(Ficha * fichaMover , tipoMovimiento_t tipoMovimiento , int cantCasilleros)
{
	// Casillero de inicio de la trayectoria
	Casillero * casilleroInicio = fichaMover->getCasilleroFicha();

	// Casillero destino de la trayectoria
	// Llamo a la funcion de tablero que navega por si mismo encontrando obstaculos o cambio de terreno
	Casillero * casilleroDestino = this->tableroJuego->navegarTablero(casilleroInicio, tipoMovimiento, cantCasilleros);


	if(!casilleroDestino)
	{
		// Si el casillero destino es null entonces me fui del mapa
		std::cout << "Error fuera de mapa" << std::endl;
	}
	else if (casilleroInicio->getTipoCasillero() != casilleroDestino->getTipoCasillero())
	{
		// Si hay cambio de terreno no puedo mover
		std::cout << "Error distinto terreno" << std::endl;
	}
	else if(casilleroDestino->estaOcupado())
	{
		// Si el casillero esta ocupado hay que tomar alguna accion pero no se puede completar el movimiento
		std::cout << "Casillero de destino ocupado" << std::endl;


		// Aca tenemos que hacer la logica de explosion o lo que fuere


	}
	else
	{
		// Si no se cumplen las condiciones anteriores entonces puedo mover la ficha

		// Desvinculo ficha y casillero anterior
		fichaMover->desvincularFichaDeCasillero();
		casilleroInicio->vaciarCasillero();

		// Vinculo ficha y casillero destino
		vincularFichaYCasillero(casilleroDestino, fichaMover);
	}
}
