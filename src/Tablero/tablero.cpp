#include <iostream>
#include <cstdlib>  // Para la generación de números aleatorios
#include <ctime>    // Para la semilla de la generación aleatoria


#include "tablero.h"

using namespace std;



//Constructor
Tablero::Tablero(int dimX, int dimY, int dimZ)
{
	// Dimensiones del tablero
	this->dimX = dimX;
	this->dimY = dimY;
	this->dimZ = dimZ;

	// Lista de casilleros inactivos comienza vacia
	this->listaCasillerosInactivos = NULL;

	Casillero* casilleroNuevo = NULL;
	tipoCasillero_t tipoCasillero=tierra;
	int nivelDelMar = NIVEL_MAXIMO_TIERRA;


	Lista<Lista<Lista<Casillero*>*>*>* tableroJuego = new Lista<Lista<Lista<Casillero*>*>*>();
	for(int z=1;z<=this->dimZ;z++)
	{
		Lista<Lista<Casillero*>* >* pisos= new Lista<Lista<Casillero*>*>();
		for(int y=1;y<=this->dimY;y++)
		{
				Lista<Casillero*>* columnas= new Lista<Casillero*>();
				for(int x=1;x<=this->dimX;x++)
				{	
					if (z<=nivelDelMar)
					{
						tipoCasillero=tierra;
					}
					else
					{
						tipoCasillero=aire;
					}
					casilleroNuevo= new Casillero(x,y,z,tipoCasillero);
					columnas->add(casilleroNuevo);
				}
				pisos->add(columnas);
		}
		tableroJuego->add(pisos);
	}

	this->tableroJuego=tableroJuego;
	vincularTablero();
	generarAguaEnTablero();

}

unsigned int Tablero::getDimX() {
	return this->dimX;
}
unsigned int Tablero::getDimY() {
	return this->dimY;
}
unsigned int Tablero::getDimZ() {
	return this->dimZ;
}

void Tablero::imprimirTablero()
{
	Casillero* casilleroImprimir = NULL;
	Lista<Lista<Casillero*>* >* pisosRecorrer=NULL;
	Lista<Casillero*>* columnasRecorrer=NULL;

	this->tableroJuego->reiniciarCursor();

	while(this->tableroJuego->avanzarCursor())
	{
		pisosRecorrer = this->tableroJuego->getCursor();

		pisosRecorrer->reiniciarCursor();

		while(pisosRecorrer->avanzarCursor())
		{
			columnasRecorrer = pisosRecorrer->getCursor();

			columnasRecorrer->reiniciarCursor();

			while(columnasRecorrer->avanzarCursor())
			{
				casilleroImprimir=columnasRecorrer->getCursor();
				casilleroImprimir->imprimirPos();
			}
		}
	}
}

