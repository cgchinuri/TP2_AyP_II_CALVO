#include "Ficha.hpp"




Ficha::Ficha(t_ficha tipo,int x, int y, int z)  {
    this->tipo=tipo;
    this->coordenada=new Coordenada<int>(x,y,z);
    this->activo=true;
}

t_ficha Ficha::obtenerTipo(void)const  {
        return this->tipo;
    }

Coordenada<int> * Ficha::obtenerCoordenada(void)  {
    return this->coordenada;
}