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
    std::string * nombre;
    int identificador;
    ListaEnlazada<Mina> * Minas;
    ListaEnlazada<Soldado> * Soldados;    
    ListaEnlazada<Barco> * Barcos;
    ListaEnlazada<Avion> * Aviones;    


   

public:
    Jugador(int identificador);
    int ObtenerIdentificador();
    void MoverSoldado( pos origen, pos destino);//Si no hay un soldado en la pos origen arrojará error
    void PonerMina(int, int, int);

    
    

};









#endif
