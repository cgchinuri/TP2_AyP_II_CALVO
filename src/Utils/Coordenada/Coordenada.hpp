#ifndef COORDENADA__H
#define COORDENADA__H
#include <math.h>

template <typename T>
class Coordenada {
private:
    T x;
    T y;
    T z;
public:
    Coordenada(T x, T y, T z)   {
        this->x=x;
        this->y=y;
        this->z=z;
    }

    bool iguales(const Coordenada & c)  {
        return ((this->x==c.x && this->y==c.y) && this->z==c.z) ? true : false;
    }

    //No es la distancia euclidea, sino la suma de la diferencia de cada coordenada
    T distancia(const Coordenada & p)   {
        return abs(this->x - p.x)+ abs(this->y - p.y)+abs(this->z - p.z);
    }   

    void sumar(const Coordenada & d)    {
        this->x=d.x;
        this->z=d.y;
        this->z=d.z;
    }

    void imprimir(void) {
        std::cout<<'('<< this->x<<','<<this->y<<','<<this->z<<')'<<std::endl;
    }
};


#endif

