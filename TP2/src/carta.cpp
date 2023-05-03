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

    if (probabilidad < 0.1) this->nombre = SOLDADO_EXTRA;
    if (probabilidad >= 0.1 && probabilidad < 0.2) this->nombre = AVION;
    if (probabilidad >= 0.2 && probabilidad < 0.3) this->nombre = TRINCHERA;
    if (probabilidad >= 0.3 && probabilidad < 0.4) this->nombre = BARCO;
    if (probabilidad >= 0.4 && probabilidad < 0.5) this->nombre = CONVERSION_SOLDADO;
    if (probabilidad >= 0.5 && probabilidad < 0.6) this->nombre = ROBO_VEHICULO;
    if (probabilidad >= 0.6 && probabilidad < 0.7) this->nombre = SUBMARINO;
    if (probabilidad >= 0.7 && probabilidad < 0.8) this->nombre = ATAQUE_AEREO;
    if (probabilidad >= 0.8 && probabilidad < 0.9) this->nombre = INVESTIGACION_BOMBA_NUCLEAR;
    else this->nombre = SOLDADO_EXTRA;
}

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
    case ROBO_VEHICULO:
        return "Robo de Vehiculo";
    case CONVERSION_SOLDADO:
        return "Conversion de Soldado Enemigo";
    case AVION:
        return "Soporte Aereo";
    case TRINCHERA:
        return "Cavar Trinchera";
    case BARCO:
        return "Barco";
    case ATAQUE_AEREO:
        return "Bombardeo Aereo";
    case INVESTIGACION_BOMBA_NUCLEAR:
        return "Investigacion Atomica";
    case SOLDADO_EXTRA:
        return "Refuerzos de infanteria";
    default:
        return "DESCONOCIDO";
    };
}