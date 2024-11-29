#include <iostream>
//#include "abb_jugadores.hpp"
#include "archivos_jugadores.hpp"
#include "archivo_palabras.hpp"
#include "tda_palabra_ruleta.hpp"
#include "t_cad.hpp"
#include "animaciones.hpp"
#include "tda_cola_turno.hpp"
#include <stdlib.h>


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
            std::cout << "La cadena no puede estar vacia. Intente nuevamente." << std::endl;
        else
            esValida = true;
    }
}

void opciones(){
    
    std::cout << "=====================================" << std::endl;
    std::cout << "       ¡BIENVENIDO AL JUEGO!        " << std::endl;
    std::cout << "=====================================" << std::endl;

    std::cout << "1. Gestion de jugadores" << std::endl;
    std::cout << "2. Crear ruleta de palabras" << std::endl;
    std::cout << "3. Jugar" << std::endl;
    std::cout << "4. Cuadro de honor" << std::endl;
    std::cout << "5. Salir del juego" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Elija una opcion: ";
}

void menu_gestion_jugadores(){
    std::cout << "=====================================" << std::endl;
    std::cout << "               JUGADOR               " << std::endl;
    std::cout << "=====================================" << std::endl;

    std::cout << "1. Agregar jugador" << std::endl;
    std::cout << "2. Consultar" << std::endl;
    std::cout << "3. Modificar jugador" << std::endl;
    std::cout << "4. Lista de jugadores" <<std::endl;
    std::cout << "5. Eliminar jugador" << std::endl;
    std::cout << "6. Volver al menu anterior" << std::endl;
    std::cout << "=====================================" <<std::endl;
    std::cout << "Elija una opcion: ";
}
void menu_crear_ruletas_palabras(){
    std::cout << "=====================================" << std::endl;
    std::cout << "               RULETA               " << std::endl;
    std::cout << "=====================================" << std::endl;

    std::cout << "1. Registrar palabras" << std::endl;
    std::cout << "2. GENERAR RULETA" << std::endl;
    std::cout << "3. Mostrar ruleta" << std::endl;
    std::cout << "4. Volver al menu anterior" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Elija una opcion: ";
}

