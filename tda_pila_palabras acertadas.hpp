#include<iostream>
#include "t_cad.hpp"

const int MAXIMO = 10;
typedef tcad tcontenedorPalabras[MAXIMO] ;
struct pila_palabrasAcertadas{
    tcontenedorPalabras palabras_acertadas;
    int cima;
};


void iniciar_pila_palabras(pila_palabrasAcertadas &p)
{
    p.cima = -1;
}


bool pila_vacia_palabras(pila_palabrasAcertadas p)
{
    return p.cima == -1;
}

int tope_pila_palabras(pila_palabrasAcertadas p)   // Devuelve la cantidad de letras de la palabra de la cima
{
    if(!pila_vacia_palabras(p))
        return strlen(p.palabras_acertadas[p.cima]);
    return 0;
}


bool pila_llena_palabras(pila_palabrasAcertadas p)
{
    return p.cima == MAXIMO-1;
}

void push_pila_palabras(pila_palabrasAcertadas &p , tcad nuevo)
{
    if(!pila_llena_palabras(p))
    {
        p.cima++;
        strcpy(p.palabras_acertadas[p.cima], nuevo);
    }
    else
        std::cout<<"Pila llena"<<std::endl;
}

void quitar_pila_palabras(pila_palabrasAcertadas &p)
{ 
    if(!pila_vacia_palabras(p))
    {
        p.cima --;
    }
}

