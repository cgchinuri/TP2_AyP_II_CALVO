/*
 * Jugador.hpp
 *
 *  Created on: 03 May. 2023
 *      Author: Ponce Santiago
 */

#ifndef JUGADOR__H
#define JUGADOR__H

#include <iostream>
#include "../Utils/LinkedList_T.h"
#include "../Utils/Coordenada.h"
#include "../Ficha/Ficha.h"
#include "../Carta_Mazo/cartaBatallaDigital.h"

class Jugador
{
private:
    std::string *nombre;
    int idJugador;
    Lista <Ficha *> * Fichas;
    Mazo <CartaBatallaDigital*> * Cartas;

public:
    Jugador(int id, const std::string s);
    std::string & Nombre(void);
    int identificador(void);
    

    void agregarFicha(Ficha * nuevaFicha);
    void eliminarFicha(unsigned int indice);
    bool eliminarFicha(Coordenada<int> & pos);
    
    Ficha * obtenerFicha(Coordenada<int> & pos);
    Ficha * obtenerFicha(unsigned int pos);

    //Este metodo (quizas deberia ser privado) elimina las fichas que esten inactivas
    void removerFichasInactivas(void);
    void retirarFichas(void);
    
    int cantidadFichas(void);
    int cantidadFichasSoldado();

    //Muestra las fichas del jugador por la consola
    void mostrarFichas(void);
    void agregarCarta(CartaBatallaDigital * carta);
    CartaBatallaDigital * obtenerCarta(int pos);
    void mostrarCartas();

};

#endif
