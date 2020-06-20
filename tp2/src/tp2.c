/*
 ============================================================================
 Name        : tp2.c
 Author      : Jose Nogueira
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Employees.h"

#define EMPLOYEES_LEN 1000

int main(void) {
	setbuf(stdout,NULL);



	int idAux = 1;
	int opcion;
	int indice = 1;
	int flagOrder;

	Employees employeesArray[EMPLOYEES_LEN];
	if(initEmployees(employeesArray,EMPLOYEES_LEN)==0)
		{
			printf("array ok\n");
		}

	//cli_Altaforzada(Employees* pEmployee, int limite,int indice,int* id,char* name,char* lastName, int sector,float salary)
	//Altaforzada(employeesArray,EMPLOYEES_LEN,0,&idAux,"jose","hola",1,1000);
	//Altaforzada(employeesArray,EMPLOYEES_LEN,1,&idAux,"pedro","chau",3,2000);
	//Altaforzada(employeesArray,EMPLOYEES_LEN,2,&idAux,"pepe","qhace",2,3000);


	do
	{

		printf("\n1.Alta de Empleado");
		printf("\n2.Modificar Empleado");
		printf("\n3.Baja de Empleado");
		printf("\n4.Listar");
		printf("\n5.Informar");
		printf("\n6.Salir\n");
		(utn_getNumero(&opcion,"Ingrese una opcion\n", "Error,reingrese\n",1,5,2));

		switch(opcion)
		{
		case 1:
			getEmployee(employeesArray,EMPLOYEES_LEN,&idAux);
			break;

		case 2:
			if(validarMenu(employeesArray,EMPLOYEES_LEN)==0)
			{
				modifyEmployee(employeesArray,EMPLOYEES_LEN,indice);
			}
			break;

		case 3:
			if(validarMenu(employeesArray,EMPLOYEES_LEN)==0)
			{
				getRemoveEmployees(employeesArray,EMPLOYEES_LEN);
			}
			break;

		case 4:
			if(validarMenu(employeesArray,EMPLOYEES_LEN)==0)
			{
			printEmployeesArray(employeesArray,EMPLOYEES_LEN);
			}
			break;

		case 5:
			if(validarMenu(employeesArray,EMPLOYEES_LEN)==0)
			{
				if(!utn_getNumero(&flagOrder,"[1.Order Apellido][0.Order Sector]","Error",0,1,2))
				{
					printEmployeesArray(employeesArray,EMPLOYEES_LEN);
					sortEmployees(employeesArray,EMPLOYEES_LEN,flagOrder);
					printEmployeesArray(employeesArray,EMPLOYEES_LEN);
					 totalYPromedioSalarios(employeesArray,EMPLOYEES_LEN);
				}

			}
			break;
		}

	}while(opcion != 6);
	return EXIT_SUCCESS;
}
