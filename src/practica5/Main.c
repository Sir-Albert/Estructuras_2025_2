#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"

#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 50

typedef struct
{
	Cola cola;
	int estado;
}Caja;


int generar_articulos(void);

int main(void)
{
	//Caja cajas[NUMERO_CAJAS];
	int opcion;	
	do
	{
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n [1] AVANZAR TICK");
		printf("\n [2] CONFIGURAR");
		printf("\n [3] HABILITAR/DESHABILITAR");
		printf("\n [4] TERMINAR");
		inputEntero("\n Selecciona opcion: ",&opcion);
		switch(opcion)
		{
			case 1:
			printf("\n [1]");
			break;
			case 2:
			printf("\n [2]");
			break;
			case 3:
			printf("\n [3]");
			break;
			case 4:
			printf("\n [4]");
			break;
			default:
			printf("\n [DEFAULT]");
				
		}	
	}while(opcion!=4);
	
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}


int generar_articulos(void)
{		
	return rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
}