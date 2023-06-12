#ifndef CARTA_H
#define CARTA_H

#include "mazo.h"
#include <string>

typedef enum tipo
{
    CARTA_SUBMARINO, CARTA_AVION_RADAR, CARTA_TRINCHERA, CARTA_BARCO, CARTA_ATAQUE_QUIMICO, CARTA_REFUERZOS
} carta_t;

class CartaBatallaDigital
{
    private:
    carta_t tipo;
    std::string nombre;
    std::string descripcion;
    unsigned int cantidadRepeticiones;

    public:
    //Constructor.
    //Pos: Crea una carta al azar
    CartaBatallaDigital(carta_t tipo);

    //Destructor
    ~CartaBatallaDigital() {};

    //Pos: Devuelve el nombre de la carta en formato nombreCarta_t (enum)
    carta_t getTipo();

    //Pos: Devuelve el nombre de la carta en forma de string
    std::string getNombre();

    //Pos: Devuelve la descripcion de la carta en forma de string
    std::string getDescripcion();

    //Pos: Devuelve la cantidad de repeticiones que habra de la carta en el mazo
    unsigned int getCantidadRepeticiones();
};


#endif // CARTA_H