#include <iostream>
using namespace std;
void opciones() {
    
    cout << "=====================================" << endl;
    cout << "     \U0001F600  ¡BIENVENIDO AL JUEGO! \U0001F600       " << endl;
    cout << "=====================================" << endl;

    cout << "1. Gestion de jugadores" << endl;
    cout << "2. Crear ruleta de palabras" << endl;
    cout << "3. Jugar" << endl;
    cout << "4. Cuadro de honor" << endl;
    cout << "5. Salir" << endl;
    cout << "=====================================" << endl;
    cout << "Elija una opcion: ";
}


void menu()
{
    int opcion = -1;
    do{
        opciones();
        cin>>opcion;
    }while(opcion!=5);

}