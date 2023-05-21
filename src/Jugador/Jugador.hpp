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
#include "../Ficha/Ficha.hpp"

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
    
    void agregarFicha(Ficha * nuevaFicha);
    Ficha * obtenerFicha(Coordenada<int> & pos);
    int cantidadFichas(void);
    //void eliminarFicha(Coordenada<int> & pos);
};

#endif
