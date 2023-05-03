#include <iostream>
#include "Jugador.hpp"



int main(void)  {
    Jugador * j1=new Jugador(3);

    std::cout<<j1->ObtenerIdentificador()<<std::endl;
    return 0;
}