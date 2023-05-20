#include "carta.hpp"
#include <string>

Carta::Carta(tipoCarta_t tipo)
{
    this->tipo = tipo;
}

std::string Carta::cartaToString()
{
    return cadenasCartas[this->tipo];
}