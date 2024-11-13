#include <iostream>
#include <stdlib.h>

using namespace std;

main()
{


}


void opciones()
{   
        cout<<"Gestión de jugadores";
        cout<<"Crear ruleta de palabras";
        cout<<"Crear ruleta de palabras";
        cout<<"Jugar";
        cout<<"Cuadro de honor";
        cout<<"Salir";
        cout<<"Elija una opcion";
        
}

void menu()
{
    int opcion = -1;
    do{
        opciones();
        cin>>opcion;
    }while(opcion!=5);

}