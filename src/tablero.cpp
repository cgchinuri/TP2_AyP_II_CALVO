#include <iostream>


#include "lista.h"
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
					columnas->agregar(casilleroNuevo);
				}
				pisos->agregar(columnas);
		}
		tableroJuego->agregar(pisos);
	}

	this->tableroJuego=tableroJuego;

}


void Tablero::imprimirTablero()


{
	Casillero* casilleroImprimir = NULL;
	Lista<Lista<Casillero*>* >* pisosRecorrer=NULL;
	Lista<Casillero*>* columnasRecorrer=NULL;
	for(int z = 1 ; z <= this->dimZ ; z++)
	{
		pisosRecorrer=this->tableroJuego->obtener(z);
		for(int y = 1 ; y <= this->dimY ; y++)
		{
			columnasRecorrer=pisosRecorrer->obtener(y);
			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casilleroImprimir=columnasRecorrer->obtener(x);
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
		columnaAnterior = this->tableroJuego->obtener(nivel)->obtener(i);

		for(int j = 1 ; j < this->dimX ; j++)
		{
			casilleroAntX = columnaAnterior->obtener(j);
			casilleroSigX = columnaAnterior->obtener(j+1);

			casilleroAntX->setSigX(casilleroSigX);
			casilleroSigX->setAntX(casilleroAntX);
		}
	}


	// Vinculación de columnas entre si
	for(int i = 1 ; i < this->dimY ; i++)
	{
		columnaAnterior = this->tableroJuego->obtener(nivel)->obtener(i);
		columnaSiguiente = this->tableroJuego->obtener(nivel)->obtener(i+1);

		for(int j = 1 ; j <= this->dimX ; j++)
		{
			casilleroAntY = columnaAnterior->obtener(j);
			casilleroSigY = columnaSiguiente->obtener(j);

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
		pisoActual=this->tableroJuego->obtener(z);
		pisoSiguiente=this->tableroJuego->obtener(z+1);
		for(int y = 1 ; y <= this->dimY ; y++)
		{
			columnasInicial=pisoActual->obtener(y);
			columnasSiguiente=pisoSiguiente->obtener(y);
			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casilleroVincularInicial=columnasInicial->obtener(x);
				casilleroVincularSiguiente=columnasSiguiente->obtener(x);
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
		piso=this->tableroJuego->obtener(z);
		for(int y = 1 ; y <= this->dimY ; y++)
		{
			columna=piso->obtener(y);
			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casillero=columna->obtener(x);
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
		casilleroReturn = this->tableroJuego->obtener(z)->obtener(y)->obtener(x);
	}

	return casilleroReturn;
}

Tablero::~Tablero()
{}