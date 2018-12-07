#pragma once

struct Nodo
{
    Nodo(const char& dato);
    ~Nodo();
    char dato{'0'};
    Nodo* apuntador{nullptr};
};
