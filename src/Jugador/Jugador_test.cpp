#ifndef JUGADOR_TEST__H
#define JUGADOR_TEST__H

#include <iostream>
#include "Jugador.hpp"

int main(void) {
    std::cout<<"Pruebas del TDA Jugador:\n";

    Jugador * jugador1=new Jugador(1,"Santiago");

    std::cout<<jugador1->Nombre()<<std::endl;
    std::cout<<jugador1->identificador()<<std::endl;

    std::cout<<"Cantidad de fichas:"<<jugador1->cantidadFichas()<<std::endl;

    Ficha * ficha=new Ficha(FICHA_BARCO,0,0,0);
    jugador1->agregarFicha(ficha);

    std::cout<<"Cantidad de fichas:"<<jugador1->cantidadFichas()<<std::endl;



    return 0;
}

#endif

//cmd compilacion:  g++ -o test Jugador_test.o Jugador.o ../Ficha/Ficha.o