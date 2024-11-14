//Prioriza espacio
typedef int contenedor[MAX];
typedef struct tbicola_s
{
    contenedor dato;
    int frente;
    int fin;
    int contador;
};
//inicialización de la bicola
void incializacion_s(tbicola_s &b){
    b.frente=MAX-1;
    b.fin=MAX-1;
    b.contador=0;
}
// bicola llena
bool bicola_llena_s(tbicola_s b){
    return b.contador==MAX;
}
//bicola vacia
bool bicola_vacia_s(tbicola_s b){
    return b.contador==0;
}
//siguiente 
int siguiente_s(int index){
    if(index==MAX-1){
        index=0;
    }else{
        index++;
    }
    return index;
}
//anterior 
int anterior_s(int index){
    if(index==0){
        index=MAX-1;
    }else{
        index--;
    }
    return index;
}
//agregar por opcion verdadero o falso
void agregar_bicola_s(tbicola_s &b,int valor,bool final){
    if(bicola_llena_s(b)){
        cout<<"BICOLA LLENA MI ESTIMADO JUGADOR"<<endl<<endl;
    }else{
        if(final==true){
            //se agregara por el final
            b.fin=siguiente_s(b.fin);
            b.dato[b.fin]=valor;
        }else{
            // se agregara por el frente
            b.dato[b.frente]=valor;
            b.frente=anterior_s(b.frente);
        }
    }
}
// quitar bicola
int quitar_bicola_s(tbicola_s &b){
    int extraido;
    if(bicola_vacia_s(b)){
        extraido=-99999;
    }else{
        b.frente=siguiente_s(b.frente);
        extraido=b.dato[b.frente];
    }
    return extraido;
}
//consultar el primer elemento del frente
int consultar_primero_s(tbicola_s b){
    int valor_frente;
    if(bicola_vacia_s(b)){
        valor_frente=-99999;
    }else{
        valor_frente=siguiente_s(b.dato[b.frente]);
    }
    return valor_frente;
}
//consultar el ultimo elemento 
int consultar_ultimo_s(tbicola_s b){
    int valor_final;
    if(bicola_vacia_s(b)){
        valor_final=-99999;
    }else{
        valor_final=b.dato[b.frente];
    }
    return valor_final;
}

// contador
int contador_s(tbicola_s b){
    return b.contador;
}