#include <iostream>
//#include "abb_jugadores.hpp"
#include "archivos_jugadores.hpp"
#include "archivo_palabras.hpp"
using namespace std;



void opciones() {
    
    cout << "=====================================" << endl;
    cout << "       ¡BIENVENIDO AL JUEGO!        " << endl;
    cout << "=====================================" << endl;

    cout << "1. Gestion de jugadores" << endl;
    cout << "2. Crear ruleta de palabras" << endl;
    cout << "3. Jugar" << endl;
    cout << "4. Cuadro de honor" << endl;
    cout << "5. Salir del juego" << endl;
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
    cout << "6. Volver al menu anterior" << endl;
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
    cout << "4. Volver al menu anterior" << endl;
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
    cout << "4. Volver al menu anterior" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}
void menu_principal_gestion_jugador()
{
    pnodo jugadores = NULL;
    int opcion;
    tcad archivo = "jugadores.dat";
    
    do{
        system("cls");
        menu_gestion_jugadores();
        cin >> opcion;
      
        switch (opcion)
        {
        case 1:     
        agregar_jugador(archivo, jugadores);
         break;
        case 2:     
            {
            tcad buscado;
            std::cout<<"Ingrese el nickname del usuario a buscar ";
            std::cin>>buscado;
            buscar_jugador(archivo, buscado);
            system("pause");
            break;
            }
        
        break;
        case 3:     
            {
                tcad nickname;
                std::cout << "Ingrese nickname a modificar: ";
                std::cin >> nickname;
                modificar_jugador_archivo(archivo, nickname);
                break;
            }
        case 4:   

                listar_jugadores(archivo, true);
                system("pause");
                break;
        case 5:     
        {   
            tcad nickname;
            std::cout << "Ingrese nickname a eliminar: ";
            std::cin >> nickname;
            eliminar_jugador(archivo, nickname);
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
    ppalabra palabras=NULL;
    tcad archivo = "palabras.dat";
    int opcion ;
    do{
        system("cls");
        menu_crear_ruletas_palabras();
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            registrar_palabra(archivo,palabras);
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
        case 3: //Jugar
            if(jugadores == NULL)
                std::cout<<"No hay jugadores registrados"<<std::endl;
            else
            {
                if(cantidad_jugadores(jugadores) < 2)
                    std::cout<<"Necesita al menos 2 jugadores para iniciar el juego"<<std::endl;
                else
                {   
                    menu_principal_jugar();
                }
            }
            system("pause");
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