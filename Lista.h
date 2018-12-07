#pragma once
#include "Nodo.h"

class Lista
{
    public:
        Lista();
        Lista(const Lista& lista);
        ~Lista();
        void insertarInicio(const char& dato);
        void insertarFin(const char& dato);
        void insertarAntes(const char& dato, const char& datoNuevo);
        void insertarAntes(const int& posicion, const char& datoNuevo);
        void insertarDespues(const char& dato, const char& datoNuevo);
        void insertarDespues(const int& posicion, const char& datoNuevo);
        char sacarElemento(const int& posicion);
        char sacarElemento(const char& dato);
        char sacarInicio();
        char sacarFin();
        void mesclar(Lista& lista);
        void invertirOrden();
        void dividir(Lista& impares, Lista& pares);
        bool existe(const char& dato) const;
        int encontrarPosicion(const char& dato) const;
        int contarOcurrencias(const char& dato) const;
        void imprimir();
    private:
        enum Posicion{ANTES, DESPUES};
        void insertar(const char& dato, Nodo* nodo, Posicion posicion);
        char sacar(Nodo* nodo);
        Nodo* buscarDato(const char& dato) const;
        Nodo* buscarNodo(const int& posicion) const;
        Nodo* buscarNodoAntecesor(Nodo* nodo) const;
        Nodo* cabeza{nullptr};
        Nodo* cola{nullptr};
};