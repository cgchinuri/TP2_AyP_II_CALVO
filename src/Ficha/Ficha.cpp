#include "Ficha.h"




Ficha::Ficha(t_ficha tipo,int x, int y, int z)  {
    if(tipo!=FICHA_BARCO && tipo!=FICHA_SOLDADO && tipo!=FICHA_AVION && tipo!=FICHA_MINA){ 
        throw "Tipo de ficha invalido";
    } 

    this->tipo=tipo;
    this->coordenada=new Coordenada<int>(x,y,z);
    this->activo=true;
    this->casillero = NULL;
}

t_ficha Ficha::obtenerTipo(void)const  {
        return this->tipo;
    }

Coordenada<int> * Ficha::obtenerCoordenada(void)  {
    return this->coordenada;
}

std::string Ficha::toStringTipo(void) {
    std::string s;
    switch(this->tipo)  {
        case FICHA_BARCO:
            s="Barco";
            break;
        case FICHA_SOLDADO:
            s="Soldado";
            break;
        case FICHA_AVION:
            s="Avion";
            break;
        case FICHA_MINA:
            s="Mina";
            break;
    }
    return s;
}

Casillero * Ficha::getCasilleroFicha(){
	return this->casillero;
}

void Ficha::setCasilleroFicha(Casillero * casillero) {
	this->casillero = casillero;
}

void Ficha::desvincularFichaDeCasillero() {
	this->casillero = NULL;
}

void Ficha::desactivarFicha(void)  {
    this->activo=false;
}

void Ficha::activarFicha(void)  {
    this->activo=true;
}

//Sin esta funcion el jugador no puede saber que fichas eliminar de su lista de fichas
bool Ficha::estaActiva(void)    {
    return this->activo;
}


t_ficha Ficha::getTipoFicha()
{
	return this->tipo;
}
