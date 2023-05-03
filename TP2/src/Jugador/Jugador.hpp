/*
 * Jugador.hpp
 *
 *  Created on: 03 May. 2023
 *      Author: Ponce Santiago
 */

#ifndef JUGADOR__H 
#define JUGADOR__H

#include "Utils/Lista/LinkedList_T.hpp"

class Jugador {
private:
    int identificador;
    ListaEnlazada<Mina> * Minas;
    ListaEnlazada<Soldado> * Soldados;    
    ListaEnlazada<Barco> * Barcos;
    ListaEnlazada<Avion> * Aviones;    


   

public:
    Jugador(int identificador);
    int ObtenerIdentificador();
    void MoverSoldado();
    void PonerMina();
    
    

};









#endif
