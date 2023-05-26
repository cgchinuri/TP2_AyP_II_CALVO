#ifndef FICHA__H
#define FICHA__H

#include "../Utils/Coordenada/Coordenada.hpp"

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
};


#endif