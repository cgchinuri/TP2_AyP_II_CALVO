/*
 * mazo.hpp
 *
 *  Created on: 20 May. 2023
 *      Author: Facundo Baratta
 * 
 * "mazo" utiliza lista ligada. Si no esta mezclado, es identico a una lista.
 * 	Si esta mezclado, devuelve una carta aleatoria.
 */

#ifndef MAZO_H
#define MAZO_H

#include <cstdlib>
#include <ctime>
#include "../Utils/Lista/LinkedList_T.hpp"



typedef enum {MEZCLADO, NO_MEZCLADO} estadoMazo_t;

template<class T> class Mazo {
private:
	Lista<T>* listaCartas;
	estadoMazo_t estado;
	T getRandom();
public:
	Mazo();
	void mezclar();
	void reordenar();
	bool vacio()const;
	unsigned int contarCartas()const;
	void agregarCarta(T carta);
    void agregarCarta(T carta, unsigned int cantidad);
	T pop();
	T getCarta(unsigned int posicion);
	void reiniciarCursor();
	bool avanzarCursor();
	T getCursor()const;
	~Mazo();
};

// POS: Devuelve un mazo en memoria dinamico no mezclado
template<class T> Mazo<T>::Mazo() {
	this->listaCartas = new Lista<T>();
	this->estado = NO_MEZCLADO;
}

// POS: Mezcla el mazo. Si esta mezcaldo, devuelve una carta aleatoria
template<class T> void Mazo<T>::mezclar() {
	this->estado = MEZCLADO;
}

// POS: Reordena el mazo como estaba anteriormente. Devuelve las cartas en orden
template<class T> void Mazo<T>::reordenar() {
	this->estdo = NO_MEZCLADO;
}

// POS: Devuelve true si no hay mas cartas en el mazo
template<class T> bool Mazo<T>::vacio() const{
	return (this->listaCartas->contarElementos() == 0);
}

// POS: Devuelve la cantidad de cartas en el mazo
template<class T> unsigned int Mazo<T>::contarCartas()const {
	return this->listaCartas->contarElementos();
}

// PRE: Recibe una carta valida
// POS: La agrega al final del mazo
template<class T> void Mazo<T>::agregarCarta(T carta) {
	if (carta == NULL) {
		throw "Carta invalida";
	}
	this->listaCartas->add(carta);
}

// PRE: Recibe una carta valida y una cantidad de repiticiones
// POS: Agrega la carta al final 'cantidad' veces
template<class T> void Mazo<T>::agregarCarta(T carta, unsigned int cantidad) {
	for (unsigned int i = 0; i < cantidad; i++)
		this->agregarCarta(carta);
}

// POS: Devuelve la carta al principio del mazo, eliminandola de este
template<class T> T Mazo<T>::pop()
{
	if (estado == MEZCLADO) return this->getRandom();
	T carta = listaCartas->get(1);
	listaCartas->remover(1);
	return carta;
}

// PRE: Recibe una posicion válida [1 , countElements()]
// POS: Devuelve la carta en la posicion, eliminandola del mazo
template<class T> T Mazo<T>::getCarta(unsigned int posicion)
{
	if(!posicion || posicion > this->contarCartas()) {
		throw "Posicion invalida";
	}

	if (estado == MEZCLADO) {
		return this->getRandom();
	}

	T carta = listaCartas->get(posicion);
	listaCartas->remover(posicion);
	return carta;
}

// PRE Y POS CONDICIONES DE CURSOR IDENTICAS A LA DE LISTA. VER LinkedList_T.hpp
template<class T> void Mazo<T>::reiniciarCursor() {
	this->listaCartas->reiniciarCursor();
}
template<class T> bool Mazo<T>::avanzarCursor(){
	return this->listaCartas->avanzarCursor();
}
template<class T> T Mazo<T>::getCursor()const{
	return this->listaCartas->getCursor();
}

// POS: Libera la memoria de la lista de cartas.
template<class T> Mazo<T>::~Mazo() {	
	delete listaCartas;
}

// Funcion privada -- POS: Devuelve una carta al azar para el mazo esta mezclado
template<class T> T Mazo<T>::getRandom()
{
	srand((unsigned) time(NULL));
	unsigned int randomInt;
	randomInt = (rand() % this->contarCartas()) + 1;
	T cartaRandom = listaCartas->get(randomInt);
	listaCartas->remover(randomInt);
	return cartaRandom;
}
#endif // MAZO_H