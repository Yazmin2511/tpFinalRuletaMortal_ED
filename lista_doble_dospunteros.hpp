#include <iostream>
#include <cstdlib> // Para rand y srand
#include <ctime> // Para time
#include <cstring> // Para strcpy y strcmp
#include <cstdio> // Para fopen, fread y fclose
#include <algorithm> // Para std::sort
#include "abb_palabras.hpp"
#include "t_cad.hpp"


// TDA DE LISTAS DOBLES
typedef struct tnodo *pnodo;
struct tnodo {
    tcad dato;
    pnodo ant; 
    pnodo sig; 
};

struct lista {
    pnodo inicio;
    pnodo fin;
};

void iniciar(lista & lis)
{
    lis.inicio = NULL;
    lis.fin = NULL;
}

void crear(pnodo &nuevo, tcad valor)
{
    nuevo = new tnodo;
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

void agregar_inicio(lista &lis, pnodo nuevo)
{
    if (lis.inicio == NULL) // vacia
    {
        lis.inicio = nuevo;
        lis.fin = nuevo;
    }
    else
    {
        nuevo->sig = lis.inicio;
        lis.inicio->ant = nuevo;
        lis.inicio = nuevo;
    }
}

void agregar_final(lista &lis, pnodo nuevo)
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

void agregar_orden(lista &lis, pnodo nuevo)
{
    pnodo i;
    if (lis.inicio == NULL) // vacia
    {
        lis.inicio = nuevo;
        lis.fin = nuevo;
    }
    else
    {
        if (strcmp(nuevo->dato, lis.inicio->dato) <= 0) // agregar inicio
            agregar_inicio(lis, nuevo);
        else
        { 
            if (strcmp(nuevo->dato, lis.fin->dato) >= 0) // agregar final
                agregar_final(lis, nuevo);
            else
            { // no analiza lis.fin
                for (i = lis.inicio->sig; i->sig != lis.fin && strcmp(nuevo->dato, i->dato) > 0; i = i->sig);
                
                nuevo->sig = i;
                nuevo->ant = i->ant;
                (nuevo->sig)->ant = nuevo;
                (nuevo->ant)->sig = nuevo;
            }
        }
    }
}

pnodo quitar_inicio(lista &lis)
{ 
    pnodo aux = NULL;
    if (lis.inicio != NULL)
    {
        aux = lis.inicio;
        if (lis.inicio == lis.fin)
        {
            lis.inicio = NULL;
            lis.fin = NULL;
        }
        else
        {
            lis.inicio = lis.inicio->sig;
            lis.inicio->ant = NULL;
            aux->sig = NULL;
        }   
    }
    return aux;
}

pnodo quitar_final(lista &lis)
{ 
    pnodo aux = NULL;
    if (lis.inicio != NULL)
    {
        aux = lis.fin;
        if (lis.inicio == lis.fin)
        {   
            lis.inicio = NULL;
            lis.fin = NULL;
        }
        else
        {
            lis.fin = lis.fin->ant;
            aux->ant = NULL;
            lis.fin->sig = NULL;
        }   
    }
    return aux;
}

pnodo quitar_nodo(lista &lis, tcad valor)
{ 
    pnodo i, aux = NULL;
    if (lis.inicio != NULL)
    {
        if (strcmp(lis.inicio->dato, valor) == 0) // extracción del primero
            aux = quitar_inicio(lis);
        else
        { 
            if (strcmp(lis.fin->dato, valor) == 0) // extracción último
                aux = quitar_final(lis);
            else
            {
                for (i = lis.inicio->sig; i != lis.fin && strcmp(valor, i->dato) != 0; i = i->sig);
                if (strcmp(valor, i->dato) == 0)
                {
                    aux = i;
                    (i->ant)->sig = i->sig;
                    (i->sig)->ant = i->ant;
                    aux->sig = NULL;
                    aux->ant = NULL;
                }   
            }
        }
    }
    return aux;
}

void mostrar(lista lis)
{
    pnodo i;
    if (lis.inicio != NULL)
    {
        for (i = lis.inicio; i != NULL; i = i->sig)
            std::cout << i->dato << ", ";
        std::cout << std::endl;
    }
    else
        std::cout << "LISTA VACIA" << std::endl;
}

bool buscar(lista lis, tcad valor)
{
    pnodo i = NULL;
    if (lis.inicio != NULL)
    {
        for (i = lis.inicio; i != NULL && strcmp(i->dato, valor) != 0; i = i->sig);
    }
    return i != NULL;
}

// Función personalizada para comparar enteros
bool comparacion(int a, int b) {
    return a < b;
}

// Función para cargar una ruleta de palabras desde el archivo binario
void generar_ruleta(tcad archivo, lista &lis, int cantidad_palabras) {
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
    int total_palabras = 0;
    palabra temp_palabra;
    while (fread(&temp_palabra, sizeof(palabra), 1, file)) {
        total_palabras++;
    }
    if (total_palabras < cantidad_palabras) {
        std::cout << "No hay suficientes palabras en el archivo.\n";
        fclose(file);
        return;
    }
    // Seleccionar aleatoriamente las palabras
    srand(time(NULL));
    int indices[cantidad_palabras];
    for (int i = 0; i < cantidad_palabras; ++i) {
        indices[i] = rand() % total_palabras;
    }
    // Ordenar los índices para facilitar la lectura secuencial del archivo
    std::sort(indices, indices + cantidad_palabras, comparacion);
    // Leer y agregar las palabras seleccionadas a la lista doble
    rewind(file);
    int indice_actual = 0;
    int indice_seleccionado = indices[indice_actual];
    int contador = 0;
    while (fread(&temp_palabra, sizeof(palabra), 1, file)) {
        if (contador == indice_seleccionado) {
            pnodo nuevo;
            crear(nuevo, temp_palabra.palabra); // Usamos temp_palabra.palabra
            agregar_final(lis, nuevo);
            indice_actual++;
            if (indice_actual >= cantidad_palabras) {
                break;
            }
            indice_seleccionado = indices[indice_actual];
        }
        contador++;
    }
    fclose(file);
}

