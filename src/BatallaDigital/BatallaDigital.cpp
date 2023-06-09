#include "BatallaDigital.h"


BatallaDigital::BatallaDigital()
{
	this->tableroJuego = NULL;
	this->cantidadJugadores = 0;
	this->listaDeJugadores = NULL;
	this->cartasDisponibles=new Mazo<CartaBatallaDigital *>();
	this->cartasJugadas=new Mazo<CartaBatallaDigital *>();

	// Se imprime por consola el mensaje de bienvenida
	imprimirMensajeBienvenida();

	//se crea el mazo de cartas con una cantidad definida en la configuracion del juego
	construirMazo(CANTIDAD_CARTAS_MAZO);

	// Se solicita la cantidad de jugadores
	ingresarNumeroJugadores();

	// Se crea la lista de jugadores
	crearListaJugadores();

	// Se solicita que se ingresen las dimensiones del tablero
	ingresarDimensionesTablero();

	// Se crea el tablero
	crearTablero();

	// Debugging
	//this->tableroJuego->imprimirTablero();

	// Se crea la instancia de logica de bitmap
	this->bitmap = new BitmapBatallaDigital(this->dimensionesTablero[0], this->dimensionesTablero[1]);
}

BatallaDigital::~BatallaDigital(void)
{
	delete this->tableroJuego;
	delete this->listaDeJugadores;
	delete this->cartasDisponibles;
	delete this->cartasJugadas;
	delete this->bitmap;
}

//Constructor de batalla digital con parametros
BatallaDigital::BatallaDigital(unsigned int cantidadJugadores,unsigned int dimX,unsigned int dimY,unsigned int dimZ){
	
	if(cantidadJugadores>CANT_MAX_JUGADORES || cantidadJugadores<CANT_MIN_JUGADORES)	{
        throw "La cantidad de jugadores no es valida";
	}
	
	this->cantidadJugadores=cantidadJugadores;
	this->tableroJuego=new Tablero(dimX,dimY,dimZ);
	this->listaDeJugadores=new Lista<Jugador*>();
	this->cartasDisponibles=new Mazo<CartaBatallaDigital *>();
	this->cartasJugadas=new Mazo<CartaBatallaDigital *>();




	for(size_t i=0;	i<cantidadJugadores;i++){
		std::ostringstream oss;
		oss<<"Jugador"<<i+1;
		std::string aux=oss.str();
		Jugador * nuevoJugador=new Jugador(i+1,aux);
		this->listaDeJugadores->add(nuevoJugador);
		oss.clear();
	}

	this->bitmap = new BitmapBatallaDigital(dimX, dimY);


}

int BatallaDigital::ingresoNumeroEnteroPositivoConsola(std::string oracionPedido)
{
	int num = 0;

	// Limpio buffer
	std::cin.clear();

	// Imprimo frase para pedir el numero
	std::cout << oracionPedido ;

	// Pido numero
	std::cin >> num;

	// Valido error
	if(std::cin.fail())
	{
		std::cin.clear();

		std::cin.ignore(100, '\n');

		num = -1;
	}

	// Retorno valor leido
	return num;
}


void BatallaDigital::ingresarNumeroJugadores()
{
	int num = 0;

	while(num < CANT_MIN_JUGADORES || num > CANT_MAX_JUGADORES)
	{
		num = ingresoNumeroEnteroPositivoConsola(STRING_INGRESE_CANT_JUGADORES);

		if(num < CANT_MIN_JUGADORES || num > CANT_MAX_JUGADORES)
		{
			std::cout  << STRING_ERROR_CANT << CANT_MIN_JUGADORES <<" y " << CANT_MAX_JUGADORES << std::endl;

			num = 0;
		}
	}


	this->cantidadJugadores = (unsigned int)num;


}

void BatallaDigital::ingresarDimensionesTablero()
{
	int num = 0;

	while(num < DIM_MIN_X_Y)
	{
		num = ingresoNumeroEnteroPositivoConsola(STRING_DIM_X);

		if(num < DIM_MIN_X_Y)
		{
			std::cout  << STRING_ERROR_DIM << DIM_MIN_X_Y << std:: endl;
		}
	}

	this->dimensionesTablero[0] = (unsigned int)num ;
	num = 0;

	while(num < DIM_MIN_X_Y)
	{
		num = ingresoNumeroEnteroPositivoConsola(STRING_DIM_Y);

		if(num < DIM_MIN_X_Y)
		{
			std::cout  << STRING_ERROR_DIM << DIM_MIN_X_Y << std:: endl;
		}
	}

	this->dimensionesTablero[1] = (unsigned int)num ;
	num = 0;

	while(num < DIM_MIN_Z)
	{
		num = ingresoNumeroEnteroPositivoConsola(STRING_DIM_Z);

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
		int idJugador = i + 1;

		std::cout << "Ingrese el nombre del jugador: " ;

		std::string nombreJugador;

		std::cin >> nombreJugador;

		std::cout << std::endl;

		Jugador * nuevoJugador=new Jugador(idJugador+1,nombreJugador);
		this->listaDeJugadores->add(nuevoJugador);
	}

	std::cout << "Se generó una lista de "<< this->listaDeJugadores->contarElementos()<< " jugadores" << std::endl;
}

Jugador * BatallaDigital::obtenerPrimerJugador()
{
	Jugador * jugador = NULL ;

	this->listaDeJugadores->reiniciarCursor();

	this->listaDeJugadores->avanzarCursor();

	jugador = this->listaDeJugadores->getCursor();

	return jugador;
}

