#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct
{
	void **tabla;
	int tam;
	int cant;
	int (*folding)(void*);
	int (*hash)(int);
	int (*rehash)(int,int);
	int (*imprimir)(void*);
	int (*comparar)(void*);
}HashTable;

HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*));
void insertarClave(HashTable* hashtable,void *dato);
void* buscarClave(HashTable* hashtable,void *clave);





#endif