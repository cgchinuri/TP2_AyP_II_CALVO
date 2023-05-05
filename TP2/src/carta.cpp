#include "carta.hpp"
#include <random>

double generarNumeroAleatorio(double parametroLambda)
{
  std::random_device generador;
  std::exponential_distribution<double> distribucion(parametroLambda);

  return distribucion(generador);
}

Carta::Carta()
{
    double probabilidad = generarNumeroAleatorio(LAMBDA);

    if (probabilidad < 0.2) this->tipo = REFUERZOS;
    if (probabilidad >= 0.2 && probabilidad < 0.4) this->tipo = AVION_RADAR;
    if (probabilidad >= 0.4 && probabilidad < 0.6) this->tipo = TRINCHERA;
    if (probabilidad >= 0.6 && probabilidad < 0.8) this->tipo = BARCO;
    else this->tipo = SUBMARINO;
}

tipoCarta_t Carta::getTipoCarta()
{
    return this->tipo;
}


std::string Carta::cartaToString()
{
    switch (this->tipo)
    {
    case SUBMARINO:
        return "Submarino";
    case ATAQUE_QUIMICO:
        return "Ataque Quimico";
    case REFUERZOS:
        return "Refuerzos de Infantería";
    case AVION_RADAR:
        return "Radar Aereo Movil";
    case TRINCHERA:
        return "Cavar Trinchera";
    case BARCO:
        return "Barco";
    default:
        return "DESCONOCIDO";
    };
}