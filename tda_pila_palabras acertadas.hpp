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

int calcular_puntaje(pila_palabrasAcertadas p , bool todasPalabrasJugadas)
{   int cantidad_palabras_adivinadas=p.cima+1;     // Ver se es valido
    int puntajeTotal, cantidad_char_palabra_Mas_Larga = 0;
    
    while(!pila_vacia_palabras(p))
    {
        if(tope_pila_palabras(p) > cantidad_char_palabra_Mas_Larga )
            cantidad_char_palabra_Mas_Larga = tope_pila_palabras(p);
        quitar_pila_palabras(p);
    }
    puntajeTotal= cantidad_palabras_adivinadas * cantidad_char_palabra_Mas_Larga;
    
    if(todasPalabrasJugadas)
        puntajeTotal= puntajeTotal*3;

    return puntajeTotal;

}