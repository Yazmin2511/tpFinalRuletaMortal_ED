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
//crear turno
void crear_turno(pturno&p , tcad jugador)
{   p = new tturno;
    strcpy(p->nickname,jugador);
    p->sig = NULL;
    p->cantidad_vidas = 5;
    iniciar_pila_palabras(p->palabras_acertadas);
}

//cola vacia
bool cola_turnos_vacia(cola_turnos b){
    return b.frente==NULL;
}
//busca jugador repetido
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
//quita turno de la cola
pturno cola_quitar_turno(cola_turnos &b){
    pturno extraido=NULL;
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
//calculo del puntaje del jugador
int calcular_puntaje_individual(pila_palabrasAcertadas p , bool todasPalabrasJugadas)
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

//jugador con mas palabras o puntajes
pturno jugador_con_mas_palabras_o_puntaje(cola_turnos jugadores)   // Verificar
{   
    pturno i=cola_quitar_turno(jugadores),aux;
    int puntajeTotalUno,puntajeTotalDos;
    
    while (cola_turnos_vacia(jugadores) == false)
    {  aux=cola_quitar_turno(jugadores);
        if(i->palabras_acertadas.cima < aux->palabras_acertadas.cima )
            i=aux;
        if((i->palabras_acertadas.cima == aux->palabras_acertadas.cima))
        {
                // Si hay empate de palabras
               
                puntajeTotalUno=calcular_puntaje_individual(i->palabras_acertadas,true);
                puntajeTotalDos=calcular_puntaje_individual(aux->palabras_acertadas,true);
                
                if(puntajeTotalUno < puntajeTotalDos)
                    i=aux;
               
        }  
    }
   
    return i;
    
}

