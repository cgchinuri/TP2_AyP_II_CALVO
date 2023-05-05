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

    if (probabilidad < 0.2) this->nombre = REFUERZOS;
    if (probabilidad >= 0.2 && probabilidad < 0.4) this->nombre = AVION_RADAR;
    if (probabilidad >= 0.4 && probabilidad < 0.6) this->nombre = TRINCHERA;
    if (probabilidad >= 0.6 && probabilidad < 0.8) this->nombre = BARCO;
    else this->nombre = SUBMARINO;


nombreCarta_t Carta::getNombreCarta()
{
    return this->nombre;
}


std::string Carta::cartaToString()
{
    switch (this->nombre)
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