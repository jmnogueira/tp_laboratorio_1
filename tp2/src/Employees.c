/*
 * Employees.c
 *
 *  Created on: 4 may. 2020
 *      Author: JM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Employees.h"


/*
 * brief da un valor conocido al array
 * pemployees array de employees
 * len tamanio del arry*/

int initEmployees(Employees* pEmployees, int len)
{
	int retorno = -1;
	int i;

	if(pEmployees != NULL && len >= 0)
	{
		for(i=0;i<len;i++)
		{
			retorno = 0;
			pEmployees[i].isEmpty = 1;
		}
	}
	return retorno;
}

/*
 * brief busca primer lugar libre en el array
 * pemployees array de employees
 * len tamanio del arry*/
int getEmptyIndex(Employees* pEmployees, int len)
{
	int retorno = -1;
	int i;

	if(pEmployees != NULL && len >= 0)
	{
		for(i=0;i<len;i++)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

/*
 * brief imprime un empleado
 * pemployees array de employees
 * */
int printEmployee(Employees* pEmployees)
{
	int retorno = -1;

	if(pEmployees != NULL && pEmployees->isEmpty == 0)
	{
		retorno = 0;
		printf("\nID: %d - NAME: %s - LASTNAME: %s - SECTOR: %d - SALARY: %.2f",pEmployees->id,pEmployees->name,pEmployees->lastName,pEmployees->sector,pEmployees->salary);
	}
	return retorno;
}

/*
 * brief imprime array de empleado
 * pemployees array de employees
 * len tamanio del arry*/
int printEmployeesArray(Employees* pEmployees, int len)
{
	int retorno = -1;
	int i;

	if(len >= 0)
	{
		for(i=0;i<len;i++)
		{
			if(pEmployees[i].isEmpty == 0)
			{
				retorno = 0;
				printEmployee(&pEmployees[i]);
			}
		}
	}
	return retorno;
}

/*
 * brief da de alta un empleado
 * pemployees array de employees
 * int id puntero al id a cambiar
 * len tamanio del arry*/
int getEmployee(Employees* pEmployees, int len, int* id)
{

	Employees employeesAux;
	int retorno = -1;
	if(pEmployees != NULL && len > 0)
	{
		if(!utn_getNombre(employeesAux.name,NAME_LEN,"Ingrese nombre\n","ERROR, reintente\n",2))
		{
			if(!utn_getNombre(employeesAux.lastName,LASTNAME_LEN,"Ingrese apellido\n","ERROR, reintente\n",2))
			{
				if(!utn_getNumeroFlotante(&employeesAux.salary,"Ingrese salario\n","ERROR,reintente",0,100000,2))
				{
					if(!utn_getNumero(&employeesAux.sector,"Ingrese sector\n","ERROR\n",0,5,2))
					{
						if(addEmployee(pEmployees,len,*id,employeesAux.name,employeesAux.lastName,employeesAux.salary,employeesAux.sector)==0)
						{
							*id +=1;
							printf("Carga exitosa\n");
						}
						else
						{
							printf("No hay mas espacio\n");
						}
					}
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}

/*
 * brief Agrega en un array de empleados existente los valores recibidos como parámetro en la primer posición libre.
 * pemployees array de employees
 * int id puntero al id a cambiar
 * len tamanio del arry*/
int addEmployee(Employees* pEmployees, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int retorno = -1;
	int indice;

	indice = getEmptyIndex(pEmployees,len);
	if(pEmployees != NULL && len > 0 && id >= 0 && name != NULL && lastName != NULL && salary > 0 && sector >= 0)
	{
		retorno = 0;
		pEmployees[indice].id = id;
		strncpy(pEmployees[indice].name,name,NAME_LEN);
		strncpy(pEmployees[indice].lastName,lastName,LASTNAME_LEN);
		pEmployees[indice].salary = salary;
		pEmployees[indice].sector = sector;
		pEmployees[indice].isEmpty = 0;

	}
	return retorno;
}

/*
 * brief busca un empleado y devulve la posisicon donde se encuentra
 * pemployees array de employees
 * int id puntero al id a cambiar
 * len tamanio del arry*/
int findEmployeeById(Employees* pEmployees, int len,int id)
{
	int retorno = -1;
	int i;

	if(pEmployees != NULL && len >= 0 && id >= 0)
	{
		retorno = 0;
		for(i=0;i<len;i++)
		{
			if(pEmployees[i].isEmpty == 0 && pEmployees[i].id == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/*Elimina de manera lógica (isEmpty Flag en 1) un empleado recibiendo como parámetro su Id.
 * pemployees array de employees
 * int id puntero al id a cambiar
 * len tamanio del arry*/
int removeEmployee(Employees* pEmployees, int len, int id)
{
	int retorno = -1;
	int indice;

	if(pEmployees != NULL && len >= 0 && id >= 0 && pEmployees->isEmpty == 0)
	{
		retorno = 0;
		indice = findEmployeeById(pEmployees,len,id);
		pEmployees[indice].isEmpty = 1;
	}
	return retorno;
}

/*Elimina  un empleado
 * pemployees array de employees
 *
 * len tamanio del arry*/
int getRemoveEmployees(Employees* pEmployees,int len)
{
	int retorno = -1;
	int id;
	int indice;
	if(printEmployeesArray(pEmployees, len) == 0)
	{
		if(!utn_getNumero(&id,"Ingrese ID\n","ERROR\n",0,1000,2))
		{
			indice = findEmployeeById(pEmployees,len,id);
			if(indice >= 0)
			{
				if(removeEmployee(pEmployees,len,id) == 0)
				{
					printf("\nBaja con exito\n");
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/*brief modifica un empleado.
 * pemployees array de employees
 * int indice  empleado a ser acutualizado
 * len tamanio del arry*/
int modifyEmployee(Employees* pEmployees, int len,int indice)
{
	int retorno = -1;
	int id;
	int opcion;
	char name[NAME_LEN];
	char lastName[LASTNAME_LEN];
	float salary;
	int sector;


			printEmployeesArray(pEmployees, len);
			if(!utn_getNumero(&id,"\nIngrese ID\n","ERROR\n",0,1000,2))
			{

				printf("\n1.MODIFICAR NOMBRE\n");
				printf("\n2.MODIFICAR APELLIDO\n");
				printf("\n3.MODIFICAR SALARY\n");
				printf("\n4.MODIFICAR SECTOR\n");
				utn_getNumero(&opcion,"\nIngrese una opcion\n","Opcion incorrecta\n",0,5,2);
				indice = findEmployeeById(pEmployees,len,id);
				if(indice >= 0)
				{
					switch(opcion)
					{
					case 1:
						if(!utn_getNombre(name,NAME_LEN,"Ingrese nuevo nombre\n","Error,reintente\n",2))
						{
							strncpy(pEmployees[indice].name,name,NAME_LEN);
							printf("\nCambio exitoso\n");
						}
						break;

					case 2:
						if(!utn_getNombre(lastName,LASTNAME_LEN,"Ingrese nuevo apellido\n","Error,reintente\n",2))
						{
							strncpy(pEmployees[indice].lastName,lastName,LASTNAME_LEN);
							printf("\nCambio exitoso\n");
						}
						break;

					case 3:
						if(!utn_getNumeroFlotante(&salary,"Ingrese nuevo salario\n","ERROR,reintente",0,100000,2))
						{
							pEmployees[indice].salary = salary;
							printf("\nCambio exitoso\n");
						}
						break;

					case 4:
						if(!utn_getNumero(&sector,"Ingrese nuevo sector\n","ERROR\n",0,5,2))
						{
							pEmployees[indice].sector = sector;
							printf("\nCambio exitoso\n");
						}
						break;
					}
				}
			}

	return retorno;

}

int Altaforzada(Employees* pEmployee, int limite,int indice,int* id,char* name,char* lastName, int sector,float salary)
{
	int retorno = -1;
	Employees pEmployeeAux;

	if(pEmployee != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		strncpy(pEmployeeAux.name,name,NAME_LEN);
		strncpy(pEmployeeAux.lastName,lastName,LASTNAME_LEN);
		pEmployeeAux.sector = sector;
		pEmployeeAux.salary = salary;
		pEmployeeAux.id = *id;
		*id = *id + 1;
		pEmployeeAux.isEmpty = 0;
		pEmployee[indice] = pEmployeeAux;
		retorno = 0;
	}
		return retorno;
}

/*brief orderna array
 * pemployees array de employees
 * int order 1 por sector 0 por apellido
 * len tamanio del arry*/
int sortEmployees(Employees* pEmployee, int len, int order)
{
	int retorno = -1;
	int i;
	int flagSwap;
	Employees bufferAux;
	if(pEmployee != NULL && len > 0)
	{
		if(order == 1)
		{
			do
			{
				flagSwap = 0;
				for(i=0;i<len-1;i++)
				{
					if(pEmployee[i].isEmpty == 1 && pEmployee[i+1].isEmpty == 1)
					{
						retorno = -1;
						break;
					}
					if(pEmployee[i].sector > pEmployee[i+1].sector )
					{
						flagSwap = 1;
						bufferAux = pEmployee[i];
						pEmployee[i] = pEmployee[i+1];
						pEmployee[i+1] = bufferAux;
					}
				}
				len--;
			}while(flagSwap);
		}

		else if(order == 0)
		{
			do
			{
				flagSwap = 0;
				for(i=0;i<len-1;i++)
				{
					if(pEmployee[i].isEmpty == 0 && pEmployee[i+1].isEmpty == 0)
					{
						retorno = -1;
						break;
					}
					if(strncmp(pEmployee[i].lastName,pEmployee[i+1].lastName,NAME_LEN) > 0)
					{
						flagSwap = 1;
						bufferAux = pEmployee[i];
						pEmployee[i] = pEmployee[i+1];
						pEmployee[i+1] = bufferAux;
					}
				}
				len--;
			}while(flagSwap);
		}
	}
	return retorno;
}

/*brief calcula total y priomedio de los empleados
 * pemployees array de employees
 * len tamanio del arry*/
int totalYPromedioSalarios(Employees* pEmployee, int len)
{
	int retorno = -1;
	float acumuladorSalario = 0;
	int contador = 0;
	float promedio;
	int i;

	if(pEmployee != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			if(pEmployee[i].isEmpty == 0)
			{
				acumuladorSalario+=pEmployee[i].salary;
				contador++;
			}
		}
	}
	promedio = acumuladorSalario/contador;
	printf("\nEl total de salario es: %.2f\n",acumuladorSalario);
	printf("El promedio es: %.2f\n",promedio);
	return retorno;
}

int validarMenu(Employees* pEmployee, int len)
{
	int retorno = -1;
	int i;
	if(pEmployee != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			if(pEmployee[i].isEmpty == 0)
			{
				retorno = 0;
				break;
			}
			if(pEmployee[i].isEmpty == 1)
			{
				printf("Dar de alta primero\n");
				break;
			}
		}
	}
	return retorno;
}
