
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"


int compararPrecedencia(char *a,char *b);
int precedencia(char c);
int contarParentesis(char *cadena);
char* infixToPostfix(char *cadena);


int main(void)
{
	char *infix = NULL;
	inputCadenaDinamica("\n Captura infix: ",&infix,100);
	char *postfix = infixToPostfix(infix);
	printf("\n Postfix: %s",postfix);	
	printf("\n\n FIN DE PROGRAMA\n");
	return 0;
}


char* infixToPostfix(char *cadena)
{
	int longitudCadena = strlen(cadena) + 1;
	int cantidadParentesis = contarParentesis(cadena);
	int longitudPostfix = longitudCadena-cantidadParentesis;
	char *postfix = (char*) calloc(longitudPostfix,sizeof(char));
	int i,indice=0;
	Pila pila = inicializarPila();
	for( i = 0; cadena[i]!='\0'; i++)
	{
		//1
		if( ( cadena[i]>='A' && cadena[i]<='Z') || (cadena[i]>='a' && cadena[i]<='z' ) )
		{
			postfix[indice++] = cadena[i];continue;
		}
		//2
		if(vacia(pila) || precedencia(cadena[i])==-1 || compararPrecedencia(&cadena[i],peek(pila))==1 )
		{
			push(&pila,&cadena[i]);continue;
		}
		//3 y 4
		else
		{
			if(precedencia(cadena[i])!=0)
			{
				while(!vacia(pila) && precedencia(*(char*)peek(pila))!=0 && compararPrecedencia(peek(pila),&cadena[i])>=0)
				{
					char *operador = pop(&pila);
					postfix[indice++] = *operador;
				}
				push(&pila,&cadena[i]);
			}
			else
			{
				while(!vacia(pila) && precedencia(*(char*)peek(pila))!=-1)
				{
					char *operador = pop(&pila);
					postfix[indice++] = *operador;
				}				
				pop(&pila);
			}
		}
	}
	while(!vacia(pila))
	{
		char *operador = pop(&pila);
		postfix[indice++] = *operador;
	}
	return postfix;
}


int contarParentesis(char *cadena)
{
	int i=0,cantidad=0;
	for( i = 0; cadena[i]!='\0' ; i++)
	{
		if( cadena[i]=='(' ||  cadena[i]==')')
			cantidad++;
	}
	return cantidad;
}


int precedencia(char c)
{
	switch(c)
	{
		case '+':case '-':
			return 1;
		case '*':case '/':
			return 2;			
		case '^':
			return 3;			
		case '(':
			return -1;
	}
	return 0;
}

int compararPrecedencia(char *a,char *b)
{
	if( precedencia(*a)>precedencia(*b) )
		return 1;
	else if( precedencia(*a)<precedencia(*b) )
		return -1;
	else return 0;
}



