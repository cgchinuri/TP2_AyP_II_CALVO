#include <iostream>

#include "casillero.h"

Casillero::Casillero(int x, int y, int z, tipoCasillero_t tipoCasillero)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->tipoCasillero = tipoCasillero;

	this->sigX=NULL;
	this->sigY=NULL;
	this->sigZ=NULL;
	this->antX=NULL;
	this->antY=NULL;
	this->antZ=NULL;

	this->turnosInactivoRestantes = 0;
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

void Casillero::imprimirPos()
{
	std::cout << "Posición del casillero: (" << this->x << ", "<< this->y << ", "<< this->z << ")" << std::endl;
}


tipoCasillero_t Casillero::getTipoCasillero()
{
	return this->tipoCasillero;
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