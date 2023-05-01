#include <iostream>

#include "tablero.h"

Tablero::Tablero(int dimX, int dimY, int dimZ)
{
	this->dimX = dimX;
	this->dimY = dimY;
	this->dimZ = dimZ;

	Casillero * casilleroNuevo = NULL;
	Casillero * casilleroAnterior = NULL;

	Casillero * inicioFilaNueva = NULL;
	Casillero * inicioFilaAnterior = NULL;

	Casillero * inicioPisoNuevo = NULL;
	Casillero * inicioPisoAnterior = NULL;

	this->listaCasillerosInactivos = NULL;

	tipoCasillero_t tipoCasillero = tierra;


	for(int z = 1 ; z <= dimZ ; z++)
	{
		for(int y = 1 ; y <= dimY ; y++)
		{
			casilleroAnterior = NULL;

			for(int x = 1 ; x <= dimX ; x++)
			{
				casilleroNuevo = new Casillero(x,y,z,tipoCasillero);

				casilleroNuevo->setAntX(casilleroAnterior);

				if(casilleroAnterior)
				{
					casilleroAnterior->setSigX(casilleroNuevo);
				}

				if(x==1 && y== 1 && z == 1)
				{
					this->casilleroInicial = casilleroNuevo;

					inicioPisoNuevo = casilleroNuevo;

					inicioFilaNueva = casilleroNuevo;
				}
				else if(x==1 && y== 1)
				{
					inicioPisoAnterior = inicioPisoNuevo;
					inicioPisoNuevo = casilleroNuevo;

					inicioFilaNueva = casilleroNuevo;

					inicioPisoAnterior->setSigZ(inicioPisoNuevo);
					inicioPisoNuevo->setAntZ(inicioPisoAnterior);
				}
				else if(x==1)
				{
					inicioFilaAnterior = inicioFilaNueva;
					inicioFilaNueva = casilleroNuevo;

					inicioFilaAnterior->setSigY(inicioFilaNueva);
					inicioFilaNueva-> setAntY(inicioFilaAnterior);
				}

				casilleroAnterior=casilleroNuevo;
			}
		}
	}
}



void Tablero::imprimirTablero()
{
	Casillero * casilleroAux = this->casilleroInicial;
	Casillero * casilleroInicioFila = this->casilleroInicial;
	Casillero * casilleroInicioPiso = this->casilleroInicial;

	for(int z = 1 ; z <= this->dimZ ; z++)
	{
		casilleroInicioFila = casilleroInicioPiso;

		for(int y = 1 ; y <= this->dimY ; y++)
		{
			casilleroAux = casilleroInicioFila;

			for(int x = 1 ; x <= this->dimX ; x++)
			{
				casilleroAux->imprimirPos();

				casilleroAux = casilleroAux->getSigX();
			}

			casilleroInicioFila = casilleroInicioFila->getSigY();

		}

		casilleroInicioPiso = casilleroInicioPiso->getSigZ();
	}
}