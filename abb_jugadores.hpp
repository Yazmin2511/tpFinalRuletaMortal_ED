#include <iostream>
#include <cstring> // Biblioteca para strcpy
typedef char tcad[30];
typedef struct tnodo *pnodo;

typedef struct tjugador{
    tcad apellido;
    tcad nombre;
    tcad nickname;
    int mejor_puntaje;
    int puntaje_total;
    int cantidad_partidas_ganadas;
};

typedef struct tnodo{
    tjugador jugador;
    pnodo izq;
    pnodo der;
};

void inicializar_arbol(pnodo&p)
{
    p->izq = NULL;
    p->der = NULL;
}

void crear_nodo(pnodo&p)
{
    p = new tnodo;
    if(p == NULL)
        std::cout<<"Memoria llena"<<std::endl;
    else
    {
        std::cout<<"Ingrese nombre"<<std::endl;
        std::cin>>p->jugador.nombre;
        std::cout<<"Ingrese apellido"<<std::endl;
        std::cin>>p->jugador.apellido;
        std::cout<<"Ingrese nickname"<<std::endl;
        std::cin>>p->jugador.nickname;

        p->jugador.mejor_puntaje = 0;
        p->jugador.puntaje_total = 0;
        p->jugador.cantidad_partidas_ganadas = 0;

        p->izq = NULL;
        p->der = NULL;
    }
}

void crear_nodo_temp(pnodo &p, const char *nombre, const char *apellido, const char *nickname) 
{ p = new tnodo; 
    if (p == NULL) 
    std::cout<< "Memoria llena" << std::endl; 
    else { // Copia los valores de los punteros char* a los arreglos de char 
        strcpy(p->jugador.nombre, nombre); 
        strcpy(p->jugador.apellido, apellido); 
        strcpy(p->jugador.nickname, nickname); 
        p->jugador.mejor_puntaje = 0; 
        p->jugador.puntaje_total = 0; 
        p->jugador.cantidad_partidas_ganadas = 0; 
        p->izq = NULL; 
        p->der = NULL; 
    } 
}

void insertar(pnodo&arbol , pnodo nuevo)
{
    if(arbol == NULL)
        arbol = nuevo;
    else
    {
        if(arbol->jugador.nickname[0] > nuevo->jugador.nickname[0])
        {
            insertar(arbol->izq,nuevo);
        }else{
            insertar(arbol->der,nuevo);
        }
    }
}

bool busqueda(pnodo p, tcad nickname){
    bool encontrado;
    if(p==NULL){
        return false;
    }else{
        if(p->jugador.nickname == nickname)
            return true;
        else{
            if(p->jugador.nickname[0] > nickname[0])
                encontrado=busqueda(p->izq,nickname);
            else
                encontrado=busqueda(p->der,nickname);
        }
    }

    return encontrado;
}

void mostrar_orden(pnodo arbol , bool asc)
{
    if(arbol != NULL )
    {   
        if(asc == true)
        {
            mostrar_orden(arbol->izq,asc);
            
            std::cout<<"Nickname "<<arbol->jugador.nickname<<" "<<std::endl;
            mostrar_orden(arbol->der,asc);
        }
        else
        {
            mostrar_orden(arbol->der,asc);
            std::cout<<"Nickname "<<arbol->jugador.nickname<<" "<<std::endl;
            mostrar_orden(arbol->izq,asc);
        }
    }
}



pnodo busqueda_datos(pnodo a,tcad buscado) 
{ pnodo encontrado=NULL;
    if (a!=NULL)
    { 
        if (strcmp(a->jugador.nickname, buscado) == 0) 
            encontrado=a;
        else{
            if (buscado[0] < a->jugador.nickname[0])
                encontrado=busqueda_datos(a->izq,buscado); 
            else
                encontrado=busqueda_datos(a->der,buscado); 
        }
    }
    return encontrado;
}

// pnodo eliminar(pnodo &a,pnodo valor)
// {
//     pnodo aux; 
// if (a==NULL) 
//     aux=NULL; 
// else{
//     if (a->dato > valor)
//         aux=eliminar(a->izq,valor); 
//     else
//     {
//         if (a->dato < valor)
//             aux=eliminar(a->der,valor); 
//         else
//         {
//             aux=a;
//             if(a->izq == NULL)
//                 a=a->der;
//             else
//             {
//                 if(a->der==NULL)
//                     a=a->izq;
//                 else
//                     aux=menor_mayores(a,a->der);
//             }
//         }
//     }
        
// }
// return aux;
// }

// pnodo menor_mayores(pnodo elegido,pnodo &menor) 
// { pnodo aux;
//     if (menor->izq!=NULL)
//         aux=menor_mayores(elegido,menor->izq);
//     else
//     { cambio(elegido->dato,menor->dato);
//         aux=menor; 
//         menor=menor->der;
//     }
//     return aux;
// }
