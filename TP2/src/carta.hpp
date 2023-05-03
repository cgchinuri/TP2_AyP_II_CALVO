#ifndef CARTA_H
#define CARTA_H

#include <string>

#define LAMBDA 3 // Este es el parametro de la distribucion exponencial del generador de azar

typedef enum Nombre
{
    ROBO_VEHICULO, CONVERSION_SOLDADO, SUBMARINO, AVION, TRINCHERA, BARCO, ATAQUE_AEREO,
    INVESTIGACION_BOMBA_NUCLEAR, SOLDADO_EXTRA,
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