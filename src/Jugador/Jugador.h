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
    //PRE:Recibe un número entero como id de jugador y un tipo de dato string con el nombre
    //POS:Construye un Jugador
    Jugador(int id, const std::string s);
    ~Jugador();
    //PRE:
    //POS:Retorna el nombre del jugador
    std::string & getNombre(void);

    //PRE:
    //POS:Retorna el identificador del jugador
    int getIdentificador(void);

    //PRE:El puntero a la ficha no puede ser nuo
    //POS:Asigna la ficha al jugador
    void agregarFicha(Ficha * nuevaFicha);


    void eliminarFicha(unsigned int indice);
    bool eliminarFicha(Coordenada<int> & pos);
    
    //PRE:Debe recibir una coordenada 
    //POS:Retorna la ficha cuya coordenada coincida con la pasada como argumento, o NULL 
    //si no hay ninguna que coincida
    Ficha * obtenerFicha(Coordenada<int> & pos);

    //PRE:Debe recibir una pos valida para indexar en el conjunto de fichas del jugador
    //POS:Retorna la ficha cuyo indice sea el de pos, o NULL si el indice no esta en rango
    Ficha * obtenerFicha(unsigned int pos);
    
    //PRE:
    //POS:Remueve las fichas inactivas del jugador  
    void removerFichasInactivas(void);

    //void retirarFichas(void);

    //PRE:
    //POS:Retorna cantidad de fichas del jugador
    int cantidadFichas(void);

    //PRE:
    //POS:Retorna cantidad de ficha de tipo SOLDADO del jugador
    int cantidadFichasSoldado();

    // Pre:
    // Pos: Muestra las fichas del jugador por la consola
    // 		Retorna la cantidad de fichas que mostró
    unsigned int mostrarFichas(void);

    //PRE:El puntero a la carta no puede ser nulo
    //POS:Agrega una carta al jugador
    void agregarCarta(CartaBatallaDigital * carta);

    //PRE:Debe recibir una pos valida para indexar en el conjunto cartas del jugador
    //POS:Retorna la carta cuyo indice sea el de pos, o NULL si el indice no esta en rango
    CartaBatallaDigital * obtenerCarta(int pos);

    //Devuelve la primera ocurrencia de una carta del tipo especificado, si no hay ninguna carta
    //de ese tipo retorna NULL
    CartaBatallaDigital * obtenerCarta(carta_t tipo);


    // Pre:
    // Pos: Muestra las cartas del jugador por la consola
    void mostrarCartas();
    
    // Pre:La lista de enemigos no puede ser nula
    // Pos:Agrega los casilleros detectados a los visibles para el jugador
    void setEnemigosDetectados(Lista<Casillero *> * enemigos);
    
    //PRE:
    //POS:Retorna la lista de casilleros donde se han detectado enemigos
    Lista<Casillero *> * getEnemigosDetectados(void);
    
    //PRE:Debe recibir una coordenada
    //POS:Retorna true si en la coordenada hay un enemigo detectado, false si no.
    bool fichaEnemigaDetectada(Coordenada<int> & pos);

    
    //pre:
    //pos: recorre la lista de fichas y devuelve true si hay una ficha en la coordenada con el tipo indicado en el parametro.
    bool hayTipoEnCoordenada(t_ficha tipo, unsigned int x, unsigned int y, unsigned int z);

};

#endif
