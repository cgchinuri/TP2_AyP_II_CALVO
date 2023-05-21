#include <stdexcept>
#include "Jugador.hpp"

Jugador::Jugador(int id,const std::string s)   {
    this->idJugador=id;
    this->nombre=new std::string(s);
    this->Fichas= new Lista <Ficha *>();
}  


std::string & Jugador::Nombre(void)  {
    return *(this->nombre);
}

int Jugador::identificador(void)    {
    return this->idJugador;
}

/* Con la implementacion actual esta primitiva ya no le pertenece al jugador, ya que si quisiera
    mover una ficha deberia:
        -   Pedirle al tablero el casillero en la posicion deseada
        -   Chequear si el casillero de destino esta apuntando a algo
        -   Eliminar ese algo... etc etc etc.
bool Jugador::moverFicha(int origenX,int origenY,int origenZ,int destinoX,int destinoY,int destinoZ) {
    Coordenada origen(origenX,origenY,origenZ);
    Coordenada destino(destinoX,destinoY,destinoZ);

    Ficha * ficha;

    if(this->Fichas->vacia())   {
        throw std::invalid_argument("Fichas no disponibles");
    }

    while(this->Fichas->avanzarCursor())   {
        if(Fichas->getCursor()->obtenerCasillero()->obtenerCoordenada()->iguales(origen)==true) {
            Fichas->getCursor()->obtenerCasillero()->obtenerCoordenada()->sumar(destino);
            Fichas->reiniciarCursor();
            return true;
        }
    }

    Fichas->reiniciarCursor();
    return false;

}
*/
void Jugador::agregarFicha(Ficha * nuevaFicha)  {
    this->Fichas->add(nuevaFicha);
}


Ficha * Jugador::obtenerFicha(Coordenada<int> & pos) {
    while(this->Fichas->avanzarCursor())   {
        if(Fichas->getCursor()->obtenerCasillero()->obtenerCoordenada()->iguales(pos)==true)    {
            Fichas->reiniciarCursor();
            return Fichas->getCursor();
        }
    }
    Fichas->reiniciarCursor();
    return NULL;
}


int Jugador::cantidadFichas(void)   {
    return this->Fichas->contarElementos();
}
