 /*
 ============================================================================
 Name        : calculadora.c
 Author      : Jose Nogueira
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"

int main(void) {
	setbuf(stdout, NULL);

	int respuesta = 0;
	int opcion;
	int operando1;
	int operando2;
	int flagOperando1 = 0;
	int flagOperando2 = 0;
	int flagOperaciones = 0;
	int retDivision;
	int retFactorial;
	int suma;
	int resta;
	int multi;
	float dividir;
	long factor1;
	long factor2;


	do
	{
		printf("Ingrese una opcion\n");
		if(flagOperando1 == 1)
		{
			printf("1.Ingrese primer operando: A= %d\n",operando1);
		}
		else
		{
			printf("1.Ingrese primer operando\n");
		}
		if(flagOperando2 == 1)
		{
			printf("2.Ingrese segundo operando: B= %d\n",operando2);
		}
		else
		{
			printf("2.Ingrese segundo operando\n");
		}
		printf("3.Calcular operaciones\n");
		printf("4.Listar operaciones\n");
		printf("5.Salir\n");
		printf("La opcion es: ");
		scanf("%d", &opcion);

		switch(opcion)
		{
		case 1:
			printf("Ingrese primer operando\n");
			flagOperando1 = scanf("%d",&operando1);
			flagOperaciones = 0;
			fflush(stdin);
			while(flagOperando1 != 1)
			{
				printf("Incorrecto, ingrese primer operando\n");
				fflush(stdin);
				flagOperando1 = scanf("%d",&operando1);
			}
			break;
		case 2:
			if(flagOperando1 == 1)
			{
				printf("Ingrese segundo operando\n");
				flagOperando2 = scanf("%d", &operando2);
				fflush(stdin);
				flagOperaciones = 0;
				while(flagOperando2 != 1)
				{
					printf("Incorrecto, ingrese segundo operando\n");
					flagOperando2 = scanf("%d", &operando2);
				}

			}
			else
			{
				printf("Primero ingrese operando 1\n");
			}


			break;
		case 3:
			if(flagOperando1 == 1 && flagOperando2 == 1)
			{

				suma = sumar(operando1,operando2);
				resta = restar(operando1,operando2);
				multi = multiplicacion(operando1, operando2);
				retDivision = division (operando1,operando2,&dividir);
				retFactorial = factorial(operando1,&factor1);
				retFactorial = factorial(operando2,&factor2);
				printf("Operaciones realizadas\n");
				flagOperaciones = 1;
			}
			else
			{
					printf("Error, no se ingresaron operandos\n");
			}
			break;

		case 4:
			if(flagOperando1 == 1 && flagOperando2 == 1)
			{
				if(flagOperaciones == 1)
				{
					printf("El resultado de la suma es:%d\n",suma);
					printf("El resultado de la resta es:%d\n",resta);
					printf("El resultado de la multiplicacion es:%d\n",multi);
					if(retDivision == 0)
					{
						printf("El resultado de la division es:%.2f\n",dividir);
					}
					else
					{
						printf("No es posible dividir por cero\n");
					}
					if(retFactorial == 0)
					{
						printf("El factorial del primer operando es:%ld\n",factor1);
						printf("El factorial del segundo operando es:%ld\n",factor2);
					}
					else
					{
						printf("No es posible factorizar numeros negativos\n");
					}
				}
			}
			else if(flagOperaciones == 0)
			{
				printf("Primero acceda a la opcion 3 para realizar las operaciones\n");
			}
			else
			{
				printf("Primero acceda a la opcion 3 para realizar las operaciones\n");
			}

			break;
		case 5:
			respuesta = 1;
			break;
		default:
			printf("Opcion incorrecta");
			break;
		}
		system("pause");

	}while(respuesta != 1);
	return EXIT_SUCCESS;
}
