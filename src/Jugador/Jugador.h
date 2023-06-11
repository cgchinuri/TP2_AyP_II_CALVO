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
    Lista<Casillero *> * enemigosDetectados;
    Mazo <CartaBatallaDigital*> * Cartas;

public:
    Jugador(int id, const std::string s);
    std::string & getNombre(void);
    int getIdentificador(void);
    
    //Recibe un puntero a una ficha y la agrega sus fichas
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
    int cantidadFichasBarco();
    int cantidadFichasAvion();
    int cantidadFichasSubmarino();
    //Muestra las fichas del jugador por la consola
    void mostrarFichas(void);
    void agregarCarta(CartaBatallaDigital * carta);
    CartaBatallaDigital * obtenerCarta(int pos);
    void mostrarCartas();
    void setEnemigosDetectados(Lista<Casillero *> * enemigos);
    
    //pre:
    //pos: recorre la lista de fichas y devuelve true si hay una ficha en la coordenada con el tipo indicado en el parametro.
    bool hayTipoEnCoordenada(t_ficha tipo, unsigned int x, unsigned int y, unsigned int z);

};

#endif
