#ifndef CARTA_H
#define CARTA_H

#include <string>
#include <map>

typedef enum tipo
{
    SUBMARINO, AVION_RADAR, TRINCHERA, BARCO, ATAQUE_QUIMICO, REFUERZOS,
} tipoCarta_t;

std::map<tipoCarta_t, std::string> cadenasCartas =
{
{SUBMARINO, "Submarino"},
{AVION_RADAR, "Avion Radar"},
{TRINCHERA, "Trinchera"},
{BARCO, "Barco"},
{ATAQUE_QUIMICO, "Ataque Quimico"},
{REFUERZOS, "Refuerzos"}
};

class Carta
{
    private:
    tipoCarta_t tipo;

    public:
    //Constructor.
    //Pre: -
    //Pos: Crea una carta al azar
    Carta(tipoCarta_t tipo);
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