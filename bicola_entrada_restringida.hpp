//Prioriza espacio
typedef int contenedor[MAX];
typedef struct tbicola_e
{
    contenedor dato;
    int frente;
    int fin;
    int contador;
};
//inicialización de la bicola
void incializacion_e(tbicola_e &b){
    b.frente=MAX-1;
    b.fin=MAX-1;
    b.contador=0;
}
// bicola llena
bool bicola_llena_e(tbicola_e b){
    return b.contador==MAX;
}
//bicola vacia
bool bicola_vacia_e(tbicola_e b){
    return b.contador==0;
}
//siguiente 
int siguiente_e(int index){
    if(index==MAX-1){
        index=0;
    }else{
        index++;
    }
    return index;
}
//anterior 
int anterior_e(int index){
    if(index==0){
        index=MAX-1;
    }else{
        index--;
    }
    return index;
}
//agregar bicola
void agregar_bicola_e(tbicola_e &b,int valor){
    if(bicola_llena_e(b)){
        cout<<"BICOLA LLENA MI ESTIMADO JUGADOR"<<endl<<endl;
    }else{
        b.fin=siguiente_e(b.fin);
    }
}
// quitar bicola por opcion verdadero o falso
int quitar_bicola_e(tbicola_e &b,bool inicio){
    int extraido;
    if(bicola_vacia_e(b)){
        extraido=-99999;
    }else{
        if(inicio==true){
            //elimina por el frente
            b.frente=siguiente_e(b.frente);
            extraido=b.dato[b.frente];
        }else{
            //elimina por el final
            extraido=b.dato[b.fin];
            b.frente=anterior_e(b.frente);
        }
       
    }
    return extraido;
}
//consultar el primer elemento del frente
int consultar_primero_e(tbicola_e b){
    int valor_frente;
    if(bicola_vacia_e(b)){
        valor_frente=-99999;
    }else{
        valor_frente=siguiente_e(b.dato[b.frente]);
    }
    return valor_frente;
}
//consultar el ultimo elemento 
int consultar_ultimo_e(tbicola_e b){
    int valor_final;
    if(bicola_vacia_e(b)){
        valor_final=-99999;
    }else{
        valor_final=b.dato[b.frente];
    }
    return valor_final;
}

// contador
int contador_e(tbicola_e b){
    return b.contador;
}