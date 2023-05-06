#include "carta.hpp"
#include <random>
#include <iostream>

tipoCarta_t calculoProbabilidad(std::map<tipoCarta_t, double> probabilidadesCartas)
{
    std::random_device generador;
    std::uniform_real_distribution<double> distribucion(0, 1);
    double probabilidad = distribucion(generador);

    std::map<tipoCarta_t, double>::iterator it;
    for (it = probabilidadesCartas.begin(); it != probabilidadesCartas.end(); it++)
    {
            if(probabilidad < it->second)
                return it->first;
            probabilidad -= it->second;
    }

    throw("Esto no deberia pasar");
}

Carta::Carta()
{
    try
    {
    this->tipo = calculoProbabilidad(probabilidadesCartas);
    }
    catch (...)
    {
        std::cout << "Error en creacion de carta" << std::endl;
    }
}

tipoCarta_t Carta::getTipoCarta()
{
    return this->tipo;
}

std::string Carta::cartaToString()
{
    return cadenasCartas[this->tipo];
}