void Tablero::imprimirGeografia()
{
	Casillero* casilleroImprimir = NULL;
	Lista<Lista<Casillero*>* >* pisosRecorrer=NULL;
	Lista<Casillero*>* columnasRecorrer=NULL;
	for(int z = 1 ; z <= this->dimZ ; z++)
	{
		pisosRecorrer=this->tableroJuego->get(z);
		for(int y = 1 ; y <= this->dimY ; y++)
		{
			columnasRecorrer=pisosRecorrer->get(y);
			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casilleroImprimir=columnasRecorrer->get(x);
				std::cout << casilleroImprimir->getTipoCasillero()<<"\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}	
}

void Tablero::vincularTablero()
{
	// Vinculo cada nivel de tablero
	for(int i = 1 ; i <= this->dimZ ; i++)
	{
		vincularNivelTablero(i);
	}

	// Vinculo los niveles entre sí
	vincularPisosTablero();
}

void Tablero::vincularNivelTablero(int nivel)
{

	Casillero* casilleroAntX = NULL;
	Casillero* casilleroSigX = NULL;
	Casillero* casilleroAntY = NULL;
	Casillero* casilleroSigY = NULL;

	Lista<Casillero*>* columnaAnterior=NULL;
	Lista<Casillero*>* columnaSiguiente=NULL;


	// Vinculación de casilleros dentro de una columna
	for(int i = 1 ; i <= this->dimY ; i++)
	{
		columnaAnterior = this->tableroJuego->get(nivel)->get(i);

		for(int j = 1 ; j < this->dimX ; j++)
		{
			casilleroAntX = columnaAnterior->get(j);
			casilleroSigX = columnaAnterior->get(j+1);

			casilleroAntX->setSigX(casilleroSigX);
			casilleroSigX->setAntX(casilleroAntX);
		}
	}


	// Vinculación de columnas entre si
	for(int i = 1 ; i < this->dimY ; i++)
	{
		columnaAnterior = this->tableroJuego->get(nivel)->get(i);
		columnaSiguiente = this->tableroJuego->get(nivel)->get(i+1);

		for(int j = 1 ; j <= this->dimX ; j++)
		{
			casilleroAntY = columnaAnterior->get(j);
			casilleroSigY = columnaSiguiente->get(j);

			casilleroAntY->setSigY(casilleroSigY);
			casilleroSigY->setAntY(casilleroAntY);
		}
	}
}

void Tablero::vincularPisosTablero()
{
	Casillero* casilleroVincularInicial = NULL;
	Casillero* casilleroVincularSiguiente = NULL;
	Lista<Lista<Casillero*>* >* pisoActual=NULL;
	Lista<Lista<Casillero*>* >* pisoSiguiente=NULL;
	Lista<Casillero*>* columnasInicial=NULL;
	Lista<Casillero*>* columnasSiguiente=NULL;
	for(int z = 1 ; z < this->dimZ ; z++)
	{
		pisoActual=this->tableroJuego->get(z);
		pisoSiguiente=this->tableroJuego->get(z+1);
		for(int y = 1 ; y <= this->dimY ; y++)
		{
			columnasInicial=pisoActual->get(y);
			columnasSiguiente=pisoSiguiente->get(y);
			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casilleroVincularInicial=columnasInicial->get(x);
				casilleroVincularSiguiente=columnasSiguiente->get(x);
				casilleroVincularInicial->setSigZ(casilleroVincularSiguiente);
				casilleroVincularSiguiente->setAntZ(casilleroVincularInicial);
			}
		}
	}
}

bool Tablero::chequearVinculosPisosTablero()
{
	Casillero* casillero = NULL;
	Lista<Lista<Casillero*>* >* piso=NULL;
	Lista<Casillero*>* columna=NULL;
	for(int z = 1 ; z <= this->dimZ ; z++)
	{
		piso=this->tableroJuego->get(z);
		for(int y = 1 ; y <= this->dimY ; y++)
		{
			columna=piso->get(y);
			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casillero=columna->get(x);
				if(z==1)
				{
					if(!casillero->getSigZ())
						{
							return false;
						}
				}
				else if(z==dimZ)
				{
					if(!casillero->getAntZ())
						{
							return false;
						}
				}
				else
				{
					if(!casillero->getSigZ() || !casillero->getAntZ())
						{
							return false;
						}
				}
			}
		}
	}
	return true;
}

void Tablero::agregarCasilleroInactivo(Casillero * casilleroInactivoNuevo)
{
	// Agrego el casillero inactivo a la lista
	this->listaCasillerosInactivos->add(casilleroInactivoNuevo);
}


void Tablero::decrementarInactividadCasilleros()
{
	// Variable aux para tener control de la posición de los elementos
	unsigned int i = 1;

	// Reinicio el cursor para comenzar a recorrer la lista
	this->listaCasillerosInactivos->reiniciarCursor();

	// Recorro la lista hasta el final
	while (this->listaCasillerosInactivos->avanzarCursor())
	{
		// Decremento inactividad en cada casillero
		this->listaCasillerosInactivos->getCursor()->decrementarInactividad();

		// Si luego de decrementar inactividad queda activo tengo que sacarlo de la lista
		if(this->listaCasillerosInactivos->getCursor()->estaActivo())
		{
			this->listaCasillerosInactivos->remover(i);
			i--;
		}

		i++;
	}
}

Casillero * Tablero::obtenerCasillero(int x, int y, int z)
{
	Casillero * casilleroReturn = NULL;

	if(x >=1 && x <=this->dimX && y >=1 && y <=this->dimY  && z >=1 && z <=this->dimZ)
	{
		casilleroReturn = this->tableroJuego->get(z)->get(y)->get(x);
	}

	return casilleroReturn;
}

Casillero * Tablero::obtenerCasillero(Coordenada<int> * coordenada)
{
	Casillero * casilleroReturn = NULL;

	int x = coordenada->obtenerX();
	int y = coordenada->obtenerY();
	int z = coordenada->obtenerZ() ;

	if(x >=1 && x <=this->dimX && y >=1 && y <=this->dimY  && z >=1 && z <=this->dimZ)
	{
		casilleroReturn = this->tableroJuego->get(z)->get(y)->get(x);
	}

	return casilleroReturn;
}

