#include "Jugador.h"
 
Jugador::Jugador(int id,const std::string s)   
{
    this->idJugador=id;
    this->nombre=new std::string(s);
    this->Fichas= new Lista <Ficha *>();
    this->Cartas=new Mazo<CartaBatallaDigital*>();
    this->enemigosDetectados=new Lista<Casillero*>();
}
Jugador::~Jugador()   
{
    delete this->nombre;
    delete this->Fichas;
    delete this->Cartas;
    delete this->enemigosDetectados;
}    


std::string & Jugador::getNombre(void)  {
    return *(this->nombre);
}

int Jugador::getIdentificador(void)    {
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
       throw "opcion invalida";
    }

    return this->Fichas->get(indice);
}

int Jugador::cantidadFichas(void)   {
    return this->Fichas->contarElementos();
}
unsigned int Jugador::mostrarFichas()   {

	std::cout<<"Fichas Disponibles:"<<std::endl;

	size_t indiceFicha = 0 ;

	Fichas->reiniciarCursor();

	while(Fichas->avanzarCursor())
	{
		indiceFicha++;

		std::cout<<'['<<indiceFicha<<']'<<" - ";
		std::cout << Fichas->getCursor()->toStringTipo();
		std::cout << " en "<< Fichas->getCursor()->getCasilleroFicha()->getCoordenada()->toString();
		std::cout << std::endl;
	}

	return indiceFicha;
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

CartaBatallaDigital * Jugador::obtenerCarta(carta_t tipo) {
    Cartas->reiniciarCursor();
    int pos=1;
    while(Cartas->avanzarCursor()){
        if(Cartas->getCursor()->getTipo()==tipo){
           return  Cartas->getCarta(pos);
        }
        pos++;
    }
    return NULL;
}

bool Jugador::fichaEnemigaDetectada(Coordenada<int> & pos){
    this->enemigosDetectados->reiniciarCursor();
    while(this->enemigosDetectados->avanzarCursor()){
       Coordenada<int> *coordenada=this->enemigosDetectados->getCursor()->getCoordenada();

       if(coordenada->iguales(pos)){
        return true;
       }
    }

    return false;
}

void Jugador::mostrarCartas()   {

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
            if (fichaCursor->obtenerTipo()==FICHA_SOLDADO && fichaCursor->estaActiva())
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

void Jugador::setEnemigosDetectados(Lista<Casillero *> * enemigos) {
   
   enemigos->reiniciarCursor();
   while(enemigos->avanzarCursor()){
    this->enemigosDetectados->add(enemigos->getCursor());
   }
}

Lista<Casillero *> * Jugador::getEnemigosDetectados(void){
    return this->enemigosDetectados;
}


bool Jugador::hayTipoEnCoordenada(t_ficha tipo, unsigned int x, unsigned int y, unsigned int z) {
    this->Fichas->reiniciarCursor();
    while(Fichas->avanzarCursor())
    {
        Ficha* fichaCursor=Fichas->getCursor();
            if (fichaCursor->obtenerTipo()==tipo && fichaCursor->obtenerCoordenada()->iguales(Coordenada<int>(x,y,z)))
            {
                return true;
            }
    }
    return false;
}