#include "hashtable.h"

int validarHashTable(HashTable *hashtable)
{
	if(!hashtable->tabla)
	{
		printf("\n No se ha reservado espacio");
		return 0;
	}
	if(!hashtable->folding || !hashtable->hash || !hashtable->rehash)
	{
		printf("\n No se ha asignado alguna de estas funciones: folding,hash,rehash");
		return 0;		
	}
	if(!hashtable->comparar || !hashtable->imprimir)
	{
		printf("\n No se ha asignado alguna de estas funciones: comparar,imprimir");
		return 0;		
	}
	return 1;	
}


HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
	HashTable hashtable = (HashTable) {NULL,tam,0,NULL,NULL,NULL,imprimir,comparar};
	while(!hashtable.tabla)
		hashtable.tabla = (void**) calloc(tam,sizeof(void*));
	return hashtable;	
}

int insertarClave(HashTable* hashtable,void *dato)
{
	if(!validarHashTable(hashtable))
		return 0;
	int clave,indice,nuevo_indice,k;
	clave = hashtable->folding(dato);
	indice = hashtable->hash(clave,hashtable->tam);
	if(hashtable->tabla[indice] == NULL)
		hashtable->tabla[indice] = dato;
	else
	{
		k = 0;
		do
		{
			k++;
			nuevo_indice = hashtable->rehash(indice,k,hashtable->tam);
		}while( hashtable->tabla[nuevo_indice] != NULL);		
		hashtable->tabla[nuevo_indice] = dato;
	}
	hashtable->cant++;
	return 1;		
}

Cola buscarClave(HashTable* hashtable,void *dato)
{
	Cola cola = inicializarCola();
	if(!validarHashTable(hashtable))
		return cola;	
	int clave,indice,nuevo_indice,k;
	clave = hashtable->folding(dato);
	indice = hashtable->hash(clave,hashtable->tam);
	if(hashtable->tabla[indice] == NULL)
		return cola;
	else
	{
		k = 0;
		do
		{
			nuevo_indice = hashtable->rehash(indice,k,hashtable->tam);
			if(hashtable->tabla[nuevo_indice]!=NULL)
			{
				if(hashtable->comparar(hashtable->tabla[nuevo_indice],dato)==0)
					enqueue(&cola,hashtable->tabla[nuevo_indice]);			
			}
			k++;
		}while( hashtable->tabla[nuevo_indice] != NULL);	
		return cola;
	}
}

void imprimirHashTabla(HashTable *hashtable)
{
	if(!validarHashTable(hashtable))
		return;
	int i,cont=0;
	for(i = 0; i < hashtable->tam ; i++)
	{
		if(hashtable->tabla[i]!=NULL)
		{
			printf("\n [%d] = ",i);
			hashtable->imprimir(hashtable->tabla[i]);
			cont++;
			if( cont == hashtable->cant)
				break;
		}
	}		
}