#include <iostream>
//#include "abb_jugadores.hpp"
#include "archivos_jugadores.hpp"
#include "archivo_palabras.hpp"
#include "lista_doble_dospunteros.hpp"
#include "t_cad.hpp"
#include "animaciones.hpp"
#include "tda_cola_turno.hpp"
using namespace std;

pjugador jugadores = NULL;
ppalabra palabras=NULL;
listaRuleta lis;
cola_turnos turnos;
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

    cout << "1. Seleccionar jugadores" << endl;
    cout << "2. Iniciar juego" << endl;
    cout << "3. Volver al menu anterior" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}
void menu_principal_gestion_jugador()
{
    
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
   
    tcad archivo_palabras = "palabras.dat";
   // lista lis;//lista doble
    int opcion ,contador=0;
    do{
        system("cls");
        menu_crear_ruletas_palabras();
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            registrar_palabra(archivo_palabras,palabras);
            system("pause");
            break;
        case 2:
            { int cantidad; 
                
                if(contador>0){
                    while(lis.inicio!=NULL){
                         extraer_final_ruleta_palabra(lis);
                    }
                    cout<<"vacio"<<endl;
                    contador=0;
                    
                }
                cout << "Ingrese la cantidad de palabras para la ruleta (mínimo 5): ";
                cin >> cantidad; 
                if(cantidad<5){
                    cout<<"Se debe Ingresar 5 o mas "<<endl;
               }else{
                    generar_ruleta(archivo_palabras, lis, cantidad); 
                }
                contador++;
                    
               system("pause");
                break; 
            }
         
         
        case 3:
          //  
            mostrar_ruleta_palabra(lis);
            system("pause");
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
    tcad archivo1 = "jugadores.dat";
    tcad nickname,nombre,apellido;
    inicializar_turnos(turnos);
    pturno turno;
    int opcion ;
    do{
        system("cls");
        menu_jugar();
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            {    cout<<"********** Jugadores disponibles **********"<<endl;
                mostrar_orden(jugadores,true);
                cout<<"Ingrese nickname de jugador a elegir"<<endl;
                cin>>nickname;

                obtener_nombre_apellido(archivo1,nickname,nombre,apellido);
                cout<<"Nombre: "<<nombre<<" , Apellido: "<<apellido<<endl;
                //strcpy(turno->nickname,nickname);

                cola_agregar_turno(turnos,turno);
                system("pause");

                /// Agregar meter a la pila 
            }
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
    tcad archivo = "jugadores.dat"; 
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
            if(contar_jugadores_desde_archivo(archivo)==0)
                std::cout<<"No hay jugadores registrados"<<std::endl;
            else
            {
                if(contar_jugadores_desde_archivo(archivo) < 2)
                    std::cout<<"Necesita al menos 2 jugadores para iniciar el juego"<<std::endl;
                else
                {   
                    menu_principal_jugar();
                }
            }
            system("pause");
            break;
        case 4:
        {   tcad resp;
            std::cout<<"Mostrar puntajes en orden asc o desc? (asc/desc)"<<std::endl;
            std::cin>>resp;
            bool asc = strcmp(resp,"asc")==0;
            mostrar_cuadro_honor(jugadores,asc);
            system("pause");
        }
            break;
        case 5:
            muerte_jugador();
            cout<<"Bye valiente jugador"<<endl;
            break;
        
        default:
            break;
        }

    }while(opcion!=5);

}