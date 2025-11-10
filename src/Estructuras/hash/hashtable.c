#include "hashtable.h"


HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*));
void insertarClave(HashTable* hashtable,void *dato);
void* buscarClave(HashTable* hashtable,void *clave);
