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
    p=NULL;
}


bool busqueda(pnodo p, tcad nickname){
    bool encontrado;
    if(p==NULL){
        return false;
    }else{
        if(strcmp(p->jugador.nickname, nickname) == 0)
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

void crear_nodo(pnodo&p , pnodo arbol)
{   bool nickname_repetido=true;
    p = new tnodo;
    if(p == NULL)
        std::cout<<"Memoria llena"<<std::endl;
    else
    {   
      
            std::cout<<"Ingrese nombre"<<std::endl;
            std::cin>>p->jugador.nombre;

            std::cout<<"Ingrese apellido"<<std::endl;
            std::cin>>p->jugador.apellido;
            
         do{
            std::cout<<"Ingrese nickname"<<std::endl;
            std::cin>>p->jugador.nickname;

            nickname_repetido = busqueda(arbol,p->jugador.nickname);
            if(nickname_repetido == true)
            {
                std::cout<<"Nickname no disponible"<<std::endl;
                system("pause");
            }
                
        }while(nickname_repetido == true );
        

        p->jugador.mejor_puntaje = 0;
        p->jugador.puntaje_total = 0;
        p->jugador.cantidad_partidas_ganadas = 0;

        p->izq = NULL;
        p->der = NULL;
    }
}

//Eliminar si no lo usamos 
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

// void insertar(pnodo&arbol , pnodo nuevo)
// {
//     if(arbol == NULL)
//         arbol = nuevo;
//     else
//     {
//         if(arbol->jugador.nickname[0] > nuevo->jugador.nickname[0])
//         {
//             insertar(arbol->izq,nuevo);
//         }else{
//             insertar(arbol->der,nuevo);
//         }
//     }
// }


void insertar(pnodo& arbol, pnodo nuevo)
{
    if (arbol == NULL)
    {
        arbol = nuevo; // Insertamos el nodo en la posición adecuada
    }
    else if (strcmp(nuevo->jugador.nickname, arbol->jugador.nickname) < 0) 
    {
        insertar(arbol->izq, nuevo); // Va a la izquierda si es menor
    }
    else if (strcmp(nuevo->jugador.nickname, arbol->jugador.nickname) > 0) 
    {
        insertar(arbol->der, nuevo); // Va a la derecha si es mayor
    }
}

void mostrar_orden(pnodo arbol , bool asc)
{  
    if(arbol != NULL )
    {   
        if(asc == true)
        {
            mostrar_orden(arbol->izq,asc);
            std::cout<<arbol->jugador.nickname<<" "<<std::endl;
            mostrar_orden(arbol->der,asc);
        }
        else
        {
            mostrar_orden(arbol->der,asc);
            std::cout<<arbol->jugador.nickname<<" "<<std::endl;
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

void mostrar_jugador(pnodo a)
{
    std::cout << "Jugador: " << a->jugador.nombre << " " << a->jugador.apellido 
                    << " (" << a->jugador.nickname << ") | Mejor Puntaje: " << a->jugador.mejor_puntaje 
                    << " | Puntaje Total: " << a->jugador.puntaje_total 
                    << " | Partidas Ganadas: " << a->jugador.cantidad_partidas_ganadas << std::endl;
}


void modificar_jugador(pnodo arbol,tcad nickname)
{
    pnodo buscado = busqueda_datos(arbol,nickname);
    if(buscado == NULL)
        std::cout<<"Nickname no encontrado"<<std::endl;
    else
    {       // Falta la validacion de los campos
        std::cout<<"Ingrese nuevo apellido ";
        std::cin>>buscado->jugador.apellido;
        std::cout<<"Ingrese nuevo nombre ";
        std::cin>>buscado->jugador.nombre;

        std::cout<<"Jugador modificado "<<std::endl;
        mostrar_jugador(buscado);
    }
}


pnodo eliminar_nodo(pnodo& arbol, tcad nickname, pnodo& padre) {
    if (!arbol) {
        return NULL; // Nodo no encontrado
    }

    if (strcmp(nickname, arbol->jugador.nickname) < 0) {
        return eliminar_nodo(arbol->izq, nickname, arbol);
    } else if (strcmp(nickname, arbol->jugador.nickname) > 0) {
        return eliminar_nodo(arbol->der, nickname, arbol);
    } else { // Nodo encontrado
        pnodo eliminado = arbol;

        // Caso 1: Nodo sin hijos
        if (!arbol->izq && !arbol->der) {
            arbol = NULL;
        }
        // Caso 2: Nodo con un hijo
        else if (!arbol->izq) {
            arbol = arbol->der;
        } else if (!arbol->der) {
            arbol = arbol->izq;
        }
        // Caso 3: Nodo con dos hijos
        else {
            pnodo sucesor = arbol->der;
            pnodo padre_sucesor = arbol;
            while (sucesor->izq) {
                padre_sucesor = sucesor;
                sucesor = sucesor->izq;
            }
            arbol->jugador = sucesor->jugador; // Copiar datos del sucesor
            eliminado = eliminar_nodo(arbol->der, sucesor->jugador.nickname, padre_sucesor);
        }

        return eliminado;
    }
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


int cantidad_jugadores(pnodo arbol)
{
    int cant;
    if(arbol == NULL)
        return 0;
    else
    {
        cant=cantidad_jugadores(arbol->izq)+cantidad_jugadores(arbol->der)+1;
    }

    return cant;
}