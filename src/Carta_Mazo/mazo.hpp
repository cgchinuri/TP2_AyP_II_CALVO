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
	T getCarta();
	void reiniciarCursor();
	bool avanzarCursor();
	T getCursor()const;
	~Mazo();
};

template<class T> Mazo<T>::Mazo() {
	this->listaCartas = new Lista<T>();
	this->estado = NO_MEZCLADO;
}

template<class T> void Mazo<T>::mezclar() {
	this->estado = MEZCLADO;
}

template<class T> void Mazo<T>::reordenar() {
	this->estdo = NO_MEZCLADO;
}

template<class T> bool Mazo<T>::vacio() const{
	return (this->listaCartas->contarElementos() == 0);
}

template<class T> unsigned int Mazo<T>::contarCartas()const {
	return this->listaCartas->contarElementos();
}

template<class T> void Mazo<T>::agregarCarta(T carta) {
	this->listaCartas->add(carta);
}

template<class T> void Mazo<T>::agregarCarta(T carta, unsigned int cantidad) {
	for (unsigned int i = 0; i < cantidad; i++)
		this->agregarCarta(carta);
}

template<class T> T Mazo<T>::getRandom()
{
	srand((unsigned) time(NULL));
	unsigned int randomInt;
	randomInt = (rand() % this->contarCartas()) + 1;
	T cartaRandom = listaCartas->get(randomInt);
	listaCartas->remover(randomInt);
	return cartaRandom;
}

template<class T> T Mazo<T>::pop()
{
	if (estado == MEZCLADO) return this->getRandom();
	T carta = listaCartas->get(1);
	listaCartas->remover(1);
	return carta;
}

template<class T> T Mazo<T>::getCarta(unsigned int posicion)
{
	if (estado == MEZCLADO) return this->getRandom();
	T carta = listaCartas->get(posicion);
	listaCartas->remover(posicion);
	return carta;
}

template<class T> T Mazo<T>::getCarta()
{
	return this->pop();
}

template<class T> void Mazo<T>::reiniciarCursor() {
	this->listaCartas->reiniciarCursor();
}

template<class T> bool Mazo<T>::avanzarCursor(){
	return this->listaCartas->avanzarCursor();
}
template<class T> T Mazo<T>::getCursor()const{
	return this->listaCartas->getCursor();
}

template<class T> Mazo<T>::~Mazo() {
	delete listaCartas;
}

#endif // MAZO_H