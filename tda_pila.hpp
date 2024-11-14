#include<iostream>

const int MAX = 10;
typedef int tcontenedor[MAX] ;
struct pila{
    tcontenedor datos;
    int cima;
};


void iniciar_pila(pila &p)
{
    p.cima = -1;
}

int tope_pila(pila p)
{
    if(!pila_vacia(p))
        return p.datos[p.cima];
    return -9999;
}

bool pila_vacia(pila p)
{
    return p.cima == -1;
}

bool pila_llena(pila p)
{
    p.cima == MAX-1;
}

void push_pila(pila &p , int nuevo)
{
    if(!pila_llena(p))
    {
        p.cima++;
        p.datos[p.cima] = nuevo;
    }
    else
        std::cout<<"Pila llena"<<std::endl;
}

int quitar_pila(pila &p)
{ int aux;
    if(!pila_vacia(p))
    {
        aux =  p.datos[p.cima];
        p.cima --;
    }
    else
        aux = -999;

    return aux;
}