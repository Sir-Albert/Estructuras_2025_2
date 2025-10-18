

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"
#include "../Estructuras/cola/cola.h"
#include "../Estructuras/arbol/arbol.h"
#include "../Estructuras/nodos/nodoarbol.h"

typedef struct
{
	char caracter;
	float *valor;
}Dato;


Dato* crearDato(char caracter);
void imprimirDato(void *dato);
Cola* expresionACola(char *expresion);
void capturarValores(Cola *cola);


int main(void)
{
	char *postfix = NULL;
	inputCadenaDinamica("\n Captura postfix: ",&postfix,100);	
	Cola *colaExpresion = expresionACola(postfix);
	capturarValores(colaExpresion);
	printf("\n Cola: ");	
	imprimirCola(*colaExpresion);
	printf("\n\n FIN DE PROGRAMA\n");
	return 0;
}

int esOperador(char caracter)
{
	int i;
	char *operadores = "+-*/^";
	for(i = 0; operadores[i]!='\0' ;i++)
	{
		if(caracter == operadores[i])
			return 1;
	}
	return 0;
}

void capturarValores(Cola *cola)
{
	int i;
	for( i = 0 ; i< cola->cantidad ; i++)
	{
		NodoA *nodo = peekC(*cola);
		Dato *dato = nodo->dato;
		if(dato->valor == NULL && !esOperador(dato->caracter))			
		{
			dato->valor = calloc(1,sizeof(float));
			printf("\n Captura valor de %c: ",dato->caracter);
			inputFloat("",dato->valor);
		}
		enqueue(cola,dequeue(cola));
	}
}

Dato* crearDato(char caracter)
{
	Dato *nuevo = calloc(1,sizeof(Dato));
	nuevo->caracter = caracter;
	return nuevo;
}

void imprimirDato(void *dato)
{
	NodoA *nodo = dato;
	Dato *info = nodo->dato;
	if(info->valor)
		printf(" %c = %f",info->caracter,*info->valor);
	else 
		printf(" %c ",info->caracter);
}

int compararCaracteres(void *param_a,void *param_b)
{	
	char *datoa  = param_a;
	NodoA *nodob = param_b;
	Dato *datob  = nodob->dato;
	if( *datoa == datob->caracter)
		return 0;
	return 1;
}


Cola* expresionACola(char *expresion)
{
	Cola *cola = calloc(1,sizeof(Cola));
	*cola = inicializarCola();
	cola->imprimir = &imprimirDato;
	int i;
	for( i = 0; expresion[i]!='\0' ; i++)
	{
		NodoA *nodo = buscarC(*cola,&expresion[i],&compararCaracteres);
		Dato* dato;
		if(nodo)
			dato = nodo->dato;
		else 
			dato = crearDato(expresion[i]);
		NodoA *nodoa = crearNodoA(dato);
		enqueue(cola,nodoa);
	}
	return cola;
}