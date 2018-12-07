#pragma once

struct Nodo
{
    Nodo(const char& dato);
    char dato{'0'};
    Nodo* apuntador{nullptr};
};
