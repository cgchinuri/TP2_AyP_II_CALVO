#include "Jugador.hpp"


int Jugador::ObtenerIdentificador() {
    return this->identificador;
}


Jugador::Jugador(int identificador)  {
    this->identificador=identificador;
}