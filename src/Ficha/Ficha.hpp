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
    //atributo de estado? vivo/no

public: 
    Ficha(t_ficha tipo,int x, int y, int z);
    t_ficha obtenerTipo(void)const;
    Coordenada<int> * obtenerCoordenada(void);
};


#endif