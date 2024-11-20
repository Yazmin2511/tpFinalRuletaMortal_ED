#include <iostream>
#include <cstring> 
typedef char tcad[50];
typedef struct tnodo *pnodo;

typedef struct tpalabra{
    tcad palabra;  
    tcad definicion;
    pnodo sinonimos;  // Sinonimos puede ser NULL
};