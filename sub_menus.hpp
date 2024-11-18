#include <iostream>
#include "abb_jugadores.hpp"
using namespace std;

pnodo arbol;

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
    inicializar_arbol(arbol);
    do{
        system("cls");
        menu_gestion_jugadores();
        cin >> opcion;
      
        switch (opcion)
        {
        case 1:     //Agregar jugador
        {   
            pnodo nuevo;
            crear_nodo(nuevo,arbol);
            insertar(arbol, nuevo);
            break;
        }
        case 2:     //Consultar jugador
        {   
            pnodo jugador;
            tcad buscado;
            cout << "Ingrese nickname de jugador: ";
            cin >> buscado;

            jugador = busqueda_datos(arbol, buscado);

            if (jugador == NULL) {
                cout << "Jugador no existe" << endl;
            } else {
                 mostrar_jugador(jugador);
            }

            system("pause");
            break;
        }
        case 3:     //Modificar jugador
            tcad buscado;
            pnodo nuevo;
            std::cout<<"Ingrese el nickname del usuario a modificar ";
            std::cin>>buscado;
            nuevo=busqueda_datos(arbol,buscado);
            system("pause");
            break;
        case 4:     //Listar jugadores
        {   
            if(arbol != NULL)
            {
                char opcion;
                do {
                    std::cout << "Ver jugadores en orden ascendente o descendente? (A/D): ";
                    std::cin >> opcion;
                    opcion = toupper(opcion);
                } while (opcion != 'A' && opcion != 'D');

                std::cout << "_________________Jugadores______________" << std::endl;
                mostrar_orden(arbol, opcion == 'A');
            }
            else
                std::cout<<"No hay jugadores registrados"<<std::endl;
            
            system("pause");
            break;
        }
        case 5:     //Eliminar jugador
        {   // Lógica para el caso 5
            system("pause");
            break;
        } 
        case 6:
        {
            std::cout << "sigue asi vamos guerrero" << std::endl;
            system("pause");
            break;
        default:
        {   
            break;

        }
            
        }
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