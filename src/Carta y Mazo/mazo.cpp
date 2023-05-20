#include "carta.hpp"
#include <map>

std::map<tipoCarta_t, unsigned int> cantidadCartas =
{
{SUBMARINO, 3},
{AVION_RADAR, 10},
{TRINCHERA, 12},
{BARCO, 10},
{ATAQUE_QUIMICO, 4},
{REFUERZOS, 14}
};

class Mazo
{
    private:
    Lista<Carta*> *listaCartas;

    publica:
    Mazo();
    agregarCarta(Carta *carta);
}

Mazo::Mazo()
{
    this->listaCartas = new Lista<Carta*>;
}
