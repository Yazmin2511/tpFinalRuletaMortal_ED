#include <cstring>
#include <iostream>

typedef char tcad[30];

tcad* obtenerTcadValido(tcad mensaje) {
    static tcad resultado; // Variable estática para devolver el valor
    do {
        std::cout << mensaje;
        std::cin.getline(resultado, 30); // Permite leer espacios
        if (strlen(resultado) == 0) {
            std::cout << "El valor no puede estar vacío. Intente nuevamente." << std::endl;
        }
    } while (strlen(resultado) == 0); // Repite hasta que el valor no esté vacío
    return &resultado;
}