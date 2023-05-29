#include <iostream>


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
	Lista<Lista<Casillero*>* >* pisos=NULL;
	Lista<Casillero*>* columnas=NULL;
	tipoCasillero_t tipoCasillero = tierra;


	Lista<Lista<Lista<Casillero*>*>*>* tableroJuego = new Lista<Lista<Lista<Casillero*>*>*>();
	for(int z=1;z<=this->dimZ;z++)
	{
		Lista<Lista<Casillero*>* >* pisos= new Lista<Lista<Casillero*>*>();
		for(int y=1;y<=this->dimY;y++)
		{
				Lista<Casillero*>* columnas= new Lista<Casillero*>();
				for(int x=1;x<=this->dimX;x++)
				{
					casilleroNuevo= new Casillero(x,y,z,tipoCasillero);
					columnas->add(casilleroNuevo);
				}
				pisos->add(columnas);
		}
		tableroJuego->add(pisos);
	}

	this->tableroJuego=tableroJuego;
	vincularTablero();

}


void Tablero::imprimirTablero()


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
				casilleroImprimir->imprimirPos();
			}
		}
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

Casillero * Tablero::obtenerCasillero(int x, int y, int z)
{
	Casillero * casilleroReturn = NULL;

	if(x >=1 && x <=this->dimX && y >=1 && y <=this->dimY  && z >=1 && z <=this->dimZ)
	{
		casilleroReturn = this->tableroJuego->get(z)->get(y)->get(x);
	}

	return casilleroReturn;
}

Casillero * Tablero::navegarTablero(Casillero * casilleroInicio, tipoMovimiento_t tipoMovimiento, int cantidadCasilleros)
{
	// Puntero que se retornará al final de la función
	Casillero * casilleroRetorno = casilleroInicio ;

	// Tipo de terreno inicial
	tipoCasillero_t tipoCasilleroInicio = casilleroInicio->getTipoCasillero();

	for(int i = 0 ; i < cantidadCasilleros ; i ++)
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
	}

	return casilleroRetorno;
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