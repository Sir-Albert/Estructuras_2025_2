#include "arbol.h"

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)			
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)			
			raiz->dch = crearNodoA(dato);
		else			
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}




void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}



void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}


void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

/*
void eliminarDatoArbol(Arbol *arbol, void *dato)
{
	Resultado res = buscarEnArbol(*arbol,dato);
	if(!res.dato)
		return;	
	arbol->cantidad--;
	if(!res.padre)
	{
		//ESTOY ELIMINANDO LA RAIZ DEL ARBOL
		if(!res.nodo->izq)
			arbol->raiz = res.nodo->dch;
		else{
			arbol->raiz = res.nodo->izq;
			NodoA *extD = res.nodo->izq;
			while(extD->dch!=NULL)
				extD = extD->dch;
			extD->dch = res.nodo->dch;
		}
	}		
	else
	{
		
		if(!res.nodo->izq)
		{
			if(res.rama == IZQUIERDA)
				res.padre->izq = res.nodo->dch;
			else 
				res.padre->dch = res.nodo->dch;
		}
		
		else{
			NodoA *extD = res.nodo->izq;
			while(extD->dch!=NULL)
				extD = extD->dch;
			extD->dch = res.nodo->dch;
			if(res.rama == IZQUIERDA)
				res.padre->izq = res.nodo->izq;
			else 
				res.padre->dch = res.nodo->izq;
		}
	}
	
	arbol->liberar(res.nodo->dato);
	free(res.nodo);
}
*/

/*
Resultado busquedaEnNodos(NodoA *padre,NodoA* raiz,void *dato, int (*comparar)(void*,void*))
{
	Resultado aux;
	if(!raiz)
		return (Resultado){NULL,NULL,NULL,IZQUIERDA};
	if( comparar( raiz->dato,dato) == 0 )
		return (Resultado){padre,raiz,raiz->dato,(padre && padre->izq==raiz) ? IZQUIERDA:DERECHA};
	aux = busquedaEnNodos(raiz , raiz->izq , dato, comparar); 
	if( !aux.dato)
		aux = busquedaEnNodos(raiz , raiz->dch , dato, comparar);  
	return aux;	
}*/



Resultado busquedaEnNodos(NodoA *padre,NodoA *raiz,void *dato, int (*comparar)(void*,void*) )
{
	if(!raiz)
		return (Resultado){NULL,NULL,NULL,IZQUIERDA};
	if( comparar( raiz->dato , dato ) == 0 )
	{
		int rama = (padre && padre->izq == raiz ) ? IZQUIERDA:DERECHA;  
		return (Resultado){padre,raiz,raiz->dato,rama};
	}
	else if( comparar( raiz->dato , dato ) > 0 )
		return busquedaEnNodos (raiz, raiz->izq , dato, comparar );
	else 
		return busquedaEnNodos (raiz, raiz->dch , dato, comparar );
	
	
}




Resultado buscarEnArbol(Arbol arbol,void *dato)
{
	Resultado res = busquedaEnNodos(NULL,arbol.raiz,dato,arbol.comparar);
	return res;
}


NodoA* extremoD(NodoA *raiz)
{
	NodoA *extD = raiz;
	while( extD && extD->dch!=NULL)
		extD = extD->dch;
	return extD;
}



void eliminarDatoArbol(Arbol *arbol, void *dato)
{
	NodoA *izquierdo,*extD,*derecho,*aux;
	Resultado res = buscarEnArbol(*arbol,dato);
	if(!res.dato )
		return;	
	izquierdo = res.nodo->izq;
	derecho = res.nodo->dch;
	extD = extremoD(izquierdo);	
	if(res.padre)
	{
		aux = (izquierdo) ? izquierdo:derecho;
		if(extD)
			extD->dch = derecho;
		if( res.rama == IZQUIERDA)
			res.padre->izq = aux;
		else
			res.padre->dch = aux;	
	}
	else
	{
		aux = (izquierdo) ? izquierdo:derecho;
		if(extD)
			extD->dch = derecho;
		arbol->raiz = aux;
	}
	if(arbol->liberar)
		arbol->liberar(res.nodo->dato);
	free(res.nodo);
	arbol->cantidad--;	
}


void calcularAltura(NodoA *raiz,int *altura)
{
	int izquierdo,derecho;
	izquierdo = derecho = *altura;
	if(raiz->izq && izquierdo++ )
		calcularAltura(raiz->izq,&izquierdo);
	if(raiz->dch && derecho++ )
		calcularAltura(raiz->dch,&derecho); 
	*altura = (izquierdo>derecho) ? izquierdo:derecho;
}

int altura(Arbol arbol)
{
	if(!arbol.raiz)
		return 0;
	int altura = 1;
	calcularAltura(arbol.raiz,&altura);
	return altura;
}

void extraccionDatos(NodoA *raiz,void **datos,int *indice)
{
	if(!raiz)
		return;
	extraccionDatos(raiz->izq,datos,indice);
	datos[*indice] = raiz->dato;
	(*indice)++;
	extraccionDatos(raiz->dch,datos,indice);
	
}


void ordenarRaices(void **inicio,void **fin,void **ordenado,int *indice)
{
	int mitad=0;
	if(inicio > fin)return;
	mitad = (fin - inicio + 1)/2;
	ordenado[*indice] = *(inicio+mitad);
	(*indice)++;	
	if(inicio == fin)return;
	//MITAD IZQUIERDA	
	ordenarRaices(inicio,inicio+mitad-1,ordenado,indice);
	//MITAD DERECHA
	ordenarRaices(inicio+mitad+1,fin,ordenado,indice);
}

void equilibrar(Arbol *arbol)
{
	void (*liberar)(void*) = arbol->liberar; // GUARDAR FUNCION DE LIBERAR
	//ASIGNAR NULO PARA QUE EN LA ELIMINACION DEL ARBOL
	//NO SE ELIMINEN LOS DATOS
	arbol->liberar = NULL; 
	int indice = 0;
	int cantidad = arbol->cantidad;
	void **datos = calloc(cantidad,sizeof(void*)); //ARREGLO PARA ALMACENAR DATOS
	void **ordenados = calloc(cantidad,sizeof(void*)); //ARREGLO CON LOS DATOS ORDENADOS
	extraccionDatos(arbol->raiz,datos,&indice);	 //PASAR DATOS AL ARREGLO
	eliminarArbol(arbol); //BORRAR ARBOL
	arbol->liberar = liberar; //RESTAURAR FUNCION DE LIBERAR
	indice = 0;
	//ORDENAR LOS DATOS PARA LA RECONSTRUCCION
	//PRIORIZANDO LAS RAICES
	ordenarRaices(datos,datos+(cantidad-1),ordenados,&indice); 
	for( int i=0; i<cantidad ; i++)
		insertarArbol(arbol, ordenados[i]  ); //RECONSTRUIR ARBOL
	free(datos);
	free(ordenados);
}