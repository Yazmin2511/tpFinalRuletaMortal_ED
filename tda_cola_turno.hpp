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

//bicola vacia
bool cola_turnos_vacia(cola_turnos b){
    return b.frente == NULL;
}

//agregar cola
void cola_agregar_turno(cola_turnos &b,pturno nuevo){
    if(b.frente == NULL)
        b.frente = nuevo;
  //  else
        
}

pturno cola_quitar_turno(cola_turnos &b){
    pturno extraido;
    if(cola_turnos_vacia(b)){
       
    }else{
        
    }
    return extraido;
}

