#ifndef CARTA_H
#define CARTA_H

#include <string>

typedef enum tipo
{
    SUBMARINO, AVION_RADAR, TRINCHERA, BARCO, ATAQUE_QUIMICO, REFUERZOS
} carta_t;

class CartaBatallaDigital
{
    private:
    carta_t tipo;

    public:
    //Constructor.
    //Pre: -
    //Pos: Crea una carta al azar
    CartaBatallaDigital(carta_t tipo);
    //Destructor
    ~CartaBatallaDigital() {};
    //Pre: -
    //Pos: Devuelve el nombre de la carta en formato nombreCarta_t (enum)
    carta_t getTipo();
    //Pre: -
    //Pos: Devuelve el nombre de la carta en forma de string
    std::string getNombre();
    //Pre: -
    //Pos: Devuelve la descripcion de la carta en forma de string
    std::string getDescripcion();
};

//Pre: -
//Pos: Inicializa la memoria dinamica de cada carta, devolviendo un arreglo dinamico de punteros
// a CartaBatallaDigital con un extra puntero a NULL para indicar el fin del arreglo.
CartaBatallaDigital ** iniciarCartas();

#endif // CARTA_H