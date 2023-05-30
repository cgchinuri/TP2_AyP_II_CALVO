#include <iostream>

#include "casillero.h"

Casillero::Casillero(int x, int y, int z, tipoCasillero_t tipoCasillero)
{
	// Redundante, reemplazado por TDA coordenada
	this->x = x;
	this->y = y;
	this->z = z;

	// Inicializo TDA coordenada
	this->coordenada= new Coordenada<int>(x,y,z);


	this->tipoCasillero = tipoCasillero;

	this->sigX=NULL;
	this->sigY=NULL;
	this->sigZ=NULL;
	this->antX=NULL;
	this->antY=NULL;
	this->antZ=NULL;

	this->turnosInactivoRestantes = 0;

	// Puntero a la ficha que lo ocupa
	this->fichaOcupa = NULL;
}


int Casillero::getPosX()
{
	return this->x;
}

int Casillero::getPosY()
{
	return this->y;
}


int Casillero::getPosZ()
{
	return this->z;
}

Coordenada<int> * Casillero::getCoordenada(void)
{
	return this->coordenada;
}

void Casillero::imprimirPos()
{
	std::cout << "Posición del casillero: (" << this->x << ", "<< this->y << ", "<< this->z << ")" << std::endl;
}


tipoCasillero_t Casillero::getTipoCasillero()
{
	return this->tipoCasillero;
}

void Casillero::setTipoCasillero(tipoCasillero_t tipo)
{
	this->tipoCasillero=tipo;
}

void Casillero::imprimirTipo()
{
	this->tipoCasillero;
}

void Casillero::setSigX(Casillero * casillero)
{
	this->sigX = casillero;
}

void Casillero::setAntX(Casillero * casillero)
{
	this->antX = casillero;
}

void Casillero::setSigY(Casillero * casillero)
{
	this->sigY = casillero;
}

void Casillero::setAntY(Casillero * casillero)
{
	this->antY = casillero;
}

void Casillero::setSigZ(Casillero * casillero)
{
	this->sigZ = casillero;
}

void Casillero::setAntZ(Casillero * casillero)
{
	this->antZ = casillero;
}

Casillero * Casillero::getSigX()
{
	return this->sigX;
}

Casillero * Casillero::getAntX()
{
	return this->antX;
}

Casillero * Casillero::getSigY()
{
	return this->sigY;
}
Casillero * Casillero::getAntY()
{
	return this->antY;
}

Casillero * Casillero::getSigZ()
{
	return this->sigZ;
}

Casillero * Casillero::getAntZ()
{
	return this->antZ;
}

void Casillero::vaciarCasillero()
{
	this->fichaOcupa = NULL;
}

void Casillero::setFichaCasillero(Ficha * fichaOcupa)
{
	this->fichaOcupa = fichaOcupa;
}

Ficha * Casillero::getFichaCasillero()
{
	return this->fichaOcupa;
}

bool Casillero::estaOcupado()
{
	return (this->fichaOcupa)?true:false;
}

int Casillero::casillerosAguaAdyacentes(Casillero* casilleroActual)
{
	int casillerosConAgua=0;
	if(casilleroActual->getAntX())
	{
		if(casilleroActual->getAntX()->getTipoCasillero()==agua)
		{
			casillerosConAgua++;
		}
	}
	if(casilleroActual->getSigX())
	{
		if(casilleroActual->getSigX()->getTipoCasillero()==agua)
		{
			casillerosConAgua++;
		}
	}
	if(casilleroActual->getAntY())
	{
		if(casilleroActual->getAntY()->getTipoCasillero()==agua)
		{
			casillerosConAgua++;
		}
	}
	if(casilleroActual->getSigY())
	{
		if(casilleroActual->getSigY()->getTipoCasillero()==agua)
		{
			casillerosConAgua++;
		}
	}

	return casillerosConAgua;
}

Casillero::~Casillero()
{
	std::cout << "destructor casillero" << std::endl;
	// Libero la memoria del TDA coordenada
	delete this->coordenada;

}

//Esta primitiva retorna true si el casillero esta activo, false si no lo esta
//Nota: Esta utilizando el atributo de turnos inactivos para determinar si esta activo o no, ya que no tiene un estado esta implementacion
bool Casillero::estaActivo(void)	{
	return this->turnosInactivoRestantes==0;
}

