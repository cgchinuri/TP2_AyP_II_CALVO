#include "cartaBatallaDigital.hpp"
#include <string>

CartaBatallaDigital::CartaBatallaDigital(carta_t tipo)
{
    this->tipo = tipo;
}

carta_t CartaBatallaDigital::getTipo()
{
    return this->tipo;
}

std::string CartaBatallaDigital::getNombre()
{
    switch (this->tipo)
    {
    case SUBMARINO:
        return "Submarino";
    case AVION_RADAR:
        return "Avion Radar";
    case TRINCHERA:
        return "Trinchera";
    case BARCO:
        return "Barco";
    case ATAQUE_QUIMICO:
        return "Ataque Quimico";
    case REFUERZOS:
        return "Refuerzos";
    
    default:
        throw "Esto no deberia pasar";
    };
}

std::string CartaBatallaDigital::getDescripcion()
{
    switch (this->tipo)
    {
    case SUBMARINO:
        return "Agrega una unidad a la armada del jugador [AGUA PROFUNDIDAD MINIMA]";
    case AVION_RADAR:
        return "Avion Radar le agrega una unidad a la fuerza aérea del jugador, capaz de detectar ... [AIRE ALTURA MINIMA]";
    case TRINCHERA:
        return "Trinchera le permite convertir un soldado en una trinchera por -- turnos, la cual eliminara soldados enemigos. El soldado queda imovil pero es inmune a soldados enemigos[TIERRA PROFUNDIDAD]";
    case BARCO:
        return "La carta barco le agrega una unidad a la armada del jugador [SUPERFICIE DE AGUA]";
    case ATAQUE_QUIMICO:
        return "Ataque quimico! Ataca ";
    case REFUERZOS:
        return "Agrega un soldado al ejercito del jugador [SUPERFICIE DE TIERRA]";
    
    default:
        throw "Esto no deberia pasar";
    };
}

// Funcion, no metodo
CartaBatallaDigital ** iniciarCartas() {
    CartaBatallaDigital *cartaSubmarino = new CartaBatallaDigital(SUBMARINO);
    CartaBatallaDigital *cartaAvion = new CartaBatallaDigital(AVION_RADAR);
    CartaBatallaDigital *cartaTrinchera = new CartaBatallaDigital(TRINCHERA);
    CartaBatallaDigital *cartaBarco = new CartaBatallaDigital(BARCO);
    CartaBatallaDigital *cartaQuimico = new CartaBatallaDigital(ATAQUE_QUIMICO);
    CartaBatallaDigital *cartaRefuerzos = new CartaBatallaDigital(REFUERZOS);

    CartaBatallaDigital *vectorAux[] = {
    cartaSubmarino, cartaAvion, cartaTrinchera, cartaBarco, cartaQuimico, cartaRefuerzos
    };

    unsigned int cantidadCartas = sizeof(vectorAux)/sizeof(vectorAux[0]);

    CartaBatallaDigital **vectorCartas = new CartaBatallaDigital*[cantidadCartas + 1];

    for (unsigned int i = 0; i < cantidadCartas; i++)
    {
        vectorCartas[i] = vectorAux[i];
    }

    vectorCartas[cantidadCartas] = NULL;

    return vectorCartas;
}