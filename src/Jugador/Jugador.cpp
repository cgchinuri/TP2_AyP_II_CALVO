#include "Jugador.hpp"
#include <stdexcept>
 
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

/*  Recibe una posicion de origen y de destino, si hay alguna ficha con la posicion de origen => 
establece su posicion con las coordenadas del destino. Retorna true si pudo mover, false si no.
*/
bool Jugador::moverFicha(int origenX,int origenY,int origenZ,int destinoX,int destinoY,int destinoZ) {
    Coordenada origen(origenX,origenY,origenZ);
    Ficha * ficha;

    if(this->Fichas->vacia())   {
        throw std::invalid_argument("Fichas no disponibles");
    }

    while(this->Fichas->avanzarCursor())   {
        if(this->Fichas->getCursor())   {//Si la ficha actual tiene la posicion de origen...... (usar primitivas de ficha)
            this->Fichas->getCursor();//Cambiar coordenada de la ficha
           // ....
            return true;
        }
    }

    Fichas->reiniciarCursor();
    return false;

}

void Jugador::agregarFicha(Ficha * nuevaFicha)  {
    this->Fichas->add(nuevaFicha);
}


Ficha * Jugador::obtenerFicha(Coordenada<int> & pos) {
    while(this->Fichas->avanzarCursor())   {
        if(Fichas->getCursor()->obtenerCoordenada()->iguales(pos)==true)
            return Fichas->getCursor();
    }

    return NULL;
}


int Jugador::cantidadFichas(void)   {
    return this->Fichas->contarElementos();
}