Jugador * BatallaDigital::obtenerSiguienteJugador(int identificadorJugadorAnterior)
{
	// Reinicializo la lista
	this->listaDeJugadores->reiniciarCursor();


	// Avanzo la lista
	while(this->listaDeJugadores->avanzarCursor())
	{
		// Comparo el identificador del jugador con er anterior
		if(this->listaDeJugadores->getCursor()->getIdentificador() > identificadorJugadorAnterior)
		{
			// Si el identificador del siguiente jugador es mayor al anterior
			// lo retorno
			return this->listaDeJugadores->getCursor();
		}
	}

	// Si se acabó la lista y no encontré un ID mayor al anterior, quiere decir que estaba al final de la lista
	// retorno el primer jugador
	return obtenerPrimerJugador();
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
		if(cursorJugador->getIdentificador()==jugador)
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


bool BatallaDigital::moverFicha(Ficha * fichaMover , tipoMovimiento_t tipoMovimiento , unsigned int cantCasilleros)
{
	// Casillero de inicio de la trayectoria
	Casillero * casilleroInicio = fichaMover->getCasilleroFicha();

	// Casillero destino de la trayectoria
	// Llamo a la funcion de tablero que navega por si mismo encontrando obstaculos o cambio de terreno
	Casillero * casilleroDestino = this->tableroJuego->navegarTablero(casilleroInicio, tipoMovimiento, cantCasilleros);


	//std::cout << "Navegar tablero retornó el casillero en"<<casilleroDestino->getCoordenada()->toString() << std::endl ;


	if(!casilleroDestino)
	{
		// Si el casillero destino es null entonces me fui del mapa
		std::cout << "El destino se encuentra fuera del mapa. No se puede realizar ese movimiento." << std::endl;
		return false;
	}
	else if (casilleroInicio->getTipoCasillero() != casilleroDestino->getTipoCasillero())
	{
		// Si hay cambio de terreno no puedo mover
		std::cout << "Cambio de terreno en la trayectoria. No se puede realizar ese movimiento." << std::endl;
		return false;
	}
	else if(!casilleroDestino->estaActivo())
	{
		// Si el casillero esta inactivo no puedo hacer el movimiento
		std::cout << "Casillero inactivo en la trayectoria. No se puede realizar ese movimiento." << std::endl;
		return false;
	}
	else if(casilleroDestino->estaOcupado())
	{
		// Si el casillero estaba ocupado se provoca una explosión de algún tipo
		Ficha * fichaOcupante = casilleroDestino->getFichaCasillero();

		if(fichaOcupante->obtenerTipo()==FICHA_MINA)
		{
			explosionEnTablero ( casilleroDestino , TURNOS_INACTIVIDAD_POR_EXPLOSION_MINA_SOLDADO , RADIO_EXPLOSION_POR_CHOQUE_MINA_SOLDADO );
		}
		else
		{
			explosionEnTablero ( casilleroDestino , TURNOS_INACTIVIDAD_POR_EXPLOSION_SOLDADOS , RADIO_EXPLOSION_POR_CHOQUE_SOLDADOS );
		}

		fichaMover->desactivarFicha();
	}
	else if(casilleroDestino->estaContaminado())
	{
		// Si el casillero estaba contaminado
		std::cout << "¡Pasaste por el casillero en " <<  casilleroDestino->getCoordenada()->toString() << "que se encontraba ENVENENADO!" << std::endl;

		// Desactivo la ficha que se intentó mover
		fichaMover->desactivarFicha();
	}
	else
	{
		// Si no se cumplen las condiciones anteriores entonces puedo mover la ficha
		std::cout << "Muevo la ficha de " << fichaMover->getCasilleroFicha()->getCoordenada()->toString() ;
		std::cout << " hasta " << casilleroDestino->getCoordenada()->toString() << std::endl;


		// Desvinculo ficha y casillero anterior
		fichaMover->desvincularFichaDeCasillero();
		casilleroInicio->vaciarCasillero();

		// Vinculo ficha y casillero destino
		vincularFichaYCasillero(casilleroDestino, fichaMover);
	}

	return true;
}



bool BatallaDigital::hayGanador(Jugador** jugadorGanador)
{
	this->listaDeJugadores->reiniciarCursor();
	int jugadoresConSoldados=0;
	Jugador * jugadorGanadorTemp = NULL;
	while(listaDeJugadores->avanzarCursor())
	{
		Jugador * jugador = listaDeJugadores->getCursor();
		if (jugador->cantidadFichasSoldado()>0)
		{
			//Cuando encuentro un jugador con soldados lo guardo en un puntero auxiliar
			jugadorGanadorTemp = jugador;
			jugadoresConSoldados++;
		}
	}

	if (jugadoresConSoldados==1)
	{
		//Cuando quede sólo un jugador con soldados, temp quedará apuntando a éste y ahi edito el puntero pasado como argumento
		*jugadorGanador = jugadorGanadorTemp;
		return true;
	}
	return false;
}


void BatallaDigital::imprimirGanador(Jugador* jugadorGanador)
{
	std::cout << STRING_JUGADOR_GANADOR_A << jugadorGanador->getNombre() << STRING_JUGADOR_GANADOR_B << std::endl << std::endl;
}

void BatallaDigital::mostrarGeografiaTablero()
{
	this->tableroJuego->imprimirGeografia();
}

Coordenada<int> BatallaDigital::pedirXYJugador(tipoCasillero_t tipoCasillero)
{
	// Coordenadas X e Y
	unsigned int x, y = 0;

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
			x = ingresoNumeroEnteroPositivoConsola(STRING_PEDIR_POS_X_SOLDADO);

			if(x < 1 || x > this->tableroJuego->getDimX())
			{
				// Si fue ingresada una posicion externa a las dimensiones del mapa
				std::cout << STRING_INGRESO_COORDENADA_ERROR_DIMENSIONES << std::endl;
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
			y = ingresoNumeroEnteroPositivoConsola(STRING_PEDIR_POS_Y_SOLDADO);


			if(y < 1 || y > this->tableroJuego->getDimY())
			{
				// Si fue ingresada una posicion externa a las dimensiones del mapa
				std::cout << STRING_INGRESO_COORDENADA_ERROR_DIMENSIONES << std::endl;
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
		// Obtengo el jugador actual de la lista
		Jugador * jugadorActual=this->listaDeJugadores->getCursor();

		// Imprimo turno del jugador
		imprimirTurnoDe(jugadorActual);

		// Entro en un bucle para que ingrese la cantidad de soldados que van a jugar
		for(int i = 0 ; i < CANT_INICIAL_SOLDADOS_POR_JUGADOR ; i++)
		{
			std::cout << STRING_INGRESO_SOLDADO << std::endl;

			Coordenada<int> coordenada = pedirXYJugador(tierra);

			fichaAux = crearFicha(FICHA_SOLDADO, coordenada.obtenerX(), coordenada.obtenerY(), coordenada.obtenerZ(), jugadorActual);

			casilleroAux = fichaAux->getCasilleroFicha();

			// Para verificar
			std::cout << "Ficha agregada a casillero: " ;
			casilleroAux->imprimirPos();
		}

		// \n
	}
}

void BatallaDigital::desactivarCasillero(Casillero * casillero , int turnosInactividad)
{
	Ficha * fichaAux = NULL ;

	fichaAux = casillero->getFichaCasillero();

	// Si el casillero estaba ocupado
	if(fichaAux)
	{
		// Desvinculo la ficha del casillero
		fichaAux->desvincularFichaDeCasillero();

		// Desactivo la ficha
		fichaAux->desactivarFicha();
	}

	// Vacío el casillero
	casillero->vaciarCasillero();

	// Desactiva el casillero con los turnos que se recibieron como parámetro
	casillero->desactivar(turnosInactividad);

	// Agrego el casillero a la lista de casilleros inactivos
	this->tableroJuego->agregarCasilleroInactivo(casillero);

}

void BatallaDigital::contaminarCasillero(Casillero * casillero , int turnosContaminacion)
{
	Ficha * fichaAux = NULL ;

	fichaAux = casillero->getFichaCasillero();

	// Si el casillero estaba ocupado
	if(fichaAux)
	{
		// Si estaba ocupado por un soldado
		if(fichaAux->getTipoFicha() == FICHA_SOLDADO)
		{
			std::cout << "El soldado ubicado en " << fichaAux->getCasilleroFicha()->getCoordenada()->toString() << " fue eliminado por envenenamiento." << std::endl;

			// Desvinculo la ficha del casillero
			fichaAux->desvincularFichaDeCasillero();

			// Desactivo la ficha
			fichaAux->desactivarFicha();
		}

	}
	// Vacío el casillero
	casillero->vaciarCasillero();

	// Contamino el casillero
	casillero->sumarTurnosContaminacion(turnosContaminacion);

	// Agrego el casillero contaminado a la lista de casilleros contaminados
	this->tableroJuego->agregarCasilleroContaminado(casillero);

}

void BatallaDigital::jugarCartaAtaqueQuimico() {

		Casillero * casilleroAtaque = NULL;

		std::cout << "Ingresar coordenada central ataque químico: " << std::endl;

		Coordenada<int> *objetivo;
		while(!casilleroAtaque)
		{
			validarCoordenada(objetivo);

			casilleroAtaque = this->tableroJuego->obtenerCasillero(objetivo);

			if(!casilleroAtaque)
			{
				std::cout << "La coordenada ingresada no corresponde a un casillero. " << std::endl;
			}
		}


		lanzarAtaqueQuimico(casilleroAtaque);
}


void BatallaDigital::explosionEnTablero (Casillero * casilleroCentral , int turnosInactividadEpicentro , int radioExplosion )
{
	if(!casilleroCentral)
	{
		throw "Error puntero a casillero nulo";
	}
	else if(turnosInactividadEpicentro < 3)
	{
		throw "Error turnos inactividad invalidos";
	}
	else if(radioExplosion < 1 || radioExplosion > 3)
	{
		throw "Error radio explosión invalido";
	}

	std::cout << "Se generó una explosión de radio " << radioExplosion << " con epicentro en el casillero " << casilleroCentral->getCoordenada()->toString() << std::endl;

	desactivarCasillero(casilleroCentral , turnosInactividadEpicentro);

	Casillero * casilleroAntX = casilleroCentral;
	Casillero * casilleroAntY = casilleroCentral;
	Casillero * casilleroSigX = casilleroCentral;
	Casillero * casilleroSigY = casilleroCentral;

	for(int i = 1 ; i < radioExplosion ; i ++)
	{
		if(casilleroAntX)
		{
			casilleroAntX = casilleroAntX->getAntX();
			if(casilleroAntX)
			{
				desactivarCasillero(casilleroAntX , turnosInactividadEpicentro - i);
			}
		}

		if(casilleroSigX)
		{
			casilleroSigX = casilleroSigX->getSigX();
			if(casilleroSigX)
			{
				desactivarCasillero(casilleroSigX , turnosInactividadEpicentro - i);
			}

		}

		if(casilleroAntY)
		{
			casilleroAntY = casilleroAntY->getAntY();
			if(casilleroAntY)
			{
				desactivarCasillero(casilleroAntY , turnosInactividadEpicentro - i);
			}
		}

		if(casilleroSigY)
		{
			casilleroSigY = casilleroSigY->getSigY();
			if(casilleroSigY)
			{
				desactivarCasillero(casilleroSigY , turnosInactividadEpicentro - i);
			}

		}

	}

}



void BatallaDigital::mostrarTablero(Jugador *jugador)
{
	bitmap->dibujarTablero(this->tableroJuego, jugador);
}

unsigned int BatallaDigital::cantidadDeJugadores()
{
	return this->cantidadJugadores;
}



Jugador * BatallaDigital::obtenerJugadorNumero(unsigned int jugador)
{
	return this->listaDeJugadores->get(jugador);
}

bool BatallaDigital::jugadorQuiereMover()
{
	std::string respuesta;
    std::cout << "¿Deseas moverte? (s/n): ";
    std::cin >> respuesta;
	if(respuesta == "s" || respuesta == "si" || respuesta == "Si" || respuesta == "SI")
	{
		return true;
	}
	else
    	return false; 
}

bool BatallaDigital::jugadorQuiereUsarCarta()
{
	std::string respuesta;
    std::cout << "¿Deseas usar una carta? (s/n): ";
    std::cin >> respuesta;
	if(respuesta == "s" || respuesta == "si" || respuesta == "Si" || respuesta == "SI")
	{
		return true;
	}
	else
    	return false; 
}

tipoMovimiento_t BatallaDigital::obtenerMovimiento()
{
    int seleccion = 0;

    std::cout << "Los posibles movimientos son:" << std::endl;
    std::cout << "1: Adelante" << std::endl;
    std::cout << "2: Atras" << std::endl;
    std::cout << "3: Izquierda" << std::endl;
    std::cout << "4: Derecha" << std::endl;
    std::cout << "5: Adelante Izquierda" << std::endl;
    std::cout << "6: Adelante Derecha" << std::endl;
    std::cout << "7: Atras Izquierda" << std::endl;
    std::cout << "8: Atras Derecha" << std::endl;

    while (seleccion < 1 || seleccion > 8)
    {
    	seleccion = ingresoNumeroEnteroPositivoConsola("¿Qué tipo de movimiento quiere realizar? ");

        if (seleccion < 1 || seleccion > 8)
        {
            std::cout << "Error. Ingrese un tipo de movimiento válido. " << std::endl;
        }
    }

    return static_cast<tipoMovimiento_t>(seleccion - 1);
}

int BatallaDigital::obtenerCantidadCasilleros()
{
    int seleccion = 0;

    while (seleccion < 1 ) {

    	seleccion = ingresoNumeroEnteroPositivoConsola("La cantidad de casillero a desplazar: ");

        if (seleccion < 1 )
        {
            std::cout << "Error. Ingresar un número positivo. ";
        }
    }


    return seleccion ;
}



void BatallaDigital::avanzarTurno(Jugador * jugador)
{
		if(!jugador)
		{
			throw "Error puntero a jugador nulo";
		}

		//Variables para el turno
		bool mover,jugarCarta=false;
		Casillero * casilleroMinar = NULL;
		
		// Imprimo de quién es el turno
		imprimirTurnoDe(jugador);

		//Se remueven las fichas del jugador que podrian haberse desactivado en otro turno.
		jugador->removerFichasInactivas();

		if(jugador->cantidadFichasSoldado() < 1)
		{
			return;
		}


		//Comienzo preguntando dónde quiere minar el jugador
		std::string stringCoordenada;
		std::cin.clear();

		//Lectura y validacion de coordenada (si la coordenada esta en rango)
		Coordenada<int> * objetivo;

		bool esCoordenadaValida=false;		

		while(!esCoordenadaValida)
		{
			// Imprimo por consola que se ingrese la coordenada
			std::cout<<"Ingrese la coordenada del casillero a minar en formato csv (Ejemplo: 1,2,1): "<<std::endl;

			//Se lee desde la consola una cadena csv indicando la coordenada a minar
			getline(std::cin, stringCoordenada);

			// Creo la coordenada
			objetivo=new Coordenada<int>(stringCoordenada,",");
			
			// Obtengo el casillero
			casilleroMinar = this->tableroJuego->obtenerCasillero(objetivo);

			//Validacion de Coordenada
			if(!casilleroMinar)
			{
				std::cout<<STRING_INGRESO_COORDENADA_ERROR_DIMENSIONES<<std::endl;
			}
			else if(casilleroMinar->getTipoCasillero()==agua)
			{
				std::cout<< STRING_INGRESO_MINA_ERROR_AGUA << std::endl;
			}
			else if(casilleroMinar->getTipoCasillero()==aire)
			{
				std::cout<< STRING_INGRESO_MINA_ERROR_AIRE << std::endl;
			}
			else if(!(casilleroMinar->estaActivo()))
			{
				std::cout<< STRING_INGRESO_MINA_ERROR_CAS_INACTIVO << std::endl;
			}
			else
			{
				esCoordenadaValida=true;
			}

			delete objetivo;
		}

		std::cout<<"Casillero a minar -> " << casilleroMinar->getCoordenada()->toString() << std::endl;

		// Se mina el casillero
		minarCasillero(casilleroMinar,jugador);

		//Le pregunto si quiere mover
		mover = jugadorQuiereMover();

		if(mover)
		{	

			//MUESTRO SUS FICHAS
			// Guardo en la variable indiceMax la cantidad de fichas mostradas
			unsigned int indiceMax = jugador->mostrarFichas();

			//LE PREGUNTO CUAL QUIERE MOVER
			unsigned int seleccion = 0;

			while (seleccion < 1 || seleccion > indiceMax)
			{
				seleccion = ingresoNumeroEnteroPositivoConsola("¿Qué numero de ficha queres mover?");

				if(seleccion < 1 || seleccion > indiceMax)
				{
					std::cout << "Error. Por favor ingrese una opción válida." << std::endl;
				}

			}

			Ficha * ficha=jugador->obtenerFicha(seleccion);

			bool movimientoExitoso=false;

			while(!movimientoExitoso)
			{
				//LE PREGUNTO COMO QUIERE MOVERLA
				tipoMovimiento_t movimiento = obtenerMovimiento();

				//LE PREGUNTO CUANTO QUIERE MOVERLA
				int cantidadCasilleros = obtenerCantidadCasilleros();

				//INTENTO MOVERLA
				if (moverFicha(ficha , movimiento , cantidadCasilleros))
				{
					movimientoExitoso=true;
				}
				
			}
		}

		//Se verifica que haya cartas en el mazo principal
		if(this->cartasDisponibles->contarCartas()==0){
			std::cout<<"Ya no quedan cartas por sacar. Mezclando mazo... "<<std::endl;
			reiniciarMazo();
		}

		//Se obtiene una carta aleatoria del mazo principal y se la asigna al jugador
		CartaBatallaDigital * cartaObtenida=this->cartasDisponibles->pop();
		std::cout<<"Carta Obtenida:"<<cartaObtenida->getNombre()<<std::endl;
		jugador->agregarCarta(cartaObtenida);
		
		//Se juega la carta, o no.
		jugarCarta = jugadorQuiereUsarCarta();
		if(jugarCarta==true)
		{	int opcionElegida;
			CartaBatallaDigital * cartaJugada;
			std::cout<<"Seleccioná la carta a utilizar"<<std::endl;
			jugador->mostrarCartas();
			std::cin>>opcionElegida;
			cartaJugada=jugador->obtenerCarta(opcionElegida);//Se saca la carta de la mano del jugador
			
			//Se juega la carta
			JugarCarta(jugador,cartaJugada);

			//Se añade la carta al mazo de las cartas utilizadas
			this->cartasJugadas->agregarCarta(cartaJugada);
			std::cout<<"Se jugó la carta "<<cartaJugada->getNombre()<<std::endl;
		}

}

void BatallaDigital::JugarCarta(Jugador * jugador, CartaBatallaDigital * carta){

	if(jugador==NULL||carta==NULL)	{
		throw "Error:Puntero nulo";
	}


	switch(carta->getTipo()){
		case CARTA_BARCO:
			jugarCartaBarco(jugador);
		break;

		case CARTA_ATAQUE_QUIMICO:
			jugarCartaAtaqueQuimico();
			std::cout<<"Un horrible ataque químico ha caído sobre el terreno de batalla!"<<std::endl;
		break;

		case CARTA_AVION_RADAR:
			jugarCartaAvion(jugador);
		break;
		case CARTA_REFUERZOS:
			jugarCartaRefuerzoSoldado(jugador);
		break;

		case CARTA_SUBMARINO:
			jugarCartaSubmarino(jugador);
		break;

		case CARTA_TRINCHERA:
			jugarCartaTrinchera(jugador);
		break;
	}
}


Lista<Casillero *> * BatallaDigital::EscanearTerreno(Jugador * jugador,Ficha * avionRadar)	{

	int cantidadCasillerosAdyacentes=1;
	int x,y,z;

	Lista<Casillero*> * casillerosEnemigos=new Lista<Casillero*>();//Lista de casilleros ocupados por fichas enemigas
	x=avionRadar->obtenerCoordenada()->obtenerX();
	y=avionRadar->obtenerCoordenada()->obtenerY();
	z=5;//Altura maxima del terreno

	if(avionRadar->obtenerTipo()!=FICHA_AVION){
		throw "El mapa solo puede ser escaneado por un avion radar";
	}

	for(int i=-cantidadCasillerosAdyacentes;	i<cantidadCasillerosAdyacentes+1;i++)	{
		for(int j=-cantidadCasillerosAdyacentes;	j<cantidadCasillerosAdyacentes+1;j++)	{

			if(_esPosicionValida(x+i,y+j,z)){

				if(this->tableroJuego->obtenerCasillero(x+i,y+j,z)->estaOcupado()){
					Coordenada<int> * coordenadaEscaneada=this->tableroJuego->obtenerCasillero(x+i,y+j,z)->getCoordenada();
					if(jugador->obtenerFicha(*coordenadaEscaneada)==NULL)	{//Si el casillero esta ocupado y no es una ficha perteneciente al jugador=> es enemiga
						casillerosEnemigos->add(this->tableroJuego->obtenerCasillero(x+i,y+j,z));
						std::cout<<"Enemigo detectado en posicion:"<<coordenadaEscaneada->toString()<<std::endl;
					}
				}
			
			} else	{
				std::cerr<<"No se agregó un casillero a los vigilados por ser una posicion invalida\n";
			}
		}
	}
	return casillerosEnemigos;
}


bool BatallaDigital::_esPosicionValida(unsigned int x,unsigned int y, unsigned int z){
	
	if(((x>0&&x<this->tableroJuego->getDimX())&&(y>0&&y<this->tableroJuego->getDimY()))&&(z>0&&z<this->tableroJuego->getDimZ()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Ejemplo de uso: se puede reemplazar desde la linea 635 hasta la 650 por esto:
// validarCoordenada(objetivo);
void BatallaDigital::validarCoordenada(Coordenada<int>* &objetivo) {
	std::string stringCoordenada;
	std::cin.clear();
	//Lectura y validacion de coordenada (si la coordenada esta en rango)
	bool esCoordenadaValida=false;		
	while(!esCoordenadaValida)	{
		std::cout<<"Ingrese la coordenada del casillero en formato csv\nEjemplo: 1,2,1"<<std::endl;
		getline(std::cin, stringCoordenada);//Se lee desde la consola una cadena csv indicando la coordenada. Ejemplo:	1,2,4
		objetivo=new Coordenada<int>(stringCoordenada,",");

		if((this->tableroJuego->obtenerCasillero(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ())) != NULL){
			esCoordenadaValida=true;
		}	else{
			delete objetivo;
			std::cout<<"Coordenada invalida[X]"<<std::endl;

		}
	}

}

void BatallaDigital::minarCasillero(Casillero * casillero ,Jugador * jugador) {

	if(!casillero)
	{
		throw "Error: Puntero a casillero nulo";
	}

	if(!jugador)
	{
		throw "Error: puntero a jugador nulo";
	}

	//Si el casillero esta ocupado genero una explosion
	if(casillero->estaOcupado())
	{
		// Puntero a la ficha que ocupa el casillero
		Ficha * fichaOcupante = casillero->getFichaCasillero();

		if(fichaOcupante->getTipoFicha() == FICHA_MINA)
		{
			explosionEnTablero(casillero, TURNOS_INACTIVIDAD_POR_EXPLOSION_MINAS , RADIO_EXPLOSION_POR_CHOQUE_MINAS);
		}
		else
		{
			explosionEnTablero(casillero, TURNOS_INACTIVIDAD_POR_EXPLOSION_MINA_SOLDADO , RADIO_EXPLOSION_POR_CHOQUE_MINA_SOLDADO);
		}
	}
	else
	{
		//Si el casillero estaba desocupado, se crea la mina, se la posiciona en el tablero y se la agrega a al jugador
		Ficha * mina =new Ficha(FICHA_MINA,casillero->getPosX(), casillero->getPosY(), casillero->getPosZ());
		casillero->setFichaCasillero(mina);
		mina->setCasilleroFicha(casillero);
		jugador->agregarFicha(mina);
	}

}



void BatallaDigital::imprimirTurnoDe(Jugador * jugador)
{
	std::cout << STRING_TURNO_DE_P1 << jugador->getNombre() << STRING_TURNO_DE_P2 << std::endl << std::endl;
}


void BatallaDigital::ubicarBarco(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador) {

	Casillero * objetivoCasillero= this->tableroJuego->obtenerCasillero(x,y,z);
	
	if(!objetivoCasillero->estaActivo()){
				throw "El casillero esta inactivo";
	}

	if(objetivoCasillero->getTipoCasillero()!=agua)	{
		 throw "Solo se puede ubicar un barco en un casillero de tipo agua";
	}

	//El casillero puede estar ocupado por otra ficha, se desactiva la ficha (se la da de baja), se vacia e inactiva el casillero
	if(objetivoCasillero->estaOcupado()){
		Ficha * fichaOcupante=objetivoCasillero->getFichaCasillero();
		fichaOcupante->desactivarFicha();
		objetivoCasillero->vaciarCasillero();
		objetivoCasillero->desactivar();
	}	else {
	//Si el casillero estaba desocupado, se ubica el barco en el tablero
		Ficha * barco=new Ficha(FICHA_BARCO,x,y,z);
		objetivoCasillero->setFichaCasillero(barco);
		barco->setCasilleroFicha(objetivoCasillero);
		jugador->agregarFicha(barco);
	}

}

void BatallaDigital::jugarCartaBarco(Jugador *jugador) {
		std::cout << "Ubicar barco : " << std::endl;
		Coordenada<int> *objetivo;
		validarCoordenada(objetivo);

		std::cout<<"Casillero a ubicar el barco "<<objetivo->toString()<<std::endl;

		//Esta funcion puede fallar: Si el casillero esta inactivo o si el tipo de casillero es distinto de AGUA
		try{
			ubicarBarco(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ(),jugador);
			}
		catch(...){
		}
		// Si pudo ubicar correctamente el barco
		if(this->tableroJuego->obtenerCasillero(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ())->estaOcupado()){
			std::cout<<"Barco ubicado en el casillero "<<objetivo->toString()<<std::endl;
			Coordenada<int> * destinoMisil;
			std::cout<<"Destino del misil:"<<std::endl;
			validarCoordenada(destinoMisil);
			

			std::cout<<"Casillero a atacar con misil "<<destinoMisil->toString()<<std::endl;
			Casillero * casilleroObjetivoMisil=this->tableroJuego->obtenerCasillero(destinoMisil->obtenerX(),destinoMisil->obtenerY(),destinoMisil->obtenerZ());

			if(!casilleroObjetivoMisil->estaOcupado()){
				std::cout<<"No habia objetivos a eliminar en la coordenada con el misil "<<std::endl;//Se desactiva un casillero desocupado que se ataca con un misil?
			} else{
				switch(casilleroObjetivoMisil->getFichaCasillero()->getTipoFicha())	{
				case FICHA_SOLDADO:
					std::cout<<"Soldado eliminado"<<std::endl;
					break;
			
				case FICHA_AVION:
					std::cout<<"Avion eliminado"<<std::endl;
					break;
				case FICHA_BARCO:
					std::cout<<"Barco eliminado"<<std::endl;
					break;
				default:
					break;
			}
				explosionEnTablero(casilleroObjetivoMisil,5,1);
			}
		}	else	{
			std::cout<<"No se pudo ubicar el barco en el casillero "<<objetivo->toString()<<std::endl;
			}

		Coordenada<int> * destinoTorpedo;
		std::cout<<"Destino del torpedo:"<<std::endl;
		validarCoordenada(destinoTorpedo);
		std::cout<<"Casillero a atacar con torpedo "<<destinoTorpedo->toString()<<std::endl;

		Casillero * casilleroObjetivoTorpedo=this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),
		destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ());

		if(!casilleroObjetivoTorpedo->estaOcupado()){
				//Se desactiva un casillero desocupado que se ataca con un misil?
				std::cout<<"No habia objetivos a eliminar en la coordenada con el torpedo "<<std::endl;
			} else 
				if(casilleroObjetivoTorpedo->getFichaCasillero()->obtenerTipo()==FICHA_SUBMARINO){
				casilleroObjetivoTorpedo->getFichaCasillero()->desactivarFicha();
				casilleroObjetivoTorpedo->vaciarCasillero();
				casilleroObjetivoTorpedo->desactivar();
				std::cout<<"Submarino eliminado"<<std::endl;
		}	else{
			std::cout<<"Solo puede eliinar submarinos"<<std::endl;
		}	

}

void BatallaDigital::ubicarAvion(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador) {

	Casillero * objetivoCasillero= this->tableroJuego->obtenerCasillero(x,y,z);
	
	if(!objetivoCasillero->estaActivo()){
				throw "El casillero esta inactivo";
	}

	if(objetivoCasillero->getTipoCasillero()!=aire)	{
		 throw "Solo se puede ubicar un avion en un casillero de tipo aire";
	}

	//El casillero puede estar ocupado por otra ficha, se desactiva la ficha (se la da de baja), se vacia e inactiva el casillero
	if(objetivoCasillero->estaOcupado()){
		Ficha * fichaOcupante=objetivoCasillero->getFichaCasillero();
		fichaOcupante->desactivarFicha();
		objetivoCasillero->vaciarCasillero();
		objetivoCasillero->desactivar();
	}	else {
	//Si el casillero estaba desocupado, se ubica el avion en el tablero
		Ficha * avion=new Ficha(FICHA_AVION,x,y,z);
		objetivoCasillero->setFichaCasillero(avion);
		avion->setCasilleroFicha(objetivoCasillero);
		jugador->agregarFicha(avion);
	}
	
}

void BatallaDigital::jugarCartaAvion(Jugador * jugador) {
		std::cout << "Ubicar avion : " << std::endl;
		Coordenada<int> *objetivo;
		validarCoordenada(objetivo);

		std::cout<<"Casillero a ubicar el avion "<<objetivo->toString()<<std::endl;

		//Esta funcion puede fallar: Si el casillero esta inactivo o si el tipo de casillero es distinto de AIRE
		try{
			ubicarAvion(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ(),jugador);
			}
		catch(...){
		}

		Casillero * casilleroAvion=this->tableroJuego->obtenerCasillero(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ());
		// Si pudo ubicar correctamente el avion
		if(casilleroAvion->estaOcupado()){
			std::cout<<"Avion ubicado en el casillero "<<objetivo->toString()<<std::endl;
			std::cout<<"Escaneando terreno..."<<std::endl;
			jugador->setEnemigosDetectados(this->EscanearTerreno(jugador,casilleroAvion->getFichaCasillero()));
			std::cout<<"...terreno escaneado"<<std::endl;
		}
		else	{
			std::cout<<"No se pudo ubicar el avion en el casillero "<<objetivo->toString()<<std::endl;
		}

}

void BatallaDigital::ubicarSubmarino(unsigned int x, unsigned int y, unsigned int z, Jugador *jugador) {
	
	Casillero * objetivoCasillero= this->tableroJuego->obtenerCasillero(x,y,z);
	
	if(!objetivoCasillero->estaActivo()){
				throw "El casillero esta inactivo";
	}

	if(objetivoCasillero->getTipoCasillero()!=agua)	{
		 throw "Solo se puede ubicar un submarino en un casillero de tipo agua";
	}

	//El casillero puede estar ocupado por otra ficha, se desactiva la ficha (se la da de baja), se vacia e inactiva el casillero
	if(objetivoCasillero->estaOcupado()){
		Ficha * fichaOcupante=objetivoCasillero->getFichaCasillero();
		fichaOcupante->desactivarFicha();
		objetivoCasillero->vaciarCasillero();
		objetivoCasillero->desactivar();
	}	else {
	//Si el casillero estaba desocupado, se ubica el submarino en el tablero
		Ficha * submarino=new Ficha(FICHA_SUBMARINO,x,y,z);
		objetivoCasillero->setFichaCasillero(submarino);
		submarino->setCasilleroFicha(objetivoCasillero);
		jugador->agregarFicha(submarino);
	}
	
}

void BatallaDigital::jugarCartaSubmarino(Jugador * jugador) {
		std::cout << "Ubicar submarino : " << std::endl;
		Coordenada<int> *objetivo;
		validarCoordenada(objetivo);

		std::cout<<"Casillero a ubicar el submarino "<<objetivo->toString()<<std::endl;

		//Esta funcion puede fallar: Si el casillero esta inactivo o si el tipo de casillero es distinto de AGUA
		try{
			ubicarSubmarino(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ(),jugador);
			}
		catch(...){
			std::cerr<<"Fallo al ubicar submarino"<<std::endl;
		}
		// Si pudo ubicar correctamente el submarino
		if(this->tableroJuego->obtenerCasillero(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ())->estaOcupado()){
			std::cout<<"Submarino ubicado en el casillero "<<objetivo->toString()<<std::endl;
			Coordenada<int> * destinoTorpedo;
			std::cout<<"Destino del torpedo:"<<std::endl;
			validarCoordenada(destinoTorpedo);
			std::cout<<"Casillero a atacar con torpedo "<<destinoTorpedo->toString()<<std::endl;
			if(this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->getFichaCasillero()->obtenerTipo()==FICHA_SUBMARINO){
				this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->getFichaCasillero()->desactivarFicha();
				this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->vaciarCasillero();
				this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->desactivar();
				std::cout<<"Submarino eliminado"<<std::endl;
			}
			else if(this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->getFichaCasillero()->obtenerTipo()==FICHA_BARCO){
				this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->getFichaCasillero()->desactivarFicha();
				this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->vaciarCasillero();
				this->tableroJuego->obtenerCasillero(destinoTorpedo->obtenerX(),destinoTorpedo->obtenerY(),destinoTorpedo->obtenerZ())->desactivar();
				std::cout<<"Barco eliminado"<<std::endl;
			} else	{
				std::cout<<"No habia objetivos a eliminar en la coordenada con el torpedo "<<std::endl;
			}
	}


	
}


void BatallaDigital::ubicarRefuerzoSoldado(unsigned int x, unsigned int y, unsigned int z,Jugador * jugador) {
	
	Casillero * objetivoCasillero= this->tableroJuego->obtenerCasillero(x,y,z);
	
	if(!objetivoCasillero->estaActivo()){
				throw "El casillero esta inactivo";
	}

	if(objetivoCasillero->getTipoCasillero()!=tierra)	{
		 throw "Solo se puede ubicar un soldado en un casillero de tipo tierra";
	}

	//El casillero puede estar ocupado por otra ficha, se desactiva la ficha (se la da de baja), se vacia e inactiva el casillero
	if(objetivoCasillero->estaOcupado()){
		Ficha * fichaOcupante=objetivoCasillero->getFichaCasillero();
		fichaOcupante->desactivarFicha();
		objetivoCasillero->vaciarCasillero();
		objetivoCasillero->desactivar();
	}	else {
	//Si el casillero estaba desocupado, se ubica el soldado en el tablero
		Ficha * soldado=new Ficha(FICHA_SOLDADO,x,y,z);
		objetivoCasillero->setFichaCasillero(soldado);
		soldado->setCasilleroFicha(objetivoCasillero);
		jugador->agregarFicha(soldado);
	}
}

void BatallaDigital::jugarCartaRefuerzoSoldado(Jugador * jugador) {
		std::cout << "Ubicar soldado : " << std::endl;
		Coordenada<int> *objetivo;
		validarCoordenada(objetivo);

		std::cout<<"Casillero a ubicar el soldado "<<objetivo->toString()<<std::endl;

		//Esta funcion puede fallar: Si el casillero esta inactivo o si el tipo de casillero es distinto de TIERRA
		try{
			ubicarRefuerzoSoldado(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ(),jugador);
			}
		catch(...){
		}
		// Si pudo ubicar correctamente el soldado
		if(this->tableroJuego->obtenerCasillero(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ())->estaOcupado()){
			std::cout<<"Soldado ubicado en el casillero "<<objetivo->toString()<<std::endl;
		}
		else	{
			std::cout<<"No se pudo ubicar el soldado en el casillero "<<objetivo->toString()<<std::endl;
		}

	}

void BatallaDigital::jugarCartaTrinchera(Jugador * jugador) {
		if (jugador->cantidadFichasSoldado() == 0) {
				throw "El jugador no tiene soldados a atrincherar";
		}
		std::cout << "Ubicar trinchera : " << std::endl;
		Coordenada<int> *objetivo;
		validarCoordenada(objetivo);
		//Verifica si el jugador tiene un soldado que le pertenezca en la coordenada ingresada
		if(jugador->hayTipoEnCoordenada(FICHA_SOLDADO,objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ())){
			this->tableroJuego->obtenerCasillero(objetivo->obtenerX(),objetivo->obtenerY(),objetivo->obtenerZ())->getFichaCasillero()->setTipoFicha(FICHA_TRINCHERA);
			std::cout<<"Soldado atrincherado. "<<objetivo->toString()<<std::endl;
		}
		else	{
			std::cout<<"No hay soldado en la coordenada ingresada "<<objetivo->toString()<<std::endl;
		}
}


void BatallaDigital::construirMazo(unsigned int cantidadCartas)	{

	CartaBatallaDigital * cartaAvion=new CartaBatallaDigital(CARTA_AVION_RADAR);
	CartaBatallaDigital * cartaBarco=new CartaBatallaDigital(CARTA_BARCO);
	CartaBatallaDigital * cartaSubmarino=new CartaBatallaDigital(CARTA_SUBMARINO);
	CartaBatallaDigital * cartaAtaqueQuimico=new CartaBatallaDigital(CARTA_ATAQUE_QUIMICO);
	CartaBatallaDigital * cartaRefuerzos=new CartaBatallaDigital(CARTA_REFUERZOS);
	CartaBatallaDigital * cartaTrinchera=new CartaBatallaDigital(CARTA_TRINCHERA);

	//Se agregan las cartas al mazo repitiendolas segun su atributo de cantidad de repeticiones
	this->cartasDisponibles->agregarCarta(cartaAvion,cartaAvion->getCantidadRepeticiones()*cantidadCartas/100);
	this->cartasDisponibles->agregarCarta(cartaBarco,cartaBarco->getCantidadRepeticiones()*cantidadCartas/100);
	this->cartasDisponibles->agregarCarta(cartaSubmarino,cartaSubmarino->getCantidadRepeticiones()*cantidadCartas/100);
	this->cartasDisponibles->agregarCarta(cartaAtaqueQuimico,cartaAtaqueQuimico->getCantidadRepeticiones()*cantidadCartas/100);
	this->cartasDisponibles->agregarCarta(cartaRefuerzos,cartaRefuerzos->getCantidadRepeticiones()*cantidadCartas/100);
	this->cartasDisponibles->agregarCarta(cartaTrinchera,cartaTrinchera->getCantidadRepeticiones()*cantidadCartas/100);

	//Se rellena con cartas de refuerzos
	while(this->cartasDisponibles->contarCartas()<cantidadCartas){
		this->cartasDisponibles->agregarCarta(cartaRefuerzos);
	}

	this->cartasDisponibles->mezclar();

	std::cout<<"Mazo creado. Cantidad de cartas:"<<this->cartasDisponibles->contarCartas()<<std::endl;
}	

void BatallaDigital::lanzarAtaqueQuimico(Casillero * casillero)
{
	if(!casillero)
	{
		throw("Error puntero a casillero nulo");
	}

	int multiplicador = 0;

	Casillero * casilleroIteracion = NULL;

	int xCentro = casillero->getPosX();
	int yCentro = casillero->getPosY();
	int zCentro	= casillero->getPosZ();

	for (int z = (-RADIO_EXPLOSION_ATAQUE_QUIMICO); z<=RADIO_EXPLOSION_ATAQUE_QUIMICO ; z++)
	{
		for (int y = (-RADIO_EXPLOSION_ATAQUE_QUIMICO); y<=RADIO_EXPLOSION_ATAQUE_QUIMICO ; y++ )
		{
			for (int x = (-RADIO_EXPLOSION_ATAQUE_QUIMICO); x<=RADIO_EXPLOSION_ATAQUE_QUIMICO ; x++ )
			{

				casilleroIteracion = this->tableroJuego->obtenerCasillero(xCentro+x, yCentro+y, zCentro+z);
				if(casilleroIteracion)
				{
					multiplicador = abs(x);
					if(abs(y)>multiplicador)
					{
						multiplicador = abs(y);
					}
					if(abs(z)> multiplicador)
					{
						multiplicador = abs(z);
					}
					contaminarCasillero(casilleroIteracion, TURNOS_CONTAMINACION_EPICENTRO_POR_ATAQUE_QUIMICO - RADIO_EXPLOSION_ATAQUE_QUIMICO * multiplicador);
				}
			}
		}
	}
}

void BatallaDigital::comienzaNuevaRonda()
{
	this->tableroJuego->decrementarInactividadCasilleros();
	this->tableroJuego->decrementarTurnosContaminacionCasilleros();
}


void BatallaDigital::reiniciarMazo(void){
	Mazo<CartaBatallaDigital *> * aux;
	aux=this->cartasDisponibles;
	this->cartasDisponibles=this->cartasJugadas;
	this->cartasJugadas=aux;
	this->cartasDisponibles->mezclar();
	return;
}
