#include <iostream>
#include <cstdlib> // Para rand y srand
#include <ctime> // Para time
#include <cstring> // Para strcpy y strcmp
#include <cstdio> // Para fopen, fread y fclose

#include "t_cad.hpp"

typedef tcad tsinonimo_ruleta[3]; 
typedef struct tpalabra_ruleta *ppalabra_ruleta;
typedef struct palabra_rul{
    tcad palabra;
    tcad definicion;
    tsinonimo_ruleta sinonimos; // Sinonimos puede ser NULL 
    int cant_sinonimo;
}; 
typedef struct tpalabra_ruleta{ 
    palabra_rul pal; 
    ppalabra_ruleta izq; 
    ppalabra_ruleta der; 
};

// TDA DE listaRuletaS DOBLES
typedef struct truleta *pruleta;
struct truleta {
    tcad dato;
    pruleta ant; 
    pruleta sig; 
};

struct listaRuleta {
    pruleta inicio;
    pruleta fin;
};

void inicializar_ruleta_palabras(listaRuleta &lis)
{
    lis.inicio = NULL;
    lis.fin = NULL;
}

void crear_ruleta_palabra(pruleta &nuevo, tcad valor)
{
    nuevo = new truleta;
    if (nuevo != NULL)
    {
        strcpy(nuevo->dato, valor);
        nuevo->sig = NULL;
        nuevo->ant = NULL;
    }
    else
    {
        std::cout << "MEMORIA INSUFICIENTE" << std::endl;
    }
}

void agregar_final_ruleta_palabra(listaRuleta &lis, pruleta nuevo)
{
    if (lis.inicio == NULL) // vacia
    {
        lis.inicio = nuevo;
        lis.fin = nuevo;
    }
    else
    {
        nuevo->ant = lis.fin;
        lis.fin->sig = nuevo;
        lis.fin = nuevo;
    }
}

void mostrar_ruleta_palabra(listaRuleta lis)
{
    pruleta i;
    if (lis.inicio != NULL)
    {
        for (i = lis.inicio; i != NULL; i = i->sig)
            std::cout << i->dato << ", ";
        std::cout << std::endl;
    }
    else
        std::cout << "Lista VACIA" << std::endl;
}

// Función para contar total de palabras en el archivo
int contar_palabras(FILE *file) {
    palabra_rul temp_palabra;
    int total_palabras = 0;
    while (fread(&temp_palabra, sizeof(palabra_rul), 1, file)) {
        total_palabras++;
    }
    rewind(file); // Volver al inicio del archivo
    return total_palabras;
}

// Función para verificar si un índice ya fue seleccionado
bool indice_seleccionado(int indices[], int cantidad_seleccionada, int indice_actual) {
    for (int i = 0; i < cantidad_seleccionada; i++) {
        if (indices[i] == indice_actual) {
            return true;
        }
    }
    return false;
}

// Función para seleccionar palabras aleatorias sin repetición
void seleccionar_palabras_aleatorias(int indices[], int cantidad_palabras, int total_palabras) {
    int seleccionadas = 0;
    srand(time(NULL));
    while (seleccionadas < cantidad_palabras) {
        int aleatorio = rand() % total_palabras;
        if (!indice_seleccionado(indices, seleccionadas, aleatorio)) {
            indices[seleccionadas] = aleatorio;
            seleccionadas++;
        }
    }
}

// Función para cargar una ruleta de palabras desde el archivo binario
void generar_ruleta(tcad archivo, listaRuleta &lis, int cantidad_palabras) {
    if (cantidad_palabras < 5) {
        std::cout << "La cantidad mínima de palabras es 5." << std::endl;
        return;
    }
    FILE *file = fopen(archivo, "rb");
    if (file == NULL) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }

    // Contar el total de palabras en el archivo
    int total_palabras = contar_palabras(file);

    if (total_palabras < cantidad_palabras) {
        std::cout << "No hay suficientes palabras en el archivo.\n";
        fclose(file);
        return;
    }

    // Seleccionar aleatoriamente las palabras sin repetición
    int indices[cantidad_palabras];
    seleccionar_palabras_aleatorias(indices, cantidad_palabras, total_palabras);

    // Leer y agregar las palabras seleccionadas a la lista doble
    int contador = 0;
    int seleccionada = 0;
    palabra_rul temp_palabra;
    while (fread(&temp_palabra, sizeof(palabra_rul), 1, file) && seleccionada < cantidad_palabras) {
        if (contador == indices[seleccionada]) {
            pruleta nuevo;
            crear_ruleta_palabra(nuevo, temp_palabra.palabra);
            agregar_final_ruleta_palabra(lis, nuevo);
            seleccionada++;
        }
        contador++;
    }

    fclose(file);

    // Verificar que se han agregado exactamente la cantidad de palabras solicitadas
    pruleta temp = lis.inicio;
    int contador_lista = 0;
    while (temp != NULL) {
        contador_lista++;
        temp = temp->sig;
    }
    if (contador_lista != cantidad_palabras) {
        std::cout << "Error: No se agregaron exactamente " << cantidad_palabras << " palabras.\n";
    }
}
