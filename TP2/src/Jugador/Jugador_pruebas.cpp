#include <iostream>
#include "Jugador.hpp"



int main(void)  {
    
    Jugador * nuevoJugador=new Jugador(1,"Santiago");
    
    //Obtener nombre e id
    std::cout<<"Jugador:"<<nuevoJugador->identificador()<<'\t'<<
    nuevoJugador->Nombre()<<std::endl;


    nuevoJugador->moverFicha(0,0,0,0,0,0);

    
    return 0;
}