Casillero * Tablero::navegarTablero(Casillero * casilleroInicio, tipoMovimiento_t tipoMovimiento, unsigned int cantidadCasilleros)
{
	// Puntero que se retornará al final de la función
	Casillero * casilleroRetorno = casilleroInicio ;

	// Tipo de terreno inicial
	tipoCasillero_t tipoCasilleroInicio = casilleroInicio->getTipoCasillero();

	for(unsigned int i = 0 ; i < cantidadCasilleros ; i ++)
	{
		switch(tipoMovimiento)
		{
			case adelante:
				casilleroRetorno = casilleroRetorno->getSigY();
				break;
			case atras:
				casilleroRetorno = casilleroRetorno->getAntY();
				break;
			case izquierda:
				casilleroRetorno = casilleroRetorno->getAntX();
				break;
			case derecha:
				casilleroRetorno = casilleroRetorno->getSigX();
				break;
			case adelante_izquierda:
				casilleroRetorno = casilleroRetorno->getSigY();
				casilleroRetorno = casilleroRetorno->getAntX();
				break;
			case adelante_derecha:
				casilleroRetorno = casilleroRetorno->getSigY();
				casilleroRetorno = casilleroRetorno->getSigX();
				break;
			case atras_izquierda:
				casilleroRetorno = casilleroRetorno->getAntY();
				casilleroRetorno = casilleroRetorno->getAntX();
				break;
			case atras_derecha:
				casilleroRetorno = casilleroRetorno->getAntY();
				casilleroRetorno = casilleroRetorno->getSigX();
				break;
			default:
				break;
		}


		if(!casilleroRetorno)
		{
			// Si estoy fuera del mapa retorno null
			return casilleroRetorno;
		}
		else if(casilleroRetorno->getTipoCasillero() != tipoCasilleroInicio)
		{
			// Si cambié de tipo de terreno retorno este casillero
			return casilleroRetorno;
		}
		else if(casilleroRetorno->estaOcupado())
		{
			// Si el casillero está ocupado, lo retorno y finalizo el movimiento
			return casilleroRetorno;
		}
		else if(!casilleroRetorno->estaActivo())
		{
			// Si el casillero está inactivo, lo retorno y finalizo el movimiento
			return casilleroRetorno;
		}
		else if(casilleroRetorno->estaContaminado())
		{
			// Si el casillero está contaminado lo retorno y finalizo el movimiento
			return casilleroRetorno;
		}
	}

	return casilleroRetorno;
}
// Pre: debe haber un tablero creado con todos sus casilleros vinculados y separado en tierra y aire para una cierta altura
//		
// Pos: genera de forma aleatoria un cuerpo de agua contiguo en el tablero que cubra entre el 10% y 50% de éste
//		
void Tablero::generarAguaEnTablero() 
{
    int nivelDelMar = NIVEL_MAXIMO_TIERRA;
    
    // Generar una semilla aleatoria para generar números aleatorios
    srand(time(NULL));

    for (int z = nivelDelMar; z > 0; z--)
    {
        Lista<Lista<Casillero*>*>* pisos = this->tableroJuego->get(z);
        for (int y = 1; y <= this->dimY; y++)
        {
            Lista<Casillero*>* columnas = pisos->get(y);
            for (int x = 1; x <= this->dimX; x++)
            {
                Casillero* casillero = columnas->get(x);
                
                // Verificar si el casillero siguiente en Z es de tipo agua
                if (casillero->getSigZ()->getTipoCasillero() == agua)
                {
                    casillero->setTipoCasillero(agua);
                }
                else if (z == nivelDelMar)
                {
                    // Generar un número aleatorio entre 0 y 499
                    int randomNum = rand() % 500;

                    // Verificar casillas adyacentes
                    int tieneAguaAdyacente = casillero->casillerosAguaAdyacentes(casillero);
                    randomNum = randomNum + tieneAguaAdyacente* PROB_AGUA_EN_TABLERO;

                    // Establecer el casillero como agua si tiene agua adyacente
                    if (randomNum >= 490) 
                    {
                        casillero->setTipoCasillero(agua);
                    }
                    
                }
            }
        }
    }
}


Lista<Lista<Lista<Casillero*>*>*>* Tablero::obtenerTablero()
{
	return this->tableroJuego;
}


Tablero::~Tablero()
{
    // Liberar la memoria de los casilleros
    for (int z = 1; z <= dimZ; z++)
    {
        Lista<Lista<Casillero*>*>* pisos = tableroJuego->get(z);
        for (int y = 1; y <= dimY; y++)
        {
            Lista<Casillero*>* columnas = pisos->get(y);
            for (int x = 1; x <= dimX; x++)
            {
                Casillero* casillero = columnas->get(x);
                delete casillero;
            }
            delete columnas;
        }
        delete pisos;
    }
    delete tableroJuego;
}
