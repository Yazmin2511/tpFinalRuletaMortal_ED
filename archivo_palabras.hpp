#include <iostream>
#include <cstring>
#include <cstdio>
#include "abb_palabras.hpp"

void guardar_inorden(ppalabra arbol, FILE *file) {
    if (arbol != NULL) {
        guardar_inorden(arbol->izq, file);
        fwrite(&(arbol->pal), sizeof(palabra), 1, file);
        guardar_inorden(arbol->der, file);
    }
}

void cargar_palabras_desde_archivo(tcad archivo, ppalabra &arbol) {
    FILE *file = fopen(archivo, "rb");
    if (file == NULL) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }

    palabra temp_palabra;
    while (fread(&temp_palabra, sizeof(palabra), 1, file)) {
        ppalabra nuevo = new tpalabra;
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

void guardar_palabras_en_archivo(tcad archivo, ppalabra arbol) {
    FILE *file = fopen(archivo, "wb");
    if (file == NULL) {
        std::cout << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    guardar_inorden(arbol, file);
    fclose(file);
}

void registrar_palabra(tcad archivo, ppalabra &arbol) {
    FILE *file_check = fopen(archivo, "rb");
    if (file_check != NULL) {
        fclose(file_check);
        cargar_palabras_desde_archivo(archivo, arbol);
    }

    ppalabra nuevo;
    crear_nodo_palabras(nuevo, arbol);

    agregar_palabra(arbol, nuevo);
    guardar_palabras_en_archivo(archivo, arbol);
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

