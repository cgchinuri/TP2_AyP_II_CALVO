#ifndef COORDENADA__H
#define COORDENADA__H
#include <math.h>
#include<iostream>
#include <sstream>
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
    
   /* Coordenada(std::string csvString,char delim)    {
        std::string token=csvString.substr(0,csvString.find(delim))
    }
*/
    T obtenerX(void)    {
        return this->x;
    }

    T obtenerY(void)    {
        return this->y;
    }

    T obtenerZ(void)    {
        return this->z;
    }

    bool iguales(const Coordenada & c)const  {
        return ((this->x==c.x && this->y==c.y) && this->z==c.z) ? true : false;
    }

    //No es la distancia euclidea, sino la suma de la diferencia de cada coordenada
    T distancia(const Coordenada & p)   {
        return abs(this->x - p.x)+ abs(this->y - p.y)+abs(this->z - p.z);
    }   

    void sumar(const Coordenada & d)    {
        this->x+=d.x;
        this->y+=d.y;
        this->z+=d.z;
    }


    std::string toString(void)  {
        std::ostringstream oss;
        oss<<'('<<this->x<<','<<this->y<<','<<this->z<<')';
        std::string s= oss.str();
        return s;
    }

    void actualizar(T x, T y, T z)  {   
        this->x=x;
        this->y=y;
        this->z=z;
    }

};


#endif

