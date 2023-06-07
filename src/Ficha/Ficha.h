#ifndef FICHA__H
#define FICHA__H

#include "../Utils/Coordenada.h"
#include "../Tablero/casillero.h"

enum t_ficha    {
    FICHA_BARCO,
    FICHA_SOLDADO,
    FICHA_AVION,
    FICHA_MINA
};

class Ficha {
private:
    Coordenada<int> * coordenada;
    t_ficha tipo;
    bool activo;
    //Puntero al casillero sobre el cual está la ficha
    Casillero * casillero;
public: 

    //pre: tipo debe ser un valor de t_ficha
    //post: crea una ficha con el tipo y coordenadas indicadas
    Ficha(t_ficha tipo,int x, int y, int z);

    //pre: -
    //post: devuelve el tipo de la ficha
    t_ficha obtenerTipo(void)const;

    //pre: -
    //post: devuelve la coordenada de la ficha
    Coordenada<int> * obtenerCoordenada(void);

    //pre: -
    //post: devuelve un string con el tipo de la ficha
    std::string toStringTipo(void);

    // Pre: -
	// Pos: devuelve puntero al casillero que apunta la ficha
	Casillero * getCasilleroFicha();

    // Pre: -
	// Pos: cambia la dirección del puntero a casillero donde apunta la ficha
	void setCasilleroFicha(Casillero * casillero);

    // Pre: -
	// Pos: cambia la dirección del puntero a casillero a NULL
	void desvincularFichaDeCasillero();

    void desactivarFicha(void);
    void activarFicha(void);

};


#endif