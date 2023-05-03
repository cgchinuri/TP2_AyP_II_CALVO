#include <iostream>
#include "LinkedList_T.hpp"



/*  int main(void)  {
    std::cout<<"Pruebas Lista enlazada"<<std::endl;
    std::string miNombre("Santiago");
{
    Nodo<std::string> c1(miNombre);
    std::cout<<c1.ObtenerDato()<<std::endl;
}

    std::cout<<miNombre<<std::endl; //Se copia el objeto en el constructor del nodo
    Nodo<std::string> * ptrToSerie=new Nodo<std::string>("Bojack Horseman");
    std::cout<<ptrToSerie->ObtenerDato()<<std::endl;
    delete ptrToSerie;

    return 0;
}
*/

int main(void)  {

    std::cout<<"Pruebas Lista enlazada"<<std::endl;

    ListaEnlazada<std::string> Series;
    Series.InsertarPrimero("Bojack Horseman");

    std::cout<<Series.VerPrimero()<<std::endl;

    Series.InsertarPrimero("Boardwalk Empire");
    std::cout<<Series.VerPrimero()<<std::endl;


    

    return 0;
}