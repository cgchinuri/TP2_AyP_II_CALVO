#include "mazo.hpp"
#include "cartaBatallaDigital.hpp"
#include <iostream>

//------FUNCION NO METODO-----------
// POS: Devuelve un arreglo dinamico de punteros a cada carta distinta 
CartaBatallaDigital** iniciarCartas() {
	CartaBatallaDigital **vectorCartas = new CartaBatallaDigital*[7];

	
	vectorCartas[0] = new CartaBatallaDigital(SUBMARINO);
    vectorCartas[1] = new CartaBatallaDigital(AVION_RADAR);
    vectorCartas[2] = new CartaBatallaDigital(TRINCHERA);
    vectorCartas[3] = new CartaBatallaDigital(BARCO);
    vectorCartas[4] = new CartaBatallaDigital(ATAQUE_QUIMICO);
    vectorCartas[5] = new CartaBatallaDigital(REFUERZOS);
	vectorCartas[6] = NULL;
	
	/*
	CartaBatallaDigital *cartaSubmarino = new CartaBatallaDigital(SUBMARINO);
    CartaBatallaDigital *cartaAvion = new CartaBatallaDigital(AVION_RADAR);
    CartaBatallaDigital *cartaTrinchera = new CartaBatallaDigital(TRINCHERA);
    CartaBatallaDigital *cartaBarco = new CartaBatallaDigital(BARCO);
    CartaBatallaDigital *cartaQuimico = new CartaBatallaDigital(ATAQUE_QUIMICO);
    CartaBatallaDigital *cartaRefuerzos = new CartaBatallaDigital(REFUERZOS);
	*/

	return vectorCartas;
}

Mazo<CartaBatallaDigital*>* iniciarMazoComun(CartaBatallaDigital **vectorCartas) {
	
	Mazo<CartaBatallaDigital*>* mazoComun = new Mazo<CartaBatallaDigital*>;

	
	CartaBatallaDigital *carta;
	unsigned int i = 0;
	while((carta=vectorCartas[i]))
	{
		mazoComun->agregarCarta(carta, carta->getCantidadRepeticiones());
		i++;
	}

	mazoComun->mezclar();
	return mazoComun;	
}

int main() {
	CartaBatallaDigital **vectorCartas = iniciarCartas();
	Mazo<CartaBatallaDigital*>* mazoComun = iniciarMazoComun(vectorCartas);
	
	for (unsigned int i = 0; i < 10; i++)
	{
		if(!mazoComun->vacio())
			std::cout<<mazoComun->pop()->getNombre()<<std::endl;
	}

	for	(unsigned int i = 0; vectorCartas[i]; i++)
	{
		delete vectorCartas[i];
	}
	delete [] vectorCartas;
	delete mazoComun;
}