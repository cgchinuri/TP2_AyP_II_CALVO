struct Coordenada_t {
    int x;
    int y;
    int z;
};

class Soldado   {
private:
    Coordenada_t * posicion;
    bool vive;
    int jugadorId;

public:
    Soldado(int jugadorId,int x, int y, int z);
    const Coordenada_t & ObtenerPosicion(void);
    int JugadorAsociado(void);
    void Mover(int x, int y, int z);
    void DarBaja(void);
    bool EstaVivo(void);
};



/*Con respecto a la primitiva Mover.
De momento solo cambia la posicion del soldado. Nada sabe del tablero.
-   Necesito una primitiva (del tablero) que me diga si la posicion es valida. Sí lo es, entonces lo mueve
de lo contrario no.

Nada tiene que ver el soldado con el tablero, pero si quisiera que lo modifique =>

void Mover(int x, int y, int z, Tablero * pt)   {
    pt->ObtenerCasillero(x,y,z);
    
}
*/