#include "Jugador.hpp"


int Jugador::ObtenerIdentificador() {
    return this->identificador;
}


Jugador::Jugador(int identificador)  {
    this->identificador=identificador;
}
void Jugador::PonerMina(int x,int y, int z)  {   //Implementar TDA COORDENADA  
    Mina * nuevaMina=new Mina(x,y,z);

    this->Minas->InsertarPrimero(*nuevaMina);
}