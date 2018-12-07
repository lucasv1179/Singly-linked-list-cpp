#include "Lista.h"
#include <iostream>
using std::cout;
using std::endl;

Lista::Lista() { }

Lista::Lista(const Lista& lista)
{
    Nodo* original{lista.cabeza};

    if(original)
    {
        cabeza = new Nodo(original->dato);
        Nodo* copia{cabeza};

        while(original->apuntador)
        {
            copia->apuntador = new Nodo(original->apuntador->dato);
            original = original->apuntador;
            copia = copia->apuntador;
        }

        cola = copia;
    }
}

Lista::~Lista()
{
    if(cabeza)
    {
        Nodo* aux = buscarNodoAntecesor(cola);

        while(aux)
        {
            delete aux->apuntador;
            (*aux).apuntador = nullptr;
            cola = aux;
            aux = buscarNodoAntecesor(cola);
        }
        delete cabeza;
        cabeza = cola = nullptr;
    }
}

void Lista::insertar(const char& dato, Nodo* nodo, Posicion posicion)
{
    if(nodo)
    {
        if(posicion == ANTES)
        {
            Nodo* aux = nodo;
            nodo = new Nodo(dato);
            nodo->apuntador = aux;
            if(aux == cabeza)
            {
                cabeza = nodo;
            }
            else
            {
                Nodo* antecesor = buscarNodoAntecesor(aux);
                if(antecesor)
                {
                    antecesor->apuntador = nodo;
                }
                else
                {
                    cout << "No hay antecesor o cabeza no existe";
                }
            }
        }
        else if(posicion == DESPUES)
        {
            Nodo* aux = nodo->apuntador;
            nodo->apuntador = new Nodo(dato);
            nodo->apuntador->apuntador = aux;
            if(nodo == cola)
            {
                cola = nodo->apuntador;
            }
        }
    }
    else
    {
        if(!cabeza)
        {
            cabeza = new Nodo(dato);
            cola = cabeza;
        }
        else
        {
            cout << "Nodo invalido" << endl;
        }
    }
    
}

char Lista::sacar(Nodo* nodo)
{
    if(nodo)
    {
        char dato = nodo->dato;
        Nodo* sucesor = nodo->apuntador;
        Nodo* antecesor = buscarNodoAntecesor(nodo);
        if(nodo == cabeza)
        {
            if(cabeza == cola)
            {
                cola = nullptr;
            }
            cabeza = nodo->apuntador;
            nodo->apuntador = nullptr;
        }
        else if (nodo == cola)
        {
            antecesor->apuntador = nullptr;
            cola = antecesor;
        }
        else
        {
            antecesor->apuntador = sucesor;
            nodo->apuntador = nullptr;
        }

        delete nodo;
        return dato;
    }
    else
    {
        cout << "Nodo invalido" << endl;
    }
}

void Lista::insertarAntes(const char& dato, const char& datoNuevo)
{
    insertar(datoNuevo, buscarDato(dato), ANTES);
}

void Lista::insertarAntes(const int& posicion, const char& datoNuevo)
{
    insertar(datoNuevo, buscarNodo(posicion), ANTES);
}

void Lista::insertarDespues(const char& dato, const char& datoNuevo)
{
    insertar(datoNuevo, buscarDato(dato), DESPUES);
}

void Lista::insertarDespues(const int& posicion, const char& datoNuevo)
{
    insertar(datoNuevo, buscarNodo(posicion), DESPUES);
}

char Lista::sacarElemento(const int& posicion)
{
    Nodo* aux = buscarNodo(posicion);
    sacar(aux);
}

char Lista::sacarElemento(const char& dato)
{
    Nodo* aux = buscarDato(dato);
    sacar(aux);
}

void Lista::insertarInicio(const char& dato)
{
    insertar(dato, cabeza, ANTES);
}

char Lista::sacarInicio()
{
    return sacar(cabeza);
}

void Lista::insertarFin(const char& dato)
{
    insertar(dato, cola, DESPUES);
}

char Lista::sacarFin()
{
    return sacar(cola);
}

void Lista::mesclar(Lista& lista)
{
    int posicion{2};

    while(buscarNodo(posicion) && lista.cabeza)
    {
        insertarAntes(posicion, lista.cabeza->dato);
        lista.sacarInicio();
        posicion += 2;
    }

    while(lista.cabeza)
    {
        insertarFin(lista.cabeza->dato);
        lista.sacarInicio();
    }
}

void Lista::invertirOrden()
{
    Nodo* aux = cola;
    while(aux && buscarNodoAntecesor(aux))
    {
        aux->apuntador = buscarNodoAntecesor(aux);
        aux = aux->apuntador;
    }
    cabeza = cola;
    cola = aux;
    cola->apuntador = nullptr;
}

void Lista::dividir(Lista& impares, Lista& pares)
{
    int posicion{0};
    while(cabeza)
    {
        impares.insertarDespues(posicion, sacarInicio());

        if(cabeza)
        {
            pares.insertarDespues(posicion, sacarInicio());
        }
        
        ++posicion;
    }
}

bool Lista::existe(const char& dato) const
{
    Nodo* aux{cabeza};
    bool existe{false};

    while(aux && !existe)
    {
        if(aux->dato == dato)
        {
            existe = true;
        }
        aux = aux->apuntador;
    }

    return existe;
}

int Lista::encontrarPosicion(const char& dato) const
{
    Nodo* aux{cabeza};
    int posicion{1};
    int indice{0};

    while(aux && !indice)
    {
        if(aux->dato == dato)
        {
            indice = posicion;
        }
        ++posicion;
        aux = aux->apuntador;
    }

    return indice;
}

int Lista::contarOcurrencias(const char& dato) const
{
    Nodo* aux{cabeza};
    int ocurrencias{0};

    while(aux)
    {
        if(aux->dato == dato)
        {
            ++ocurrencias;
        }
        
        aux = aux->apuntador;
    }

    return ocurrencias;
}

void Lista::imprimir()
{
    if(cabeza)
    {
        Nodo* aux = cabeza;
        while(aux)
        {
            cout << aux->dato << " ";
            aux = aux->apuntador;
        }
        cout << endl;
    }
    else
    {
        cout << "Lista vacia" << endl;
    }
}

Nodo* Lista::buscarDato(const char& dato) const
{
    Nodo* aux{cabeza};
    Nodo* nodo{nullptr};

    while(aux && !nodo)
    {
        if(aux->dato == dato)
        {
            nodo = aux;
        }
        aux = aux->apuntador;
    }

    return nodo;
}

Nodo* Lista::buscarNodo(const int& posicion) const
{
    Nodo* aux{cabeza};
    Nodo* nodo{nullptr};
    int contador{1};

    while(aux && !nodo)
    {
        if(contador == posicion)
        {
            nodo = aux;
        }
        aux = aux->apuntador;
        ++contador;
    }

    return nodo;
}

Nodo* Lista::buscarNodoAntecesor(Nodo* nodo) const
{
    Nodo* aux{cabeza};
    Nodo* target{nullptr};
    while(aux && aux != nodo)
    {
        target = aux;
        aux = aux->apuntador;
    }
    return target;
}
