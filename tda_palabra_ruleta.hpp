#include <iostream>
#include <cstdlib> // Para rand y srand
#include <ctime> // Para time
#include <cstring> // Para strcpy y strcmp
#include <cstdio> // Para fopen, fread y fclose
#include <cctype>

#include "t_cad.hpp"

typedef struct tpalabra_ruleta *ppalabra_ruleta;
typedef struct palabra_rul{
    tcad palabra;
    tcad definicion;
    tcad sinonimos; 
}; 

typedef struct tpalabra_ruleta{ 
    palabra_rul pal; 
    ppalabra_ruleta izq; 
    ppalabra_ruleta der; 
};

// TDA DE listaRuletaS DOBLES
typedef struct truleta *pruleta;
struct truleta {
    palabra_rul dato;
    pruleta ant; 
    pruleta sig; 
};

struct listaRuleta {
    pruleta inicio;
    pruleta fin;
};


void convertirPalabraAGuiones(tcad palabra, tcad&resultado)
{ 
    int longitud = strlen(palabra); 
    for (int i = 0; i < longitud; i++) {
         resultado[i] = '_'; 
    } 
    resultado[longitud] = '\0';
}


void cambiarPrimeraLetra(tcad palabra,tcad&palabraGuiones)
{ 
    palabraGuiones[0] = palabra[0];
}


void probarLetraPalabra(tcad palabra, tcad& palabraGuiones) {
    char letra;
    bool letraEncontrada = false;
    std::cout << "Ingrese una letra: ";
    std::cin >> letra;
    letra = tolower(letra); 

    for (int i = 0; i < strlen(palabra); i++) {
        if (tolower(palabra[i]) == letra) { 
            palabraGuiones[i] = palabra[i];
            letraEncontrada = true;
        }
    }
    
    if (!letraEncontrada) {
        std::cout << "La letra '" << letra << "' no está en la palabra." << std::endl;
    }
}


void inicializar_ruleta_palabras(listaRuleta &lis)
{
    lis.inicio = NULL;
    lis.fin = NULL;
}

void crear_ruleta_palabra(pruleta &nuevo, tcad palabra, tcad definicion,tcad sinonimos)
{
    nuevo = new truleta;
    if (nuevo != NULL)
    {
        strcpy(nuevo->dato.palabra, palabra);
        strcpy(nuevo->dato.definicion, definicion);
        strcpy(nuevo->dato.sinonimos, sinonimos);
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

pruleta extraer_final_ruleta_palabra(listaRuleta &lista){
    pruleta extraer;
    if(lista.fin==NULL){
        extraer=NULL;
    }else{
        if(lista.inicio==lista.fin){
            extraer=lista.inicio;
            lista.fin=NULL;
            lista.inicio=NULL;
        }else{
            extraer=lista.fin;
            lista.fin=lista.fin->ant;
            lista.fin->sig=NULL;
            extraer->ant=NULL;
        }
    }
    return extraer;
}

void mostrar_ruleta_palabra(listaRuleta lis)
{
    pruleta i;
    if (lis.inicio != NULL)
    {
        for (i = lis.inicio; i != NULL; i = i->sig)
            std::cout << i->dato.palabra << ", ";
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
    FILE *file = fopen(archivo, "rb");
    if (file == NULL) {
        std::cout << "El archivo no existe o no pudo abrirse.\n";
        return;
    }

    // Contar total de palabras en el archivo
    int total_palabras = contar_palabras(file);
    if (total_palabras < cantidad_palabras) {
        std::cout << "No hay suficientes palabras en el archivo. Se encontraron " << total_palabras << " palabras.\n";
        fclose(file);
        return;
    }

    // Seleccionar aleatoriamente las palabras sin repetición
    int indices[cantidad_palabras];
    seleccionar_palabras_aleatorias(indices, cantidad_palabras, total_palabras); 

    // Leer y agregar las palabras seleccionadas a la lista doble
    palabra_rul temp_palabra;
    for (int i = 0; i < cantidad_palabras; i++) {
        fseek(file, indices[i] * sizeof(palabra_rul), SEEK_SET); // Moverse a la posición correcta
        fread(&temp_palabra, sizeof(palabra_rul), 1, file);
        pruleta nuevo;
        crear_ruleta_palabra(nuevo, temp_palabra.palabra,temp_palabra.definicion,temp_palabra.sinonimos);
        agregar_final_ruleta_palabra(lis, nuevo);
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





