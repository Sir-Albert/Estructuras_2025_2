#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

#include "../nodos/nodo.h"
#include "../cola/cola.h"

typedef struct
{
	void **tabla;
	int tam;
	int cant;
	int (*folding)(void*);
	int (*hash)(int,int);
	int (*rehash)(int,int,int);
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
}HashTable;

HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*));
int insertarClave(HashTable *hashtable,void *dato);
Cola buscarClave(HashTable *hashtable,void *dato);
void imprimirHashTabla(HashTable *hashtable);





#endif