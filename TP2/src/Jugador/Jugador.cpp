#include "Jugador.hpp"
 #include <stdexcept>

Coordenada::Coordenada(int x, int y, int z) {
    this->x=x;
    this->y=y;
    this->z=z;
}

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

    for(ficha=this->Fichas->getCursor(); ficha!=NULL; ficha=this->Fichas->getCursor())  {
        if(ficha->obtenerPosicion()==origen){ //Mejor implementar un metodo 'equals() en el tipo de dato coordenada que diga si son iguales
            ficha->establecerPosicion(destinoX,destinoY,destinoZ);
            Fichas->reiniciarCursor();
            return true;
        }
        else    {
            this->Fichas->avanzarCursor();
        }
    }
    
    Fichas->reiniciarCursor();
    return false;

}

void Jugador::agregarFicha(Ficha * nuevaFicha)  {
    this->Fichas->add(nuevaFicha);
}


Ficha * Jugador::obtenerFicha(Coordenada & pos) {
    
}