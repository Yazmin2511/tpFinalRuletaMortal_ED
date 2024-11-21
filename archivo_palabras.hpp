#include <iostream>
#include <cstring> // Para strcpy y strcmp
#include <cstdio>
#include "abb_palabras.hpp" // Aquí están las funciones del ABB que definiste

// Función recursiva auxiliar para guardar en orden
void guardar_inorden(ppalabra arbol, FILE *file) {
    if (arbol != NULL) {
        guardar_inorden(arbol->izq, file);
        fwrite(&(arbol->pal), sizeof(palabra), 1, file);
        guardar_inorden(arbol->der, file);
    }
}

// Función para cargar palabras desde el archivo binario al ABB
void cargar_palabras_desde_archivo(tcad archivo, ppalabra& arbol) {
    FILE *file = fopen(archivo, "rb");
    if (file == NULL) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }

    palabra temp_palabra;
    while (fread(&temp_palabra, sizeof(palabra), 1, file)) {
        ppalabra nuevo;
        nuevo = new tpalabra;
        if (nuevo == NULL) {
            std::cout << "Memoria llena\n";
            fclose(file);
            return;
        }
        strcpy(nuevo->pal.palabra, temp_palabra.palabra);
        strcpy(nuevo->pal.definicion, temp_palabra.definicion);
        for (int i = 0; i < temp_palabra.cant_sinonimo; ++i) {
            strcpy(nuevo->pal.sinonimos[i], temp_palabra.sinonimos[i]);
        }
        nuevo->pal.cant_sinonimo = temp_palabra.cant_sinonimo;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        agregar_palabra(arbol, nuevo);
    }

    fclose(file);
}

// Función para guardar las palabras del ABB en un archivo binario (sobreescribe el archivo)
void guardar_palabras_en_archivo(tcad archivo, ppalabra arbol) {
    FILE *file = fopen(archivo, "wb");
    if (file == NULL) {
        std::cout << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    guardar_inorden(arbol, file);
    fclose(file);
}

// Función para registrar una palabra
void registrar_palabra(tcad archivo, ppalabra& arbol) {
    cargar_palabras_desde_archivo(archivo, arbol); // Cargar palabras desde el archivo al ABB

    ppalabra nuevo;
    crear_nodo_palabras(nuevo, arbol); // Crear un nuevo nodo con los datos de la palabra

    agregar_palabra(arbol, nuevo); // Insertar el nodo en el ABB
    guardar_palabras_en_archivo(archivo, arbol); // Guardar el ABB en el archivo binario
    std::cout << "Palabra registrada correctamente.\n";
}

// Función para listar palabras
// void listar_palabras(tcad archivo, bool ascendente) {
//     ppalabra arbol = NULL;
//     cargar_palabras_desde_archivo(archivo, arbol);

//     if (arbol == NULL) {
//         std::cout << "No hay palabras registradas.\n";
//         return;
//     }

//     std::cout << "Listado de palabras:\n";
//     listar_palabrass(arbol); // Llama a tu función para mostrar las palabras en orden ascendente o descendente
// }

