#include <iostream>
#include <cstring> // Para strcpy y strcmp
#include <cstdio>
#include "abb_jugadores.hpp" // Aquí están las funciones del ABB que definiste

// Función recursiva auxiliar para guardar en orden
void guardar_inorden(pnodo arbol, FILE *file) {
    if (arbol != NULL) {
        guardar_inorden(arbol->izq, file);
        fwrite(&(arbol->jugador), sizeof(tjugador), 1, file);
        guardar_inorden(arbol->der, file);
    }
}

// Función para cargar jugadores desde el archivo binario al ABB
void cargar_jugadores_desde_archivo(tcad archivo, pnodo& arbol) {
    FILE *file = fopen(archivo, "rb");
    if (file == NULL) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }

    tjugador temp_jugador;
    while (fread(&temp_jugador, sizeof(tjugador), 1, file)) {
        pnodo nuevo;
        crear_nodo_temp(nuevo, temp_jugador.nombre, temp_jugador.apellido, temp_jugador.nickname);
        nuevo->jugador.mejor_puntaje = temp_jugador.mejor_puntaje;
        nuevo->jugador.puntaje_total = temp_jugador.puntaje_total;
        nuevo->jugador.cantidad_partidas_ganadas = temp_jugador.cantidad_partidas_ganadas;
        insertar(arbol, nuevo);
    }
    
    fclose(file);
}

// Función para guardar los jugadores del ABB en un archivo binario (sobreescribe el archivo)
void guardar_jugadores_en_archivo(tcad archivo, pnodo arbol) {
    FILE *file = fopen(archivo, "wb");
    if (file == NULL) {
        std::cout << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    guardar_inorden(arbol, file);
    fclose(file);
}

// Función para agregar un jugador
void agregar_jugador(tcad archivo, pnodo& arbol) {
    cargar_jugadores_desde_archivo(archivo, arbol); // Cargar jugadores desde el archivo al ABB

    pnodo nuevo;
    crear_nodo(nuevo, arbol); // Crear un nuevo nodo con los datos del jugador

    insertar(arbol, nuevo); // Insertar el nodo en el ABB
    guardar_jugadores_en_archivo(archivo, arbol); // Guardar el ABB en el archivo binario
    std::cout << "Jugador agregado correctamente.\n";
}

// Función para listar jugadores
void listar_jugadores(tcad archivo, bool ascendente) {
    pnodo arbol = NULL;
    cargar_jugadores_desde_archivo(archivo, arbol);

    if (arbol == NULL) {
        std::cout << "No hay jugadores registrados.\n";
        return;
    }

    std::cout << "Listado de jugadores:\n";
    mostrar_orden(arbol, ascendente); // Mostrar jugadores en orden ascendente o descendente
}

// Función para buscar un jugador por nickname y mostrarlo
void buscar_jugador(tcad archivo, tcad nickname) {
    pnodo arbol = NULL;
    cargar_jugadores_desde_archivo(archivo, arbol);

    pnodo encontrado = busqueda_datos(arbol, nickname);
    if (encontrado != NULL) {
        mostrar_jugador(encontrado);
    } else {
        std::cout << "Jugador con nickname \"" << nickname << "\" no encontrado.\n";
    }
}

// Función para modificar los datos de un jugador (excepto nickname, puntajes y partidas ganadas)
void modificar_jugador_archivo(tcad archivo, tcad nickname) {
    pnodo arbol = NULL;
    cargar_jugadores_desde_archivo(archivo, arbol);

    pnodo encontrado = busqueda_datos(arbol, nickname);
    if (encontrado == NULL) {
        std::cout << "Jugador con nickname \"" << nickname << "\" no encontrado.\n";
        return;
    }

    modificar_jugador(arbol, nickname); // Modificar los datos del jugador
    guardar_jugadores_en_archivo(archivo, arbol); // Guardar los cambios en el archivo binario
}

// Función para eliminar un jugador
void eliminar_jugador(tcad archivo, tcad nickname) {
    pnodo arbol = NULL;
    cargar_jugadores_desde_archivo(archivo, arbol);

    pnodo padre = NULL;
    pnodo eliminado = eliminar_nodo(arbol, nickname, padre); // Implementa la función `eliminar_nodo` en tu ABB
    if (eliminado == NULL) {
        std::cout << "Jugador con nickname \"" << nickname << "\" no encontrado.\n";
    } else {
        std::cout << "Jugador eliminado correctamente.\n";
        delete eliminado; // Liberar la memoria del nodo eliminado
    }

    guardar_jugadores_en_archivo(archivo, arbol); // Guardar el ABB actualizado en el archivo
}
