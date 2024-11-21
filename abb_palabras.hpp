#include <iostream>
#include <cstring> 
#include "t_cad.hpp"

typedef struct tpalabra *ppalabra;

typedef struct palabra{
    tcad palabra;  
    tcad definicion;
    tsinonimo sinonimos;  
    int cant_sinonimo;
};

typedef struct tpalabra{
    palabra pal;
    ppalabra izq;
    ppalabra der;
};



void inicializar_arbol_palabras(ppalabra&p)
{   
    p=NULL;
    p->pal.cant_sinonimo=0;
}

bool busqueda_palabra(ppalabra p, tcad nueva_palabra){
    bool encontrado;
    if(p==NULL){
        return false;
    }else{
        if(strcmp(p->pal.palabra, nueva_palabra) == 0)
            return true;
        else{
            if(p->pal.palabra[0] >nueva_palabra[0])
                encontrado=busqueda_palabra(p->izq,nueva_palabra);
            else
                encontrado=busqueda_palabra(p->der,nueva_palabra);
        }
    }

    return encontrado;
}

ppalabra busqueda_palabra_datos(ppalabra p, tcad nueva_palabra){
    bool encontrado;
    if(p==NULL){
        return NULL;
    }else{
        if(strcmp(p->pal.palabra, nueva_palabra) == 0)
            return p;
        else{
            if(p->pal.palabra[0] >nueva_palabra[0])
                encontrado=busqueda_palabra_datos(p->izq,nueva_palabra);
            else
                encontrado=busqueda_palabra_datos(p->der,nueva_palabra);
        }
    }

    return NULL;
}

void crear_nodo_palabras(ppalabra&p , ppalabra arbol)
{   bool palabra_repetida=true , ingresar_mas=true;
    tcad resp;
    p = new tpalabra;
    if(p == NULL)
        std::cout<<"Memoria llena"<<std::endl;
    else
    {   
            do{
                std::cout<<"Ingrese palabra"<<std::endl;
                std::cin>>p->pal.palabra;

                palabra_repetida = busqueda_palabra(arbol,p->pal.palabra);
                if(palabra_repetida == true)
                    std::cout<<"Esta palabra ya esta registrada"<<std::endl;
            }while(palabra_repetida == true);
            

            std::cout<<"Ingrese definicion"<<std::endl;
            std::cin>>p->pal.definicion;

            std::cout<<"Desea ingresar un sinonimo?"<< std::endl;
            std::cin>>resp;
            //inicializar sinonimo
            while(strcmp(resp,"si") == 0 && p->pal.cant_sinonimo < 3)
            {

                std::cout<<"Ingrese sinonimo"<<std::endl;
                std::cin>>p->pal.sinonimos[p->pal.cant_sinonimo];
                p->pal.cant_sinonimo++;

                std::cout<<"Desea ingresar otro sinonimo?"<< std::endl;
                std::cin>>resp;
            }
        

        p->izq = NULL;
        p->der = NULL;
    }
}

ppalabra eliminar_palabra(ppalabra arbol)
{
    return NULL;
}

void listar_palabras(ppalabra arbol)
{
    if(arbol != NULL)
    {
            listar_palabras(arbol->izq);
            std::cout<<arbol->pal.palabra<<" "<<std::endl;
            listar_palabras(arbol->der);
    }
}

void agregar_palabra(ppalabra&arbol,ppalabra nuevo)
{
     if (arbol == NULL)
    {
        arbol = nuevo; 
    }
    else if (strcmp(nuevo->pal.palabra, arbol->pal.palabra) < 0) 
    {
        agregar_palabra(arbol->izq, nuevo); 
    }
    else if (strcmp(nuevo->pal.palabra, arbol->pal.palabra) > 0) 
    {
        agregar_palabra(arbol->der, nuevo); 
    }
}