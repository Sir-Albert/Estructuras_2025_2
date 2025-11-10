

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/heap/heap.h"



int compararEntero(void*,void*);
void imprimirEntero(void*);
int main(void)
{
	Heap heap = inicializarHeap( &imprimirEntero,&compararEntero);
	int arr[] = {3, 5, 8, 10, 17, 11, 13, 19, 22, 24, 29};
	int cant = sizeof(arr)/sizeof(int);
	int i;
	for( i = 0 ; i < cant ; i++)
	{
		insertarHeap(&heap,&arr[i]);
	}
	
	//CAMBIAR A HEAP MINIMO
	heap.tipo = MIN;
	heapify(&heap);
	printf("\n");
	imprimirHeap(heap);	
	printf("\n");
	imprimirArbol(heap.arbol);
	//CAMBIAR A HEAP MAXIMO
	heap.tipo = MAX;
	heapify(&heap);
	printf("\n");
	imprimirHeap(heap);
	printf("\n");
	imprimirArbol(heap.arbol);
	
	printf("\n");
	while( heap.cantidad )
	{
		void *x = quitarHeap(&heap);
		imprimirEntero(x);
	}
	
	printf("\n\n\n");
	
	
	
	return 0;
}

void cambiarPrioridad(Heap *heap)
{	
	heap->tipo = (heap->tipo == MIN) ? MAX:MIN;
	heapify(heap);
}



void imprimirEntero(void *a)
{
	int *aa=a;
	printf(" %d",*aa);
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}
