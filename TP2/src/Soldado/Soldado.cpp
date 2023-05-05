#include "Soldado.hpp"

Soldado::Soldado(int jugadorId,int x, int y, int z) {
    this->posicion=new(Coordenada_t);

    this->posicion->x=x;
    this->posicion->y=y;
    this->posicion->z=z;

    this->vive=true;
    this->jugadorId=jugadorId;
}


const Coordenada_t & Soldado::ObtenerPosicion(void)  {
    return *(this->posicion);
}

int Soldado::JugadorAsociado(void)  {
    return this->jugadorId;
}

void Soldado::Mover(int x, int y, int z)    {
    this->posicion->x+=x;
    this->posicion->y+=y;
    this->posicion->z+=z;
    return;
}

void Soldado::DarBaja(void) {
    this->vive=false;
}
bool Soldado::EstaVivo(void)    {
    return this->vive;
}