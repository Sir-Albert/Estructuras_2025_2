#include "cola.h"
#include <stdio.h>


Cola inicializarCola(void)
{
	return (Cola) {NULL,NULL,-1,0,NULL,NULL};
}

int llenaC(Cola cola)
{
	return 0;
}

int vaciaC(Cola cola)
{	
	return 0;
}

void enqueue(Cola *cola,void *dato)
{	
	return;
}
void* peekC(Cola cola)
{	
	return NULL;
}

void* dequeue(Cola *cola)
{	
	return NULL;
}
void imprimirCola(Cola cola)
{
	return;
}

void eliminarCola(Cola *cola)
{
	return;
}

void* buscarC(Cola cola,void *dato,int (*comparar)(void*,void*))
{
	return NULL;
}