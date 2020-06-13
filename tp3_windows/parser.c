#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* pE;
	int retorno = -1;
	char id[128];
	char nombre[128];
	char horasTrabajadas[128];
	char sueldo[128];

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo)==4)
			{
				pE = employee_newParametros(id,nombre,horasTrabajadas,sueldo);
				if(pE != NULL && !ll_add(pArrayListEmployee,pE))
				{
					retorno = 0;
				}
			}
		}while(feof(pFile)==0);
	}
	return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int fin = 1;
	Employee* pE;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			pE = employee_new();
			fin = fread(pE,sizeof(Employee),1,pFile);
			if(fin == 1  && pE != NULL)
			{
				ll_add(pArrayListEmployee,pE);
				retorno = 0;
			}
		}while(feof(pFile)==0);
	}
    return retorno;
}
