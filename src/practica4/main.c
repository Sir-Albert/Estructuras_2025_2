#include <stdio.h>
#include <stdlib.h>
#include "../Estructuras/pila/pila.h"

#define ARRIBA 1
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 8

#define REN 27
#define COL 26

typedef struct
{
	int x,y;
}Coordenada;


unsigned char ** crear_laberinto(void);
void imprimirLab(unsigned char **lab);


Coordenada* crearCoordenada(int x,int y);
int compararCoordenada(void *a,void *b);
void imprimirCoordenada(void *dato);

unsigned char alternativas(unsigned char **lab,Coordenada *coordenada);
void imprimirPosibles(unsigned char);

Pila solucion(unsigned char **lab);

int main(void)
{
    unsigned char **lab; 
    lab = crear_laberinto();
    imprimirLab(lab);
	Pila prueba = solucion(lab);
	printf("\n PILA RESPUESTA");
	imprimirPilaInvertida(prueba);
	imprimirLab(lab);	
    printf("\n\n FIN DE PROGRAMA");
    return 0;
}


void imprimirLab(unsigned char **lab)
{
	int i,j;
	for(i=0;i<REN;i++)
    {
        printf("\n\r");
        for(j=0;j<COL;j++)
        {
            if(lab[i][j]=='*')printf("  ");
			else printf("%c ",lab[i][j]);
        }   
    }
}

unsigned char ** crear_laberinto(void)
{
    int i,j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x*************Bx\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

 
    
    unsigned char **lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    
    for(i=0;i<REN;i++)
    {
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    
    for(i=0;i<REN;i++)
    {
        //printf("\n\r");
        for(j=0;j<COL;j++)
        {
            //printf("%c",tmp[(i*COL)+j]);
            lab[i][j] = tmp[(i*COL)+j];
        }   
    }
    return lab;
}


Coordenada* crearCoordenada(int x,int y)
{
	Coordenada *nueva = malloc(sizeof(Coordenada));
	nueva->x=x;
	nueva->y=y;
	return nueva;
}

void imprimirCoordenada(void *dato)
{
	Coordenada *a = dato;
	printf("[%-2d,%-2d]", a->x,a->y);
}

int compararCoordenada(void *a,void *b)
{
	Coordenada *aa=a,*bb=b;
	if(aa->x==bb->x && aa->y==bb->y)
		return 1;
	return 0;
}



unsigned char alternativas(unsigned char **lab,Coordenada *coordenada)
{		
	unsigned char caracter;
	unsigned char banderas;
	banderas = 0;	
	//EVALUAR ALTERNATIVA Y REGISTRAR POSIBILIDAD DE MOVIMIENTO
	//EN UN REGISTRO DE BITS/BANDERAS	
	caracter = lab[coordenada->x-1][coordenada->y];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= ARRIBA;
	
	caracter = lab[coordenada->x+1][coordenada->y];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= ABAJO;
	
	caracter = lab[coordenada->x][coordenada->y+1];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= DERECHA;
	
	caracter = lab[coordenada->x][coordenada->y-1];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= IZQUIERDA;
	return banderas;	
}


void imprimirPosibles(unsigned char caminos)
{
	if(caminos&ARRIBA)
		printf("\n ARRIBA");
	if(caminos&ABAJO)
		printf("\n ABAJO");
	if(caminos&IZQUIERDA)
		printf("\n IZQUIERDA");
	if(caminos&DERECHA)
		printf("\n DERECHA");
}

Pila solucion(unsigned char **lab)
{
	unsigned char posibles;
	Pila respuesta = inicializarPila();
	Pila basura = inicializarPila();
	respuesta.imprimir = basura.imprimir = &imprimirCoordenada;
	respuesta.liberar = basura.liberar = &free;
	Coordenada *coordenada = crearCoordenada(1,1);
	push(&respuesta,coordenada);
	while(!vacia(respuesta) && lab[coordenada->x][coordenada->y]!='B')
	{
		coordenada = peek(respuesta);
		posibles = alternativas(lab,coordenada);
		printf("\n");
		imprimirCoordenada(coordenada);
		getchar();
		//imprimirPosibles(posibles);
		imprimirLab(lab);		
		if(posibles&DERECHA)
		{			
			coordenada = crearCoordenada(coordenada->x,coordenada->y+1);
			lab[coordenada->x][coordenada->y] = (lab[coordenada->x][coordenada->y]!='B')?'.':'B';
			push(&respuesta, coordenada);
		}
		else if(posibles&ABAJO)		
		{			
			coordenada =crearCoordenada(coordenada->x+1,coordenada->y);
			lab[coordenada->x][coordenada->y] = (lab[coordenada->x][coordenada->y]!='B')?'.':'B';
			push(&respuesta, coordenada);
		}
		else if(posibles&IZQUIERDA)
		{			
			coordenada =crearCoordenada(coordenada->x,coordenada->y-1);
			lab[coordenada->x][coordenada->y] = (lab[coordenada->x][coordenada->y]!='B')?'.':'B';
			push(&respuesta, coordenada);
		}
		else if(posibles&ARRIBA)
		{			
			coordenada =crearCoordenada(coordenada->x-1,coordenada->y);
			lab[coordenada->x][coordenada->y] = (lab[coordenada->x][coordenada->y]!='B')?'.':'B';
			push(&respuesta, coordenada);
		}	
		else
		{
			coordenada =pop(&respuesta);			
			lab[coordenada->x][coordenada->y] = 'o';
			push(&basura,coordenada );
		}		
	}
	printf("\n PILA BASURA");
	imprimirPila(basura);
	eliminarPila(&basura);
	return respuesta;
}
