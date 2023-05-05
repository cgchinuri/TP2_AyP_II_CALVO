#ifndef CARTA_H
#define CARTA_H

#include <string>

#define LAMBDA 3 // Este es el parametro de la distribucion exponencial del generador de azar

typedef enum Nombre
{
        SUBMARINO, AVION_RADAR, TRINCHERA, BARCO, ATAQUE_QUIMICO, REFUERZOS
} nombreCarta_t;

class Carta
{
    private:
    nombreCarta_t nombre;
    double generarNumeroAleatorioExponencial(double parametroLambda);

    public:
    //Constructor.
    //Pre: -
    //Pos: Crea una carta al azar
    Carta();
    //Destructor
    ~Carta() {};
    //Pre: -
    //Pos: Devuelve el nombre de la carta en formato nombreCarta_t (enum)
    nombreCarta_t getNombreCarta();
    //Pre: -
    //Pos: Devuelve el nombre de la carta en forma de string, DESCONOCIDO
    // si nombreCarta_t es invalido
    std::string cartaToString();
};

#endif // CARTA_H