//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"
//FUNCION MAIN

#define LONGITUD 64

void imprimirCadena(void *a);
void imprimirCaracter(void *a);
void liberarCadena(void *a);

int main(void)
{
	// {INICIO NULO, SIN LIMITE, CANTIDAD 0, COMO IMPRIMIR, COMO LIBERAR}
	Pila pila = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	//Pila pilaC = {NULL,-1,0,&imprimirCaracter,NULL};
	push(&pila, cadenaDinamica("David") );
	push(&pila, cadenaDinamica("Carlo") );
	push(&pila, cadenaDinamica("J") );
	push(&pila, cadenaDinamica("Nicol") );
	push(&pila, cadenaDinamica("Abraham") );
	imprimirPila(pila);
	liberarCadena( pop(&pila) );
	liberarCadena( pop(&pila) );
	imprimirPila(pila);
	eliminarPila(&pila);
	imprimirPila(pila);	
	
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}


void imprimirCadena(void *a)
{
	char *aa = a;
	printf("%s",aa);
	
}


void imprimirCaracter(void *a)
{
	char *c = a;
	printf("%c",*c);
}

void liberarCadena(void *a)
{
	char *aa = a;
	free(aa);
}