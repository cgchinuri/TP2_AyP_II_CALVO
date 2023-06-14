#include "cartaBatallaDigital.h"
#include <string>

// PRE: Recibe un tipo de carta de Batalla Digital válido
// POS: Crea una carta con tipo, nombre, y descripción
CartaBatallaDigital::CartaBatallaDigital(carta_t tipo)
{
    this->tipo = tipo;

    switch (tipo) {
    case CARTA_SUBMARINO:
        this->nombre = "Submarino";
        this->descripcion = "Agrega una unidad a la armada del jugador capaz de lanzar misiles. Solo puede ser destruidos por barcos y "
        "otros submarinos [AGUA PROFUNDIDAD MINIMA]";
        this->cantidadRepeticiones = 15;
        break;
    case CARTA_AVION_RADAR:
        this->nombre = "Avion Radar";
        this->descripcion = "Avion Radar le agrega una unidad a la fuerza aérea del jugador, capaz de detectar unidades enemigas en la superficie. "
        "No tiene capacidades ofensivas o defensivas. [AIRE ALTURA MINIMA]";
        this->cantidadRepeticiones = 15;
        break;
    case CARTA_TRINCHERA:
        this->nombre = "Trinchera";
        this->descripcion = "Trinchera le permite convertir un soldado en una trinchera por -- turnos, la cual eliminara soldados enemigos. "
        "El soldado queda imovil pero es inmune a soldados enemigos[TIERRA PROFUNDIDAD]";
        this->cantidadRepeticiones = 15;
        break;
    case CARTA_BARCO:
        this->nombre = "Barco";
        this->descripcion = "Arega una unidad a la armada del jugador capaz de lanzar misiles y "
        "torpedos anti-submarinos [SUPERFICIE DE AGUA]";
        this->cantidadRepeticiones = 20;
        break;
    case CARTA_ATAQUE_QUIMICO:
        this->nombre = "Ataque Quimico";
        this->descripcion = "Ataque quimico! Elimina soldados enemigos en un radio de -- casillas."
        "Deja las casillas inactivas por -- turnos";
        this->cantidadRepeticiones = 10;
        break;
    case CARTA_REFUERZOS:
        this->nombre = "Refuerzos";
        this->descripcion = "Agrega un soldado al ejercito del jugador [SUPERFICIE DE TIERRA]";
        this->cantidadRepeticiones = 25;
        break;
    
    default:
        throw "Tipo Invalido";
    }
}

carta_t CartaBatallaDigital::getTipo()
{
    return this->tipo;
}

std::string CartaBatallaDigital::getNombre()
{
    return this->nombre;
}

std::string CartaBatallaDigital::getDescripcion()
{
    return this->descripcion;
}

unsigned int CartaBatallaDigital::getCantidadRepeticiones()
{
    return this->cantidadRepeticiones;
}