#include<iostream>
#include "t_cad.hpp"

const int MAXIMO = 10;
typedef tcad tcontenedorPalabras[MAXIMO] ;
struct pila_palabrasAcertadas{
    tcontenedorPalabras palabras_acertadas;
    int cima;
};

//iniciar pila
void iniciar_pila_palabras(pila_palabrasAcertadas &p)
{
    p.cima = -1;
}

//pila vacia
bool pila_vacia_palabras(pila_palabrasAcertadas p)
{
    return p.cima == -1;
}
//tope de nuestra pila
int tope_pila_palabras(pila_palabrasAcertadas p)   // Devuelve la cantidad de letras de la palabra de la cima
{
    if(!pila_vacia_palabras(p))
        return strlen(p.palabras_acertadas[p.cima]);
    return 0;
}

//pila llena
bool pila_llena_palabras(pila_palabrasAcertadas p)
{
    return p.cima == MAXIMO-1;
}
//agregar palabras
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
//quitar pila
void quitar_pila_palabras(pila_palabrasAcertadas &p)
{ 
    if(!pila_vacia_palabras(p))
    {
        p.cima --;
    }
}

