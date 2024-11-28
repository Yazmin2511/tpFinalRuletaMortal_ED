#include <iostream>
//#include "abb_jugadores.hpp"
#include "archivos_jugadores.hpp"
#include "archivo_palabras.hpp"
#include "tda_palabra_ruleta.hpp"
#include "t_cad.hpp"
#include "animaciones.hpp"
#include "tda_cola_turno.hpp"
using namespace std;

pjugador jugadores = NULL;
ppalabra palabras=NULL;
listaRuleta ruleta_palabras;
cola_turnos turnos;
//verifica que la ruleta haya sido creada 
bool ruleta_creada=false;

void crear_comprobarCadenaNoVacia(tcad& cadena , tcad mensaje) {
    bool esValida = false;
    while (!esValida) 
    {
        std::cout << mensaje;
        std::cin.getline(cadena, 50);
        if (strlen(cadena) == 0)
            std::cout << "La cadena no puede estar vacía. Intente nuevamente." << std::endl;
        else
            esValida = true;
    }
}

void opciones(){
    
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

void menu_juego_encurso(tcad palabraActual, pturno&turno)
{
    cout << "=====================================" << endl;
    cout << " Palabra :" <<palabraActual<<endl;
    cout << "=====================================" << endl;

    cout << "Turno del jugador: " <<turno->nickname<<" Vidas restantes: "<< turno->cantidad_vidas<< endl;
    cout << "1. Probar una letra (-1 vida)" << endl;
    cout << "2. Solicitar primera letra" << endl;
    cout << "3. Solicitar una pista" << endl;
    cout << "4. Arriesgar la palabra (-1 vida)" << endl;
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
                    while(ruleta_palabras.inicio!=NULL){
                        extraer_final_ruleta_palabra(ruleta_palabras);
                    }
                    //con esto la opcion 2 de jugar queda inabilitada 
                    ruleta_creada=false;
                    cout<<"vacio"<<endl;
                    contador=0;
                }
                cout << "Ingrese la cantidad de palabras para la ruleta (mínimo 5): ";
                cin >> cantidad; 
                if(cantidad<5){
                    cout<<"Se debe Ingresar 5 o mas "<<endl;
                }else{
                    generar_ruleta(archivo_palabras, ruleta_palabras, cantidad);
                    contador++;
                    //se utiliza para verificar que la ruletra es creada previamente
                     ruleta_creada=true; 
                }
               system("pause");
                break; 
            }
        case 3:
          //  
            mostrar_ruleta_palabra(ruleta_palabras);
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

// switch
void menu_gestion_opciones_juego(pturno turno,palabra_rul palabra,tcad&palabraGuiones) {
    int opcion,opcion2;
    tcad palabraArriesgada;
    bool sigueElJuego = true;
    cin >> opcion;
    while(sigueElJuego == true)
    {
        switch (opcion) {
        case 1:
            probarLetraPalabra(palabra.palabra, palabraGuiones);
            turno->cantidad_vidas -= 1;
            break;
        case 2:
            turno->cantidad_vidas -= 1;
            probarLetraPalabra(palabra.palabra,palabraGuiones);
            break;
        case 3:     // Pistas sinonimos o definicion
        {
            cout<<"1 Definicion (-2 vidas) "<<endl;
            cout<<"2 Sinonimo (-3 vidas) "<<endl;
            cout<<"Elija opcion:  "<<endl;
            cin>>opcion2;
            if(opcion2 == 1)
            {  if((turno->cantidad_vidas-2) > 0 )
                {
                    turno->cantidad_vidas -= 2;
                    cout<<palabra.definicion<<endl;
                }
                else
                    cout<<"Vidas insuficientes"<<endl;
                    
            }
            else
            {   if((turno->cantidad_vidas-3) > 0 )
                {
                    turno->cantidad_vidas -= 3;
                    cout<<palabra.sinonimos<<endl;
                    
                }
                else
                    cout<<"Vidas insuficientes"<<endl;
                
            }
        }
        break;

        case 4: //Arriesgar palabra
                turno->cantidad_vidas -= 1;
                cout<< "Ingrese palabra"<<endl;
                cin>>palabraArriesgada;
                if(strcmp(palabra.palabra,palabraArriesgada) == 0)
                {
                    turno->cantidad_vidas+=3;
                    cout << "========================" << endl; 
                    cout << "¡¡¡FELICIDADES!!! 🎉🎉🎉" << endl; 
                    cout << "Has acertado la palabra." << endl; 
                    cout << "========================" << endl;
                    sigueElJuego = false;
                    // Agregar la palabra a la pila del jugador . 
                }
                else
                {
                    cout << "========================" << endl; 
                    cout << "💔 ¡FALLASTE! 💔" << endl; 
                    cout << "La palabra no es correcta." << endl; 
                    cout << "========================" << endl;
                }
            break;

        default:
            // Opción inválida
            break;
    }

    }
    

}



