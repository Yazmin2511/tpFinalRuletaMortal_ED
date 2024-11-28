#include "t_cad.hpp"
#include <stdlib.h>
#include <string.h>

typedef struct tturno *pturno;
typedef struct tturno{
    pturno sig;
    tcad nickname;
};

typedef struct cola_turnos
{  
   pturno frente;
   pturno fin;
};
//inicialización de la bicola
void inicializar_turnos(cola_turnos &b){
   b.frente = NULL;
}

void crear_turno(pturno&p , tcad jugador)
{   p = new tturno;
    strcpy(p->nickname,jugador);
    p->sig = NULL;
}

//cola vacia
bool cola_turnos_vacia(cola_turnos b){
    return b.frente == NULL;
}

bool buscar_jugador_repetido(cola_turnos b, tcad jugador)
{pturno i;
    if(b.frente != NULL)
    {
        for(i = b.frente; i!=NULL && strcmp( i->nickname,jugador)!=0;i= i->sig);
        if(strcmp( i->nickname,jugador)==0)
            return true;
    }
    return false;
}

//agregar cola
void cola_agregar_turno(cola_turnos &b,pturno nuevo){
    if(b.frente == NULL)
    {
        b.frente = nuevo;
        b.fin = nuevo;
    }
    else
    {   
        pturno i;
        for(i=b.frente; i->sig!=NULL;i=i->sig);
        i->sig = nuevo;
        b.frente = nuevo;
    }  
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
            for(i=b.frente;(i->sig)->sig!=NULL;i=i->sig);
            extraido = i->sig;
            b.fin = i;
            i->sig = NULL;
       }
    }
    return extraido;
}