void menu_principal_gestion_jugador()
{
    
    int opcion;
    tcad archivo = "jugadores.dat";
    tcad asc;
    do{
        system("cls");
        menu_gestion_jugadores();
        std::cin >> opcion;
      
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
                crear_comprobarCadenaNoVacia(asc,"Listar de forma asc/desc: ");
                if(strcmp(asc,"asc")==0)
                    listar_jugadores(archivo, true);
                else
                    listar_jugadores(archivo, false);
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
        std::cin>>opcion;
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
                    contador=0;
                }
                std::cout << "Ingrese la cantidad de palabras para la ruleta (minimo 5): ";
                std::cin >> cantidad; 
                if(cantidad<5){
                    std::cout<<"Se debe Ingresar 5 o mas "<<std::endl;
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
            std::cout<<"sigue asi vamos guerrero"<<std::endl;
            break;
        
        default:
            break;
        }

    }while(opcion!=4);

}
//2
void menu_gestion_opciones_juego(pturno&turno,palabra_rul palabra,tcad&palabraGuiones,bool&palabraResuelta) {
    int opcion,opcion2;
    tcad palabraArriesgada;
    bool continuar = true;
    do{
        std::cin >> opcion;
        switch (opcion) {
            case 1:
                probarLetraPalabra(palabra.palabra, palabraGuiones);
                if(strcmp(palabra.palabra,palabraGuiones) == 0)
                    {
                        turno->cantidad_vidas+=3;
                        std::cout << "========================" << std::endl; 
                        std::cout << "<3 FELICIDADES!!! <3 " << std::endl; 
                        std::cout << "Has acertado la palabra." << std::endl; 
                        std::cout << "========================" << std::endl;
                        palabraResuelta = true; 
                        push_pila_palabras(turno->palabras_acertadas,palabra.palabra);
                    }
                turno->cantidad_vidas -= 1;
                continuar=false;
                break;
            case 2:
                turno->cantidad_vidas -= 1;
                cambiarPrimeraLetra(palabra.palabra,palabraGuiones);
                continuar=false;
                break;
            case 3:     // Pistas sinonimos o definicion
            {   continuar=true;
                std::cout<<"1 Definicion (-2 vidas) "<<std::endl;
                std::cout<<"2 Sinonimo (-3 vidas) "<<std::endl;
                std::cout<<"Elija opcion:  "<<std::endl;
                std::cin>>opcion2;
                system("cls");
                if(opcion2 == 1)
                {  if((turno->cantidad_vidas-2) > 0 )
                    {   
                        turno->cantidad_vidas -= 2;
                        std::cout<<palabra.definicion<<std::endl;
                        continuar=false;
                    }
                    else
                        std::cout<<"Vidas insuficientes"<<std::endl;
                }
                else
                {   if(strlen(palabra.sinonimos)>0)
                    {
                        if((turno->cantidad_vidas-3) > 0 )
                        {   continuar=false;
                            turno->cantidad_vidas -= 3;
                            std::cout<<palabra.sinonimos<<std::endl;
                        }
                        else
                            std::cout<<"Vidas insuficientes"<<std::endl;
                            
                    }else
                        std::cout<<"No hay sinonimos registrados"<<std::endl;
                        
                }
                system("pause");
            }
            break;

            case 4: //Arriesgar palabra
                    continuar=false;
                    turno->cantidad_vidas -= 1;
                    std::cout<< "Ingrese palabra"<<std::endl;
                    std::cin>>palabraArriesgada;
                    if(strcmp(palabra.palabra,palabraArriesgada) == 0)
                    {
                        turno->cantidad_vidas+=3;
                        std::cout << "========================" << std::endl; 
                        std::cout << "<3 FELICIDADES!!! <3 " << std::endl; 
                        std::cout << "Has acertado la palabra." << std::endl; 
                        std::cout << "========================" << std::endl;
                        palabraResuelta = true;   
                        push_pila_palabras(turno->palabras_acertadas,palabra.palabra);
                    }
                    else
                    {
                        std::cout << "========================" << std::endl; 
                        std::cout << " </3 FALLASTE! </3 " << std::endl; 
                        std::cout << "La palabra no es correcta." << std::endl; 
                        std::cout << "========================" << std::endl;
                    }
                    system("pause");
                break;

            default:
                std::cout<<"Opcion invalida"<<std::endl;
                break;
        }
    }
    while(continuar == true);
}

// 2
void menu_juego_encurso(tcad&palabraGuiones, pturno&turno)
{
    std::cout << "=====================================" << std::endl;
    std::cout << " Palabra : " <<palabraGuiones<<std::endl;
    std::cout << "=====================================" << std::endl;

    std::cout << "Turno del jugador: " <<turno->nickname<<" Vidas restantes: "<< turno->cantidad_vidas<< std::endl;
    std::cout << "1. Probar una letra (-1 vida)" << std::endl;
    std::cout << "2. Solicitar primera letra (-1 vida)" << std::endl;
    std::cout << "3. Solicitar una pista" << std::endl;
    std::cout << "4. Arriesgar la palabra (-1 vida)" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Elija una opcion: ";

}



//1
void menu_jugar() {
    std::cout << "=====================================" << std::endl;
    std::cout << "                 JUGAR               " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "1. Seleccionar jugadores" << std::endl;
    std::cout << "2. Iniciar juego" << std::endl;
    std::cout << "3. Volver al menu anterior" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Elija una opcion: ";
}

