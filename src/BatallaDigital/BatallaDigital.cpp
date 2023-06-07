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

//Constructor de batalla digital con parametros
BatallaDigital::BatallaDigital(unsigned int cantidadJugadores,unsigned int dimX,unsigned int dimY,unsigned int dimZ){
	
	if(cantidadJugadores>CANT_MAX_JUGADORES || cantidadJugadores<CANT_MIN_JUGADORES)	{
        throw "La cantidad de jugadores no es valida";
	}
	
	this->cantidadJugadores=cantidadJugadores;
	this->tableroJuego=new Tablero(dimX,dimY,dimZ);
	this->listaDeJugadores=new Lista<Jugador*>();

	//Esto, construir la lista de jugadores, puede ir en una funcion privada.
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

	for(unsigned int i = 0; i < this->cantidadJugadores; i++)
	{
		int aux = i + 1;
		std::string nombre = "Jugador " + aux;//FALTA ACA LO DEL ID DEL JUGADOR
		Jugador* jugador = new Jugador(i+1, nombre);
		this->listaDeJugadores->add(jugador);
	}
	std::cout << "Se generó una lista de "<< this->listaDeJugadores->contarElementos()<< " jugadores" << std::endl;
}

void BatallaDigital::imprimirMensajeBienvenida()
{
	std::cout <<  STRING_BIENVENIDA << std::endl;
	std::cout <<  STRING_ALUMNO_1 << std::endl;
	std::cout <<  STRING_ALUMNO_2 << std::endl;
	std::cout <<  STRING_ALUMNO_3 << std::endl;
	std::cout <<  STRING_ALUMNO_4 << std::endl;
	std::cout <<  STRING_ALUMNO_5 << std::endl;
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


Ficha * BatallaDigital::crearFicha(t_ficha tipoFicha, int x, int y, int z, int jugador)
{
	Ficha * nuevaFicha = new Ficha(tipoFicha, x, y , z);
	Casillero * casilleroVinculacion = this->tableroJuego->obtenerCasillero(x,y,z);

	vincularFichaYCasillero(casilleroVinculacion, nuevaFicha);

	this->listaDeJugadores->reiniciarCursor();
	while(listaDeJugadores->avanzarCursor())
	{
		Jugador* cursorJugador = listaDeJugadores->getCursor();
		if(cursorJugador->identificador()==jugador)
		{
			cursorJugador->agregarFicha(nuevaFicha);
		}
	}
	return nuevaFicha;

}

Ficha * BatallaDigital::crearFicha(t_ficha tipoFicha, int x, int y, int z, Jugador * jugador)
{
	Ficha * nuevaFicha = new Ficha(tipoFicha, x, y , z);
	Casillero * casilleroVinculacion = this->tableroJuego->obtenerCasillero(x,y,z);

	vincularFichaYCasillero(casilleroVinculacion, nuevaFicha);


	jugador->agregarFicha(nuevaFicha);

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
	else if(!casilleroDestino->estaActivo())
	{
		// Si el casillero esta inactivo no puedo hacer el movimiento
		std::cout << "Casillero inactivo en la trayectoria" << std::endl;
	}
	else if(casilleroDestino->estaOcupado())
	{
		// Si el casillero esta ocupado hay que tomar alguna accion pero no se puede completar el movimiento
		std::cout << "Casillero ocupado en la trayectoria" << std::endl;


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

//Deberia chequear el estado del casillero a minar: Si esta minado, explota? Si hay un jugador lo mata
//si esta envenenado? Si esta inactivo .... etc.
void BatallaDigital::minarCasillero(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador) {

	Casillero * objetivo= this->tableroJuego->obtenerCasillero(x,y,z);
	
	if(!objetivo->estaActivo()){
        throw "El casillero esta inactivo";
	}

	if(objetivo->getTipoCasillero()!=tierra)	{
		 throw "Solo se puede minar un casillero de tipo tierra";
	}

	if(objetivo->estaOcupado()){
		Ficha * fichaOcupante=objetivo->getFichaCasillero();
		/*
		opcion1 si las fichas tienen un id de a que jugador pertenece
		Jugador * jugadorOcupante=NULL;
		int idJugador= fichaOcupante->getDueño();
		
		while(this->listaDeJugadores->avanzarCursor())	{
			if(this->listaDeJugadores->getCursor()->identificador()==idJugador)	{
				jugadorOcupante=this->listaDeJugadores->getCursor();
				this->listaDeJugadores->reiniciarCursor();
				break;
			}
		}
		*/
		//Opcion 2:si no tengo el id de jugador en la ficha :Recorrer la lista de jugadores, para cada jugador recorrer la lista de sus fichas... un poco feo
	
		while(this->listaDeJugadores->avanzarCursor())	{
			if(this->listaDeJugadores->getCursor()->eliminarFicha(*objetivo->getCoordenada())==true)	{
				this->listaDeJugadores->reiniciarCursor();
				break;
			}
		}


		objetivo->vaciarCasillero();
		//objetivo->desactivar();//primitiva para inactivar un casillero cuando una mina explota
	}	else {
		
		Ficha * mina=new Ficha(FICHA_MINA,x,y,z);
		objetivo->setFichaCasillero(mina);
		mina->setCasilleroFicha(objetivo);
		jugador->agregarFicha(mina);
	}
	return;
}

bool BatallaDigital::hayGanador()
{
	this->listaDeJugadores->reiniciarCursor();
	int jugadoresConSoldados=0;
	while(listaDeJugadores->avanzarCursor())
	{
		Jugador * Jugador = listaDeJugadores->getCursor();
		if (Jugador->cantidadFichasSoldado()>0)
		{
			jugadoresConSoldados++;
		}
	}

	if (jugadoresConSoldados==1)
	{
		return true;
	}
	return false;
}

void BatallaDigital::avanzarTurno(Jugador * jugador)
{
		//Variables para el turno
		int x,y,z=0;
		bool mover,jugarCarta=false;
		int indice=1;

		//Comienzo preguntando dónde quiere minar el jugador
		std::string stringCoordenada;
		getline(std::cin, stringCoordenada);
		minarCasillero(x,y,z,jugador);

		//Le pregunto si quiere mover
		//mover= jugadorQuiereMover();
		if(mover==true)
		{
			//MUESTRO SUS FICHAS
			jugador->mostrarFichas();

			//LE PREGUNTO CUAL QUIERE MOVER
			Ficha * ficha=jugador->obtenerFicha(indice);

			//LA MUEVO
			// moverFicha();  esta podría ser la función general y las de arriba las subfunciones
		}
		// SI MOVIO GESTIONO EVENTOS
		// explotarMina(); ?
		// matarSoldado(); ?
		// matarOtraFicha(); ?
		// limpiarFichasInactivas(); ?


		//Le pregunto si quiere jugar una carta
		//jugarCarta = jugadorQuiereUsarCarta();
		if(jugarCarta==true)
		{

			//POSIBLES EVENTOS SEGUN LA CARTA USADA

			//ataqueQuimico();

			//avionDeCombate();

			// algun otro??

			return;
		}
		// SI SE USO CARTA GESTIONO EVENTOS



		//UNA VEZ PASA TODO ESTO, ACTUALIZO EL TABLERO y FICHAS
		//actualizarTablero();
		//decrementarInactividadCasilleros();
		//mostrarTablero();
	
}

void BatallaDigital::iniciarJuego(void)	{
	//posicionarSoldados();//Funcion que posiciona los soldados al inicio del juego para cada jugador

	while(!hayGanador())	{

		listaDeJugadores->reiniciarCursor();	

		while(listaDeJugadores->avanzarCursor())	{
			//mostrarTablero(listaDeJugadores->getCursor());//mostrar el tablero al jugador
			avanzarTurno(listaDeJugadores->getCursor());
		}

	}

}

void BatallaDigital::mostrarGeografiaTablero()
{
	this->tableroJuego->imprimirGeografia();
}

Coordenada<int> BatallaDigital::pedirXYJugador(tipoCasillero_t tipoCasillero)
{
	// Coordenadas X e Y
	int x, y = 0;

	bool coordenadaOK = false;
	bool casilleroOK = false;

	Casillero * casilleroResultante = NULL;

	while(!casilleroOK)
	{
		coordenadaOK = false ;
		casilleroOK = false ;

		// Ingreso de la coordenada X
		while(!coordenadaOK)
		{
			std::cout << STRING_PEDIR_POS_X_SOLDADO ;
			std::cin >> x ;


			if(x < 1 || x > this->dimensionesTablero[0])
			{
				// Si fue ingresada una posicion externa a las dimensiones del mapa
				std::cout << STRING_INGRESO_SOLDADO_ERROR_DIMENSIONES << std::endl;
			}
			else
			{
				// Hacer la asignacion en la coordenada
				coordenadaOK = true;
			}
		}

		coordenadaOK = false;

		// Ingreso de la coordenada Y
		while(!coordenadaOK)
		{
			std::cout << STRING_PEDIR_POS_Y_SOLDADO ;
			std::cin >> y ;


			if(y < 1 || y > this->dimensionesTablero[1])
			{
				// Si fue ingresada una posicion externa a las dimensiones del mapa
				std::cout << STRING_INGRESO_SOLDADO_ERROR_DIMENSIONES << std::endl;
			}
			else
			{
				// Hacer la asignacion en la coordenada
				coordenadaOK = true;
			}
		}

		casilleroResultante = this->tableroJuego->obtenerCasillero(x,y,NIVEL_MAXIMO_TIERRA);


		if(!casilleroResultante)
		{
			// Si el casillero es nulo informo
			std::cout << STRING_INGRESO_SOLDADO_CAS_NULO << std::endl;
		}
		else if(casilleroResultante->getTipoCasillero()!=tipoCasillero)
		{
			// Si el casillero no es del tipo esperado informo
			std::cout << STRING_INGRESO_SOLDADO_ERROR_AGUA << std::endl;
		}
		else if(casilleroResultante->estaOcupado())
		{
			// Si el casillero está ocupado lo informo
			std::cout << STRING_INGRESO_SOLDADO_ERROR_OBSTACULO << std::endl;
		}
		else
		{
			// Si llegué acá el casillero sirve para poner el soldado
			casilleroOK = true;
		}
	}

	// Genero y retorno la coordenada
	Coordenada<int> coordenada(x,y,NIVEL_MAXIMO_TIERRA);

	return coordenada;
}

void BatallaDigital::colocarFichasIniciales()
{
	// Punteros aux
	Ficha * fichaAux=NULL;
	Casillero * casilleroAux = NULL;

	// Inicializo lista de jugadores
	this->listaDeJugadores->reiniciarCursor();

	// Recorro la lista de jugadores
	while(this->listaDeJugadores->avanzarCursor())
	{
		// ¡¡ Imprimir nombre del jugador !!

		for(int i = 0 ; i < CANT_INICIAL_SOLDADOS_POR_JUGADOR ; i++)
		{
			std::cout << STRING_INGRESO_SOLDADO << std::endl;

			Coordenada<int> coordenada = pedirXYJugador(tierra);

			fichaAux = crearFicha(FICHA_SOLDADO, coordenada.obtenerX(), coordenada.obtenerY(), coordenada.obtenerZ(), this->listaDeJugadores->getCursor());

			casilleroAux = fichaAux->getCasilleroFicha();

			// Para verificar
			std::cout << "Ficha agregada a casillero: " ;
			casilleroAux->imprimirPos();
		}

	}

}

