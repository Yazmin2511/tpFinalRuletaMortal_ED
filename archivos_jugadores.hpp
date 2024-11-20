#include <iostream>
#include <fstream>
#include <cstring> // Para strcpy y strcmp
#include "abb_jugadores.hpp" // Aquí están las funciones del ABB que definiste

// Función para cargar jugadores desde el archivo binario al ABB
void cargar_jugadores_desde_archivo(tcad archivo, pnodo& arbol) {
    std::ifstream file(archivo, std::ios::binary);
    if (!file) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }
    
    tjugador temp_jugador;
    while (file.read(reinterpret_cast<char*>(&temp_jugador), sizeof(tjugador))) {
        pnodo nuevo;
        crear_nodo_temp(nuevo, temp_jugador.nombre, temp_jugador.apellido, temp_jugador.nickname);
        nuevo->jugador.mejor_puntaje = temp_jugador.mejor_puntaje;
        nuevo->jugador.puntaje_total = temp_jugador.puntaje_total;
        nuevo->jugador.cantidad_partidas_ganadas = temp_jugador.cantidad_partidas_ganadas;
        insertar(arbol, nuevo);
    }
    
    file.close();
}

// Función para guardar los jugadores del ABB en un archivo binario (sobreescribe el archivo)
void guardar_jugadores_en_archivo(tcad archivo, pnodo arbol) {
    std::ofstream file(archivo, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cout << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    // Función recursiva auxiliar para guardar en orden
    auto guardar_inorden = [](pnodo arbol, std::ofstream& file, auto& guardar_inorden_ref) -> void {
        if (arbol) {
            guardar_inorden_ref(arbol->izq, file, guardar_inorden_ref);
            file.write(reinterpret_cast<const char*>(&arbol->jugador), sizeof(tjugador));
            guardar_inorden_ref(arbol->der, file, guardar_inorden_ref);
        }
    };

    guardar_inorden(arbol, file, guardar_inorden);
    file.close();
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

    if (!arbol) {
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
    if (encontrado) {
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
    if (!encontrado) {
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
    if (!eliminado) {
        std::cout << "Jugador con nickname \"" << nickname << "\" no encontrado.\n";
    } else {
        std::cout << "Jugador eliminado correctamente.\n";
        delete eliminado; // Liberar la memoria del nodo eliminado
    }

    guardar_jugadores_en_archivo(archivo, arbol); // Guardar el ABB actualizado en el archivo
}
