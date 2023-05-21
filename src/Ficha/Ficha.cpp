#include "Ficha.hpp"




Ficha::Ficha(t_ficha tipo,Jugador * jugador,Casillero * pc) {
    this->tipo=tipo;
    this->pc=pc;
    this->pj=jugador;
}

t_ficha Ficha::getTipo(void)const  {
    return this->tipo;
}

Jugador * Ficha::getJugador(void)  {
    return this->pj;
}

Casillero *Ficha::getCasillero(void) {  
    return this->pc;
}


void Ficha::setJugador(Jugador * pj)  {
    this->pj=pj;
}
void Ficha::setCasillero(Casillero * pc)  {
    this->pc=pc;
}
void Ficha::setTipo(t_ficha tipo) {
    this->tipo=tipo;
}
