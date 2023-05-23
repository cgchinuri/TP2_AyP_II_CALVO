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
    Coordenada destino(destinoX,destinoY,destinoZ);

    Ficha * ficha;

    if(this->Fichas->vacia())   {
        throw std::invalid_argument("Fichas no disponibles");
    }

    while(this->Fichas->avanzarCursor())   {
        if(Fichas->getCursor()->obtenerCoordenada()->iguales(origen)==true) {
            Fichas->getCursor()->obtenerCoordenada()->sumar(destino);
            Fichas->reiniciarCursor();
            return true;
        }
    }

    Fichas->reiniciarCursor();
    return false;

}

bool Jugador::moverFicha(int indiceFicha,int destinoX,int destinoY,int destinoZ)    {
    Coordenada destino(destinoX,destinoY,destinoZ);
    this->Fichas->get(indiceFicha)->obtenerCoordenada()->sumar(destino);
    return true;

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

Ficha * Jugador::obtenerFicha(int pos) {
    return this->Fichas->get(pos);
}
int Jugador::cantidadFichas(void)   {
    return this->Fichas->contarElementos();
}

void Jugador::mostrarFichas()   {
    std::cout<<"Fichas Disponibles:"<<std::endl;//DEBUG

    for(size_t i=1; Fichas->avanzarCursor();i++)    {
        std::cout<<'['<<i<<']'<<Fichas->getCursor()->obtenerCoordenada()->toString()<<std::endl;
    }
}

void Jugador::eliminarFicha(unsigned int pos)   {
    this->Fichas->remover(pos);

}

