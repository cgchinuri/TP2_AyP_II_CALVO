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
#include "../Carta_Mazo/cartaBatallaDigital.hpp"
#include "../Carta_Mazo/mazo.hpp"

class Jugador
{
private:
    std::string *nombre;
    int idJugador;
    Lista <Ficha *> * Fichas;
    Mazo <CartaBatallaDigital*> *mazoJugador;

public:

    Jugador(int id, const std::string s);
    std::string & Nombre(void);
    int identificador(void);
    
    bool moverFicha(int origenX,int origenY,int origenZ,int destinoX,int destinoY,int destinoZ);
    void moverFicha(int indiceFicha,int destinoX,int destinoY,int destinoZ);

    void agregarFicha(Ficha * nuevaFicha);
    void eliminarFicha(unsigned int pos);
    Ficha * obtenerFicha(Coordenada<int> & pos);
    Ficha * obtenerFicha(int pos);
    int cantidadFichas(void);

    /*  Muestra las fichas del jugador por la consola
    */
    void mostrarFichas(void);

    Mazo <CartaBatallaDigital*> *getMazoJugador(); 
};

#endif