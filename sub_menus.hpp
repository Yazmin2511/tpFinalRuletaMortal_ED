#include <iostream>
#include "abb_jugadores.hpp"
using namespace std;



void opciones() {
    
    cout << "=====================================" << endl;
    cout << "       ¡BIENVENIDO AL JUEGO!        " << endl;
    cout << "=====================================" << endl;

    cout << "1. Gestion de jugadores" << endl;
    cout << "2. Crear ruleta de palabras" << endl;
    cout << "3. Jugar" << endl;
    cout << "4. Cuadro de honor" << endl;
    cout << "5. Salir" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}

void menu_gestion_jugadores(){
    cout << "=====================================" << endl;
    cout << "               JUGADOR               " << endl;
    cout << "=====================================" << endl;

    cout << "1. Agregar jugador" << endl;
    cout << "2. Consultar" << endl;
    cout << "3. Modificar jugador" << endl;
    cout << "4. Lista de jugadores" << endl;
    cout << "5. Eliminar jugador" << endl;
    cout << "6. Salir" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}
void menu_crear_ruletas_palabras(){
    cout << "=====================================" << endl;
    cout << "               RULETA               " << endl;
    cout << "=====================================" << endl;

    cout << "1. Registrar palabras" << endl;
    cout << "2. GENERAR RULETA" << endl;
    cout << "3. Mostrar ruleta" << endl;
    cout << "4. Salir" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}
void menu_jugar(){
    cout << "=====================================" << endl;
    cout << "                 JUGAR               " << endl;
    cout << "=====================================" << endl;

    cout << "1. Registrar palabras" << endl;
    cout << "2. GENERAR RULETA" << endl;
    cout << "3. Mostrar ruleta" << endl;
    cout << "4. Salir" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}
void menu_principal_gestion_jugador()
{
    int opcion;
    pnodo arbol, nuevo;
    inicializar_arbol(arbol);
    do{
        system("cls");
        menu_gestion_jugadores();
        cin >> opcion;
      
        switch (opcion)
        {
        case 1:
        {
            //pnodo nuevo; // Mueve la declaración aquí
            crear_nodo(nuevo,arbol);
            insertar(arbol, nuevo);
            break;
        }
        case 2: 
        {
            tcad buscado;
            cout << "Ingrese nickname de jugador: ";
            cin >> buscado;

            nuevo = busqueda_datos(arbol, buscado);

            if (nuevo == NULL) {
                cout << "Jugador no existe" << endl;
            } else {
                cout << "Jugador: " << nuevo->jugador.nombre << " " << nuevo->jugador.apellido 
                    << " (" << nuevo->jugador.nickname << ") | Mejor Puntaje: " << nuevo->jugador.mejor_puntaje 
                    << " | Puntaje Total: " << nuevo->jugador.puntaje_total 
                    << " | Partidas Ganadas: " << nuevo->jugador.cantidad_partidas_ganadas << endl;
            }

            system("pause");
            break;
        }
        case 3:
            // Lógica para el caso 3
            system("pause");
            break;
        case 4:
            // Lógica para el caso 4
            //cout para elegir si mostrar en asc o desc
            std::cout<<"_________________Jugadores______________"<<std::endl;
            mostrar_orden(arbol,true);
            system("pause");
            break;
        case 5:
            // Lógica para el caso 5
            system("pause");
            break;
        case 6:
            std::cout << "sigue asi vamos guerrero" << std::endl;
            system("pause");
            break;
        default:
            break;
        }
       
    } while (opcion != 6);
   
}

void menu_principal_ruleta_palabras()
{
    int opcion ;
    do{
         system("cls");
        menu_crear_ruletas_palabras();
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            
            break;
        case 2:
           
            break;
        case 3:
            
            break;
      
        case 4:
            cout<<"sigue asi vamos guerrero"<<endl;
            break;
        
        default:
            break;
        }

    }while(opcion!=4);

}
void menu_principal_jugar()
{
    int opcion ;
    do{
         system("cls");
        menu_jugar();
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            
            break;
        case 2:
           
            break;
        case 3:
            
            break;
      
        case 4:
            cout<<"BYE GUERREROS"<<endl;
            break;
        
        default:
            break;
        }

    }while(opcion!=4);

}
void menu()
{
    int opcion ;
    do{
        system("cls");
        opciones();
        
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            menu_principal_gestion_jugador();
            break;
        case 2:
            menu_principal_ruleta_palabras();
            break;
        case 3:
            menu_principal_jugar();
            break;
        case 4:
            
            break;
        case 5:
            cout<<"Bye valiente jugador"<<endl;
            break;
        
        default:
            break;
        }

    }while(opcion!=5);

}