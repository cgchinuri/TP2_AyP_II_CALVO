/*
*   LinkedList_T.hpp:   Implementacion de luna clase de lista enlazada generica utilizando templates
*
*   Creacion : 3 Mayo 2023
*   Autor : Ponce Santiago
*
*/

#ifndef LISTA_ENLAZADA__H
#define LISTA_ENLAZADA__H

#include <iostream>
//Nodo generico
template <class T>
class Nodo  {
private:
    T dato;
    Nodo<T> * sig;
public:
    Nodo(T dato)    {//Mejor con referencia al dato?
        this->dato=dato;
        this->sig=NULL;
    }

    ~Nodo(){
        /*  Esta funcion se llama antes del final de la vida del nodo, aca deberia invocarse la funcion
        destructora del dato, si fuera un dato más complejo */
        std::cout<<"Se llamó al destructor de nodo"<<std::endl;
        std::cout<<this->ObtenerDato()<<std::endl;
    }

    T ObtenerDato(void) {
        return this->dato;
    }

    void CambiarSiguiente(Nodo<T> * nuevoSig)   {
        this->sig=nuevoSig;
    }


};

//Lista generica
template <class T>
class ListaEnlazada  {
private:
    Nodo<T> * primero;
    Nodo<T> * ultimo;
    unsigned int cantidad;
public:
    ListaEnlazada(void) {
        this->primero=NULL;
        this->ultimo=NULL;
        this->cantidad=0;
    }
    ~ListaEnlazada(){
        std::cout<<"Se llamó al destructor de la lista enlazada"<<std::endl;

            delete this->primero;

    }
    void InsertarPrimero(T dato)   {
        Nodo<T> * nuevoNodo=new Nodo<T>(dato);
        
        if(this->primero==NULL) {
            this->primero=nuevoNodo;
            return;
        }

        Nodo<T> * aux;
        aux=this->primero;
        this->primero=nuevoNodo;
        this->primero->CambiarSiguiente(aux);
        this->cantidad++;
        return;

    }
    //InsertarUltimo()
    T VerPrimero(void)  {
        if(this->primero==NULL) {
            std::cout<<"Lista vacia"<<std::endl;
            throw("Lista vacia");
        }
        
        return this->primero->ObtenerDato();
    }
    //VerUltimo()
    unsigned int Cantidad(void) {
        return this->cantidad;
    }

};
#endif

