#ifndef CARTA_H
#define CARTA_H

#include <string>

#define LAMBDA 3 // Este es el parametro de la distribucion exponencial del generador de azar

typedef enum tipo
{
    SUBMARINO, AVION_RADAR, TRINCHERA, BARCO, ATAQUE_QUIMICO, REFUERZOS
} tipoCarta_t;

class Carta
{
    private:
    tipoCarta_t tipo;
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
    tipoCarta_t getTipoCarta();
    //Pre: -
    //Pos: Devuelve el nombre de la carta en forma de string, DESCONOCIDO
    // si es una carta inválida
    std::string cartaToString();
};

#endif // CARTA_H