void menu_principal_gestion_jugar()
{ 
    tcad archivo1 = "jugadores.dat";
    tcad nickname,nombre,apellido;
    inicializar_turnos(turnos);
    pturno turno;
    int opcion ;
    tcad palabraGuiones;
    do{
        system("cls");
        menu_jugar();
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            {   cout<<"********** Jugadores disponibles **********"<<endl;
                mostrar_orden(jugadores,true);
                cout<<"Ingrese nickname de jugador a elegir"<<endl;
                cin>>nickname;

                obtener_nombre_apellido(archivo1,nickname,nombre,apellido);
                cout<<"Nombre: "<<nombre<<" , Apellido: "<<apellido<<endl;
                crear_turno(turno,nickname);

                if(buscar_jugador_repetido(turnos,nickname) == true)    // Validacion para que no se repitan los jugadores en la cola
                    cout<<"Jugador ya seleccionado"<<endl;
                else
                    cola_agregar_turno(turnos,turno);
                system("pause");
            }
            break;
        case 2:
            {
                if(ruleta_creada==true){
                    if(turnos.cantidad >=2)
                    {   // otra validacion que termine el bucle cuando haya 1 jugador restante
                        for(pruleta palabraEnJuego=ruleta_palabras.inicio; palabraEnJuego!= NULL && turnos.cantidad>=2 ; palabraEnJuego=palabraEnJuego->sig)
                        {   //menu_turnos_juego();
                            convertirPalabraAGuiones(palabraEnJuego->dato.palabra,palabraGuiones);
                            do{
                                turno = cola_quitar_turno(turnos);
                                menu_juego_encurso(palabraEnJuego->dato.palabra,turno);
                                if(turno->cantidad_vidas > 0)
                                {
                                    cola_agregar_turno(turnos,turno);
                                    menu_gestion_opciones_juego(turno,palabraEnJuego->dato,palabraGuiones);
                                }
                             
                                
                            }while(turnos.cantidad >=2 );
                        }

                        if(turnos.cantidad == 1)
                        {   // La animacion
                            system("pause");
                            system("cls");
                            cout << "Calculando puntaje final"<< endl;
                            system("pause");
                            system("cls");
                            // buscamos el jugador por el nick y le sumamos el puntaje 
                            //Mostramos por pantalla
                        }
                        else
                        {
                            
                        }


                    }
                    else{
                    cout<<endl;
                    cout<<"**********************Estimado seleccione al menos 2 jugadores*********************"<<endl;
                    cout<<endl;
                }

                }else{
                    cout<<endl;
                    cout<<"**********************Estimado debe generar la ruleta*********************"<<endl;
                    cout<<endl;
                }
            }
            system("pause");
            break;

      
        case 3:
            
            cout<<"BYE GUERREROS"<<endl;
            break;
        
        default:
            break;
        }

    }while(opcion!=3);

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
                    menu_jugar();
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