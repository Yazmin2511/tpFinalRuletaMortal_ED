#include <iostream>
#include <cstring> 
typedef char tcad[50];
typedef struct tnodo *pnodo;
typedef struct tsinonimo *psinonimo;

typedef struct tpalabra{
    tcad palabra;  
    tcad definicion;
    psinonimo sinonimos;  // Sinonimos puede ser NULL
};

typedef struct tnodo{
    tpalabra palabra;
    pnodo izq;
    pnodo der;
};

typedef struct tsinonimo{
    tcad palabra;
    pnodo sig;
};

void inicializar_arbol_palabras(pnodo&p)
{   
    p=NULL;
}

bool busqueda(pnodo p, tcad nueva_palabra){
    bool encontrado;
    if(p==NULL){
        return false;
    }else{
        if(strcmp(p->palabra.palabra, nueva_palabra) == 0)
            return true;
        else{
            if(p->palabra.palabra[0] >nueva_palabra[0])
                encontrado=busqueda(p->izq,nueva_palabra);
            else
                encontrado=busqueda(p->der,nueva_palabra);
        }
    }

    return encontrado;
}

void crear_nodo_palabras(pnodo&p , pnodo arbol)
{   bool palabra_repetida=true , ingresar_mas=true;
    tcad resp;
    p = new tnodo;
    if(p == NULL)
        std::cout<<"Memoria llena"<<std::endl;
    else
    {   
        //Validacion de que la palabra no esta repetida
            std::cout<<"Ingrese palabra"<<std::endl;
            std::cin>>p->palabra.palabra;

            std::cout<<"Ingrese definicion"<<std::endl;
            std::cin>>p->palabra.definicion;

            std::cout<<"Desea ingresar un sinonimo?"<< std::endl;
            std::cin>>resp;
            //inicializar sinonimo
            while(strcmp(resp,"si") == 0)
            {

                std::cout<<"Ingrese sinonimo"<<std::endl;
                std::cin>>p->palabra.sinonimos->palabra;

                
            }  // Se quieran ingresar + sinonimos
        

        p->izq = NULL;
        p->der = NULL;
    }
}
