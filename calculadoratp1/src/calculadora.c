/*
 * calculadoraa.c
 *
 *  Created on: 14 abr. 2020
 *      Author: JM
 */
#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"


/*brief suma 2 enteros
 * int recibe entero A
 * int recibe entero B
 * int devulve el valor de la suma*/

int sumar(int a, int b)
{
	int resultado;

	resultado = a + b;
	return resultado;
}


/*brief resta 2 enteros
 * int recibe entero A
 * int recibe entero B
 * int devulve el valor de la resta*/
int restar(int a, int b)
{
	int resultado;

	resultado = a - (b);
	return resultado;
}


/*brief multiplica 2 enteros
 * int recibe entero A
 * int recibe entero B
 * int devulve el valor de la multiplicacion*/
int multiplicacion(int a, int b)
{
	int resultado;

	resultado = a * b;
	return resultado;
}


/*brief divide 2 flotantes
 * int recibe entero A
 * int recibe entero B
 * float recibe el resutado de la division por referencia
 * int devulve 0 si esta si pudo dividir y 1 si no se pudo*/
int division(int a, int b, float* pResultado)
{
	float resultado;
	int retorno = 1;
	if(pResultado != NULL && b != 0)
	{
			resultado = (float) a / b;
			*pResultado = resultado;
			retorno = 0;
	}
	else
	{
		retorno = -1;
	}
	return retorno;

}


/*brief factorial de 1 entero
 * int recibe entero A
 * long int recibe el resultado por referencia
 * int devulve 0 si pudo realizar la operacion o 1 si no pudo*/
int factorial(int a, long int* pResultado)
{
	long factorial = 1;
	int retorno = 1;
	int i;
	if(pResultado != NULL && a > 0)
	{
		for(i=a; i>=1; i--)
		{
			factorial = factorial * i;
			retorno = 0;
		}
		*pResultado = factorial;
	}
	else
	{
		retorno = -1;
	}

	return retorno;
}