void menu_principal_gestion_jugar() { 
    tcad archivo1 = "jugadores.dat", nickname, nombre, apellido,palabraGuiones;
    inicializar_turnos(turnos);
    pturno turno;
    int opcion;
    bool palabraResuelta,todasLasPalabrasJugadas=false;
    
    do {
        system("cls");
        menu_jugar();
        std::cin >> opcion;
        switch (opcion) {
            case 1: // Seleccionar jugadores
            {
                listar_jugadores(archivo1, true);
                std::cout << "\n |     Ingrese nickname de jugador a elegir     |" << std::endl;
                std::cin >> nickname;

                obtener_nombre_apellido(archivo1, nickname, nombre, apellido);
                std::cout << "Nombre: " << nombre << " , Apellido: " << apellido << std::endl;
                crear_turno(turno, nickname);

                if (buscar_jugador_repetido(turnos, nickname)) { // Validacion para que no se repitan los jugadores en la cola
                    std::cout << "Jugador ya seleccionado" << std::endl;
                } else {
                    cola_agregar_turno(turnos, turno);
                    std::cout << "========================" << std::endl;
                    std::cout << "| " << turnos.fin->nickname << " agregado con exito!" << std::endl;
                    std::cout << "========================" << std::endl;
                }
                system("pause");
                break;
            }    
            case 2:
            {
                pruleta palabraEnJuego=NULL;
                if (ruleta_creada) 
                {
                    if (turnos.cantidad >= 2)
                    {
                        for (palabraEnJuego = ruleta_palabras.inicio; palabraEnJuego != NULL && turnos.cantidad >1; palabraEnJuego = palabraEnJuego->sig)
                        {
                            system("cls");
                            palabraResuelta = false;
                            convertirPalabraAGuiones(palabraEnJuego->dato.palabra, palabraGuiones);
                            do
                            { // Recorre los turnos de los jugadores
                                turno = cola_quitar_turno(turnos);
                                menu_juego_encurso(palabraGuiones, turno);
                                menu_gestion_opciones_juego(turno, palabraEnJuego->dato, palabraGuiones,palabraResuelta);
                                if (turno->cantidad_vidas > 0) {
                                    cola_agregar_turno(turnos, turno);
                                }else
                                {   
                                    //Animacion
                                    std::cout<<" Jugador "<< turno->nickname<<" fue alcanzado por la parca"<<std::endl;
                                }
                                system("cls");
                            } while (turnos.cantidad >1 && palabraResuelta == false);
                        }

                        std::cout << "Calculando puntaje final..." << std::endl;
                        system("pause");
                        system("cls");
                        
                        if(palabraEnJuego == NULL)
                            todasLasPalabrasJugadas = true;
                        
                        pturno turnoGanador = jugador_con_mas_palabras_o_puntaje(turnos);
                        
                        int puntaje_total = calcular_puntaje_individual(turnoGanador->palabras_acertadas,todasLasPalabrasJugadas);
                        
                        modificar_ganador(archivo1, turnoGanador->nickname , puntaje_total);
                        
                         //setear la ruleta de palabras en nulo 
                        
                        std::cout << "==============================" << std::endl;
                        std::cout << "     FELICIDADES, " << turnoGanador->nickname << "!" << std::endl;
                        std::cout << "==============================" << std::endl;
                        std::cout << "     Has ganado el juego!      " << std::endl;
                        std::cout << "==============================" << std::endl;
                        std::cout << "     Puntaje: " << puntaje_total << " puntos" << std::endl;
                        std::cout << "==============================" << std::endl;

                        //Setear estos valores a 0
                        inicializar_ruleta_palabras(ruleta_palabras);
                        inicializar_turnos(turnos);

                        system("pause");

                    } else {
                        std::cout << "**********************Estimado seleccione al menos 2 jugadores*********************" << std::endl;
                        system("pause");
                    }

                } else {
                    std::cout << "**********************Estimado debe generar la ruleta*********************" << std::endl;
                    system("pause");
                }
                break;
            }
            case 3:
            {
                std::cout << "BYE GUERREROS" << std::endl;
                system("pause");
                return;
            }
            default:{
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                system("pause");
                break;
            }
                
        }
    } while (opcion != 3);
}

void menu() {
    tcad archivo = "jugadores.dat"; 
    int opcion;    
    do {
        system("cls");
        opciones();
        std::cin >> opcion;
        switch (opcion) {
            case 1:
                menu_principal_gestion_jugador();
                break;
            case 2:
                menu_principal_ruleta_palabras();
                break;
            case 3: // Jugar
                if (contar_jugadores_desde_archivo(archivo) == 0) {
                    std::cout << "No hay jugadores registrados." << std::endl;
                } else {
                    if (contar_jugadores_desde_archivo(archivo) < 2) {
                        std::cout << "Necesita al menos 2 jugadores para iniciar el juego." << std::endl;
                    } else {   
                        menu_principal_gestion_jugar();
                    }
                }
                system("pause");
                break;
            case 4:
                {   
                    tcad resp;
                    
                    listar_jugadores_cuadro_honor(archivo, true);
                    system("pause");
                }
                break;
            case 5:
                std::cout << "Bye valiente jugador." << std::endl;
                system("pause");
                break;
        
            default:
                std::cout << "Opcion no válida. Intente de nuevo." << std::endl;
                system("pause");
                break;
        }

    } while (opcion != 5);
}
