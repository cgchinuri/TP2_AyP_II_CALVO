#ifndef JUGADOR_TEST__H
#define JUGADOR_TEST__H

#include <iostream>
#include "Jugador.hpp"
#include "../Carta_Mazo/cartaBatallaDigital.hpp"

int main(void) {
    std::cout<<"Pruebas del TDA Jugador:\n";

    Jugador * jugador1=new Jugador(1,"Jugador 1");

    std::cout<<"Nombre:"<<jugador1->Nombre()<<std::endl;
    std::cout<<"id:"<<jugador1->identificador()<<std::endl;

    std::cout<<"Cantidad de fichas:"<<jugador1->cantidadFichas()<<std::endl;

    Ficha * barco1=new Ficha(FICHA_BARCO,0,0,0);
    Ficha * soldado1=new Ficha(FICHA_SOLDADO,0,1,0);
    Ficha * avion1=new Ficha(FICHA_AVION,0,1,10);
    Ficha * mina1= new Ficha(FICHA_MINA,0,3,0); 

    jugador1->agregarFicha(barco1);
    jugador1->agregarFicha(soldado1);
    jugador1->agregarFicha(avion1);
    jugador1->agregarFicha(mina1);

    

    std::cout<<"Cantidad de fichas:"<<jugador1->cantidadFichas()<<std::endl;

    jugador1->mostrarFichas();

    std::cout<<"Obtener ficha en pos 3"<<jugador1->obtenerFicha(3)->obtenerCoordenada()->toString()<<std::endl;//esperado 0,1,10
    std::cout<<"Obtener ficha en pos 4"<<jugador1->obtenerFicha(4)->obtenerCoordenada()->toString()<<std::endl;//esperado 0,3,0
    //std::cout<<jugador1->obtenerFicha(5)->obtenerCoordenada()->toString()<<std::endl;//Fuera de rango. Esperado :? Explota

    std::cout<<"Eliminar ficha pos 3:"<<std::endl;
    jugador1->eliminarFicha(3);
    jugador1->mostrarFichas();

    
    std::cout<<"Obtener ficha en pos 3"<<jugador1->obtenerFicha(3)->obtenerCoordenada()->toString()<<std::endl;//esperado 0,3,0

    std::cout<<"Desplazar ficha de pos 3 en (5,5,5)"<<std::endl;
    std::cout<<jugador1->obtenerFicha(3)->toStringTipo()<<jugador1->obtenerFicha(3)->obtenerCoordenada()->toString()<<std::endl;
    jugador1->moverFicha(3,5,5,5);
    std::cout<<jugador1->obtenerFicha(3)->toStringTipo()<<jugador1->obtenerFicha(3)->obtenerCoordenada()->toString()<<std::endl;


    jugador1->mostrarFichas();

    //Integracion del mazo

    CartaBatallaDigital * cartaAvion=new CartaBatallaDigital(AVION_RADAR);
    CartaBatallaDigital * cartaQuimica=new CartaBatallaDigital(ATAQUE_QUIMICO);
    CartaBatallaDigital * cartaTrinchera=new CartaBatallaDigital(TRINCHERA);

    jugador1->agregarCarta(cartaAvion);
    jugador1->agregarCarta(cartaQuimica);
    jugador1->agregarCarta(cartaTrinchera);


    jugador1->mostrarCartas();
    jugador1->obtenerCarta(1);
        jugador1->mostrarCartas();

    return 0;
}

#endif

//comando compilacion:  g++ -o test Jugador_test.o Jugador.o ../Ficha/Ficha.o ../Carta_Mazo/cartaBatallaDigital.o