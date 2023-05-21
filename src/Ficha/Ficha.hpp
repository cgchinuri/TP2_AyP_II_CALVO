#ifndef FICHA__H
#define FICHA__H

#include "../Utils/Coordenada/Coordenada.hpp"
#include "../Casillero/casillero.h"
#include "../Jugador/Jugador.hpp"



enum t_ficha    {
    FICHA_BARCO,
    FICHA_SOLDADO,
    FICHA_AVION,
    FICHA_MINA
};

class Ficha {
private:
    t_ficha tipo;
    Jugador * pj;//Puntero al jugador al cual pertenece la ficha
    Casillero * pc;//puntero al casillero que ocupa
public: 
    Ficha(t_ficha tipo,Jugador * jugador,Casillero * pc);
    t_ficha getTipo(void)const;
    Casillero * getCasillero(void);
    Jugador * getJugador(void);

    void setJugador(Jugador * pj);
    void setCasillero(Casillero * pc);
    void setTipo(t_ficha tipo);
};
/* Con respecto a esta implementacion:
    En la version anterior, donde la ficha poseia una coordenada, la creacion
    se hacia pasandole x,y,z para que la ficha cree SU coordenada, sin la ficha
    no existia la coordenada, luego se podia usar esa coordenada para interactuar
    con las primitivas del tablero. La ficha podia existir tranquilamente, sin 
    un casillero ya que tenia su atributo de posicion

    Con esta implementacion para que la ficha tenga una posicion DEBE tener un 
    casillero
*/


#endif