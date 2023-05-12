/*
 * Jugador.hpp
 *
 *  Created on: 03 May. 2023
 *      Author: Ponce Santiago
 */

#ifndef JUGADOR__H
#define JUGADOR__H

#include <iostream>
#include "../Utils/Lista/LinkedList_T.hpp"
#include "../Utils/Coordenada/Coordenada.hpp"

typedef int Ficha;//Para que compile

class Jugador
{
private:
    std::string *nombre;
    int idJugador;
    Lista <Ficha *> * Fichas;

public:
    Jugador(int id, const std::string s);
    std::string & Nombre(void);
    int identificador(void);
    
    bool moverFicha(int origenX,int origenY,int origenZ,int destinoX,int destinoY,int destinoZ);
    void agregarFicha(Ficha * nuevaFicha);
    Ficha * obtenerFicha(Coordenada<int> & pos);
    void eliminarFicha(Coordenada<int> & pos);
};

#endif
