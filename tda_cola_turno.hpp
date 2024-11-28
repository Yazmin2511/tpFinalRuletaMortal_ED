#include "t_cad.hpp"
#include <stdlib.h>
#include <string.h>
#include "tda_pila_palabras acertadas.hpp"

typedef struct tturno *pturno;
typedef struct tturno{
    pturno sig;
    tcad nickname;
    int cantidad_vidas;
    pila_palabrasAcertadas palabras_acertadas;
};

typedef struct cola_turnos
{  
   pturno frente;
   pturno fin;
   int cantidad;
};
//inicialización de la bicola
void inicializar_turnos(cola_turnos &b){
   b.frente = NULL;
   b.cantidad = 0;
}

void crear_turno(pturno&p , tcad jugador)
{   p = new tturno;
    strcpy(p->nickname,jugador);
    p->sig = NULL;
    p->cantidad_vidas = 5;
    iniciar_pila_palabras(p->palabras_acertadas);
}

//cola vacia
bool cola_turnos_vacia(cola_turnos b){
    return b.cantidad == 0;
}

bool buscar_jugador_repetido(cola_turnos b, tcad jugador)
{pturno i;
    if(!cola_turnos_vacia(b))
    {
        for(i = b.frente; i!=NULL && strcmp(i->nickname, jugador)!=0 ; i= i->sig);
        if(i!=NULL)
            return true;
    }
    return false;
}

//agregar cola
void cola_agregar_turno(cola_turnos &b,pturno nuevo){
    if(cola_turnos_vacia(b))
    {
        b.frente = nuevo;
        b.fin = nuevo;
    }
    else
    {   
        pturno i;
        for(i=b.frente; i->sig!=NULL;i=i->sig);
        i->sig = nuevo;
        b.fin = nuevo;
    }  

    b.cantidad++;
}

pturno cola_quitar_turno(cola_turnos &b){
    pturno extraido=NULL,i;
    if(cola_turnos_vacia(b) == false){
       if(b.frente == b.fin)
       {
            extraido = b.frente;
            b.frente = NULL;
            b.fin = NULL;
       }
       else
       {
            extraido = b.frente;
            b.frente= extraido->sig;
            extraido->sig = NULL;
       }
    }
    return extraido;
}

