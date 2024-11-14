#include <iostream>

typedef struct tnodo *pnodo;
struct tnodo{
			int dato;
			pnodo ant; 
			pnodo sig; 
};

struct lista{
        pnodo inicio;
        pnodo fin;
};

void iniciar(lista & lis)
{
	lis.inicio=NULL;
    lis.fin=NULL;
}

void crear(pnodo &nuevo,int valor)
{
	nuevo=new tnodo;
	if (nuevo!=NULL)
	{
		nuevo->dato=valor;
		nuevo->sig=NULL;
		nuevo->ant=NULL;
	}
	else
		std::cout << "MEMORIA INSUFICIENTE" << std::endl;
	
}

void agregar_inicio(lista&lis, pnodo nuevo)
{
    if (lis.inicio==NULL) // vacia
    {
        lis.inicio= nuevo;
        lis.fin = nuevo;
    }
    else
    {
        nuevo->sig = lis.inicio;
        lis.inicio->ant = nuevo;
        lis.inicio = nuevo;
    }
}

void agregar_final(lista&lis, pnodo nuevo)
{
    if (lis.inicio==NULL) // vacia
    {
        lis.inicio= nuevo;
        lis.fin = nuevo;
    }
    else
    {
        nuevo->ant = lis.fin;
		lis.fin->sig = nuevo;
        lis.fin = nuevo;
    }
}

void agregar_orden(lista &lis,pnodo nuevo)
{ pnodo i,fin;
  if (lis.inicio==NULL) // vacia
  {
     lis.inicio= nuevo;
     lis.fin = nuevo;
  }
  else
  {	if (nuevo->dato <= lis.inicio->dato) // agregar inicio
		agregar_inicio(lis,nuevo);
	else
	{ 
		if (nuevo->dato >= lis.fin->dato) // agregar final
			agregar_final(lis,nuevo);
		else
		{	// no analiza lis.fin
			for(i=lis.inicio->sig;i->sig!=lis.fin && nuevo->dato > i->dato;i=i->sig);
			
			nuevo->sig=i;
			nuevo->ant=i->ant;
			(nuevo->sig)->ant=nuevo;
			(nuevo->ant)->sig=nuevo;
		}

	}
  }
}

pnodo quitar_inicio(lista &lis)
{ pnodo aux = NULL;
	if (lis.inicio!=NULL)
	{	aux = lis.inicio;
		if(lis.inicio == lis.fin)
		{
			lis.inicio = NULL;
			lis.fin = NULL;
		}
		else
		{
			lis.inicio = lis.inicio->sig;
			lis.inicio ->ant = NULL;
			aux->sig = NULL;
		}	
	}

	return aux;
}

pnodo quitar_final(lista &lis)
{ pnodo aux = NULL;
	if (lis.inicio!=NULL)
	{	aux = lis.fin;
		if(lis.inicio == lis.fin)
		{	
			lis.inicio = NULL;
			lis.fin = NULL;
		}
		else
		{
			lis.fin = lis.fin->ant;
			aux ->ant = NULL;
			lis.fin->sig = NULL;
		}	
	}

	return aux;
}

pnodo quitar_nodo(lista &lis,int valor)
{ pnodo i,aux=NULL;
	if (lis.inicio!=NULL)
	{ if (lis.inicio->dato==valor) // extracción del primero
		aux = quitar_inicio(lis);
	  else
	  { 
		if (lis.fin->dato==valor) // extracción ultimo
			aux = quitar_final(lis);
		else
		{
			for(i=lis.inicio->sig;i!=lis.fin && valor!=i->dato;i=i->sig);
			if(valor == i->dato)
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
{ pnodo i;
  if (lis.inicio!=NULL)
  { for(i=lis.inicio;i!=NULL;i=i->sig)
	  std::cout << i->dato << ", ";
    std::cout << std::endl;
  }
  else
	std::cout << "LISTA VACIA" << std::endl;
}

bool buscar(lista lis,int valor)
{ pnodo i=NULL;
  if (lis.inicio!=NULL)
    for(i=lis.inicio;i!=NULL && i->dato!=valor;i=i->sig);
  return i!=NULL;
}

pnodo ultimo(lista lis)
{
	if (lis.inicio==NULL) // lista vacia
		return NULL;
	else
	{ 
		return lis.fin;
	}	
}

pnodo primero(lista lis)
{
	if (lis.inicio==NULL) // lista vacia
		return NULL;
	else
	{ 
		return lis.inicio;
	}	
}

void max_min(pnodo inicio,pnodo &max,pnodo &min)
{
	if (inicio==NULL) // lista vacia
	{  max=NULL;
	   min=NULL;	
	}	
	else
	{ if (inicio->sig==NULL) // ultimo nodo
	   { max=inicio;
		 min=inicio;
	   }
	  else
	  { max_min(inicio->sig,max,min);
		if (inicio->dato > max->dato) // actualizar maximo
			max=inicio;
		if (inicio->dato < min->dato) // actualizar minimo
			min=inicio;
	  }
	}	
}
