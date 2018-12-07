#include "Nodo.h"

Nodo::Nodo(const char& dato) : dato{dato} { }

Nodo::~Nodo()
{
    if(apuntador)
    {
        delete apuntador;
    }
}
