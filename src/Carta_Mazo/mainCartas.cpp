#include "mazo.hpp"
#include "cartaBatallaDigital.hpp"
#include <iostream>

Mazo<CartaBatallaDigital*>* inciarMazoComun(CartaBatallaDigital **arregloCartas) {
	
	unsigned int vectorCantidadCartas[] = {
	[SUBMARINO] = 15, [AVION_RADAR] = 25, [TRINCHERA] = 40, 
	[BARCO] = 30, [ATAQUE_QUIMICO] = 10, [REFUERZOS] = 50};
	Mazo<CartaBatallaDigital*>* mazoComun = new Mazo<CartaBatallaDigital*>;
	for (size_t i = 0; arregloCartas[i] != NULL; i++)
	{
		mazoComun->agregarCarta(arregloCartas[i], vectorCantidadCartas[arregloCartas[i]->getTipo()]);
	}

	mazoComun->mezclar();
	return mazoComun;	
}

int main() {
	CartaBatallaDigital **arregloCartas = iniciarCartas();
	Mazo<CartaBatallaDigital*>* mazoComun = inciarMazoComun(arregloCartas);
	for (unsigned int i = 0; i < 10; i++)
	{
		if(!mazoComun->vacio())
			std::cout<<mazoComun->pop()->getNombre()<<std::endl;
	}
	
	delete mazoComun;
	delete [] arregloCartas;
}