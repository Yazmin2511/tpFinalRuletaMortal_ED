#include <iostream>
#include <cstring> // Biblioteca para strcpy
#include "t_cad.hpp"
typedef struct tjugador *pjugador;

typedef struct player{
    tcad apellido;
    tcad nombre;
    tcad nickname;
    int mejor_puntaje;  // cambiar //nickname -> jugador
    int puntaje_total; // +=puntaje
    int cantidad_partidas_ganadas; // ++
};

typedef struct tjugador{
    player jugador;
    pjugador izq;
    pjugador der;
};

void inicializar_arbol(pjugador&p)
{   
    p=NULL;
}


bool busqueda(pjugador p, tcad nickname){
    bool encontrado;
    if(p == NULL){
        return false;
    }else{
        if(strcmp( p->jugador.nickname , nickname) == 0)
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

void crear_nodo(pjugador&p , pjugador arbol)
{   bool nickname_repetido=true;
    p = new tjugador;
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
void crear_nodo_temp(pjugador &p, tcad nombre, tcad apellido, tcad nickname) 
{ p = new tjugador; 
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

// void insertar(pjugador&arbol , pjugador nuevo)
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


void insertar(pjugador& arbol, pjugador nuevo)
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

void mostrar_orden(pjugador arbol , bool asc)
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

pjugador busqueda_datos(pjugador a,tcad buscado) 
{ pjugador encontrado=NULL;
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

void mostrar_jugador(pjugador a)
{
    std::cout << "Jugador: " << a->jugador.nombre << " " << a->jugador.apellido 
                    << " (" << a->jugador.nickname << ") | Mejor Puntaje: " << a->jugador.mejor_puntaje 
                    << " | Puntaje Total: " << a->jugador.puntaje_total 
                    << " | Partidas Ganadas: " << a->jugador.cantidad_partidas_ganadas << std::endl;
}


void modificar_jugador(pjugador arbol,tcad nickname)
{
    pjugador buscado = busqueda_datos(arbol,nickname);
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


pjugador eliminar_nodo(pjugador& arbol, tcad nickname, pjugador& padre) {
    if (!arbol) {
        return NULL; // Nodo no encontrado
    }

    if (strcmp(nickname, arbol->jugador.nickname) < 0) {
        return eliminar_nodo(arbol->izq, nickname, arbol);
    } else if (strcmp(nickname, arbol->jugador.nickname) > 0) {
        return eliminar_nodo(arbol->der, nickname, arbol);
    } else { // Nodo encontrado
        pjugador eliminado = arbol;

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
            pjugador sucesor = arbol->der;
            pjugador padre_sucesor = arbol;
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

int cantidad_jugadores( pjugador arbol)
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

void generar_cuadro_de_honor(pjugador arbol,pjugador&aux)
{
     if(arbol != NULL )
    {   
        if(arbol->jugador.puntaje_total==0)
            insertar(aux,arbol);
        
        generar_cuadro_de_honor(arbol->izq,aux);
        generar_cuadro_de_honor(arbol->der,aux);
    }
}

void mostrar_cuadro_honor(pjugador arbol,bool asc)
{pjugador aux=NULL;
    generar_cuadro_de_honor(arbol,aux);
    if(aux == NULL)
        std::cout<<"No hay jugadores con puntajes mayores a 0"<<std::endl;
    else
    {
        std::cout << "\n"; 
        std::cout << "====================================" << std::endl; 
        std::cout << " *** Cuadro de Honor *** " << std::endl; 
        std::cout << "====================================" << std::endl; 
        std::cout << "\n";
         mostrar_orden(aux,asc);
    }
       
}

void obtener_nombre_apellido(tcad archivo, tcad nickname, tcad &nombre, tcad &apellido) { 
    FILE *file = fopen(archivo, "rb"); 
    if (file == NULL) { 
        std::cout << "El archivo no existe o no pudo abrirse.\n"; return; 
        } 
        player temp_jugador; 
        while (fread(&temp_jugador, sizeof(player), 1, file)) { 
            if (strcmp(temp_jugador.nickname, nickname) == 0) { 
                strcpy(nombre, temp_jugador.nombre); 
                strcpy(apellido, temp_jugador.apellido); 
                fclose(file); 
               return; 
            } 
         } 
         fclose(file); 
        std::cout << "Jugador con nickname \"" << nickname << "\" no encontrado.\n"; 
}

void modificar_ganador(tcad& archivo, tcad nickname, int puntaje_total) {
    FILE *file = fopen(archivo, "rb+");
    if (file == NULL) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }
    player temp_jugador;
    while (fread(&temp_jugador, sizeof(player), 1, file)) {
        if (strcmp(temp_jugador.nickname, nickname) == 0) {
            if (puntaje_total > temp_jugador.mejor_puntaje)
                temp_jugador.mejor_puntaje = puntaje_total;

            temp_jugador.cantidad_partidas_ganadas++;
            temp_jugador.puntaje_total += puntaje_total;

            // Mueve el puntero de archivo hacia atrás para sobrescribir el registro
            fseek(file, -sizeof(player), SEEK_CUR);
            fwrite(&temp_jugador, sizeof(player), 1, file);
            fclose(file);
            return;
        }
    }

    fclose(file);
    std::cout << "Jugador con nickname \"" << nickname << "\" no encontrado.\n";
}

