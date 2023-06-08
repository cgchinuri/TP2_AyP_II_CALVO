#include "Jugador.h"
#include <stdexcept>
 
Jugador::Jugador(int id,const std::string s)   
{
    this->idJugador=id;
    this->nombre=new std::string(s);
    this->Fichas= new Lista <Ficha *>();
    this->Cartas=new Mazo<CartaBatallaDigital*>();
}  


std::string & Jugador::Nombre(void)  {
    return *(this->nombre);
}

int Jugador::identificador(void)    {
    return this->idJugador;
}

void Jugador::agregarFicha(Ficha * nuevaFicha)  
{
    this->Fichas->add(nuevaFicha);
}


Ficha * Jugador::obtenerFicha(Coordenada<int> & pos) {
    
    this->Fichas->reiniciarCursor();
    while(this->Fichas->avanzarCursor())   {
        if(Fichas->getCursor()->obtenerCoordenada()->iguales(pos)==true)    {
            return Fichas->getCursor();
        }
    }

    return NULL;
}

Ficha * Jugador::obtenerFicha(unsigned int indice) {
    if(indice>this->Fichas->contarElementos()){
        throw std::invalid_argument("Opcion invalida");
    }

    return this->Fichas->get(indice);
}

int Jugador::cantidadFichas(void)   {
    return this->Fichas->contarElementos();
}
void Jugador::mostrarFichas()   {
    std::cout<<"Fichas Disponibles:"<<std::endl;

    for(size_t i=1; Fichas->avanzarCursor();i++)    {
        std::cout<<'['<<i<<']'<<Fichas->getCursor()->toStringTipo()<<Fichas->getCursor()->obtenerCoordenada()->toString()<<std::endl;
    }
}
void Jugador::eliminarFicha(unsigned int pos)   {
    this->Fichas->remover(pos);
}

bool Jugador::eliminarFicha(Coordenada<int> & pos)   {

    for(size_t i=1; Fichas->avanzarCursor();i++){
        if(Fichas->getCursor()->obtenerCoordenada()->iguales(pos)==true){
            Fichas->remover(i);
            Fichas->reiniciarCursor();
            return true;
        }
    }
    return false;

}


void Jugador::agregarCarta(CartaBatallaDigital *carta)  {
    this->Cartas->agregarCarta(carta);
}
CartaBatallaDigital * Jugador::obtenerCarta(int pos) {
    return this->Cartas->getCarta(pos);
}

void Jugador::mostrarCartas()   {
    std::cout<<"Cartas Disponibles:"<<std::endl;//DEBUG

    for(size_t i=1; Cartas->avanzarCursor();i++)    {
        std::cout<<'['<<i<<']'<<Cartas->getCursor()->getNombre()<<std::endl;
    }
}

int Jugador::cantidadFichasSoldado()
{
    this->Fichas->reiniciarCursor();
    int cantidadSoldados=0;
    while(Fichas->avanzarCursor())
    {
        Ficha* fichaCursor=Fichas->getCursor();
            if (fichaCursor->obtenerTipo()==FICHA_SOLDADO)
            {
                cantidadSoldados++;
            }
    }
    return cantidadSoldados;
}



void Jugador::removerFichasInactivas(void)    {
    
    this->Fichas->reiniciarCursor();

    for(size_t i=1;this->Fichas->avanzarCursor();i++) {
        if(!(this->Fichas->getCursor()->estaActiva())){
            this->Fichas->remover(i);

            this->Fichas->reiniciarCursor();//Si no se reinicia el cursor y el indice se podria incurrir en un funcionamiento erratico al remover otra ficha
            i=0;
        }
    }
}

//Esta funcion recorre la lista de fichas del jugador, para cada ficha obtiene el casillero asociado, lo inactiva (si la ficha a retirar es una mina) y vacia el casillero

void Jugador::retirarFichas(void)   {
    this->Fichas->reiniciarCursor();

    while(this->Fichas->avanzarCursor()){
        Ficha * fichaRetirada=this->Fichas->getCursor();
        fichaRetirada->getCasilleroFicha()->vaciarCasillero();
        fichaRetirada->desactivarFicha();
        if(fichaRetirada->obtenerTipo()==FICHA_MINA)    {
            fichaRetirada->getCasilleroFicha()->desactivar();
        }
    }
    //En este punto ya todas las fichas restantes estan desvinculadas en el tablero
    //Deberia entonces destruirse la lista de fichas.
    this->removerFichasInactivas();

}

