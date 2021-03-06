#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"
#include "utn.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pF = NULL;
    if(path != NULL && pArrayListEmployee != NULL)
    {
    	pF = fopen(path,"r");
    	if(pF != NULL)
    	{
    		parser_EmployeeFromText(pF,pArrayListEmployee);
    		fclose(pF);
    		retorno = 0;
    	}
    	else
		{
			printf("Error en la apertura del archivo\n");
		}
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pF = NULL;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pF = fopen(path,"rb");
		{
			if(pF != NULL)
			{
				parser_EmployeeFromBinary(pF,pArrayListEmployee);
				fclose(pF);
				retorno = 0;
			}
			else
			{
				printf("Error en la apertura del archivo\n");
			}
		}
	}
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pE;
    int retorno =-1;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    int sueldo;

    pE = employee_new();
    if(pArrayListEmployee != NULL && pE != NULL)
    {
    	if(!utn_getNombre(nombre,NOMBRE_LEN,"Ingrese nombre\n","Error\n",2)&&
    		!utn_getNumero(&horasTrabajadas,"Ingrese cantidad de horas trabajadas\n","Error\n",0,10000,2)&&
			!utn_getNumero(&sueldo,"Ingrese su sueldo\n","Error\n",0,100000,2))
    	{
    		if(!employee_setId(pE,-1)&&
			   !employee_setNombre(pE,nombre)&&
			   !employee_setHorasTrabajadas(pE,horasTrabajadas)&&
			   !employee_setSueldo(pE,sueldo))
    		{
    			if(ll_add(pArrayListEmployee,pE))
    			{
    				printf("Carga exitosa\n");
    				retorno = 0;
    			}

    		}
    	}
    	else
    	{
    		printf("Error en la carga\n");
    	}
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

//El modificar y la baja no funcionan correctamente porque s�lo se queda con el �ltimo empleado al recorrer y evalua si ese es el que coincide con el id buscado.
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int idMod;
	int horasTrabajadasMod;
	int sueldoMod;
	int tam = ll_len(pArrayListEmployee);
	char nombreMod[NOMBRE_LEN];
	int i;
	int opcion = 0;
	Employee* bufferEmpleado;

	printf(":::::MODIFICAR EMPLEADO:::::\n");
	if(!controller_ListEmployee(pArrayListEmployee)&&
	   !utn_getNumero(&idMod,"ingrese id a modificar\n","error\n",1,tam,2)&&
	   (i = employee_printPorId(pArrayListEmployee,idMod))>= 0)
		{

			printf("1. Modificar nombre\n");
			printf("2. Modificar horas trabajadas\n");
			printf("3. Modificar sueldo\n");
			printf("4. salir\n");
			utn_getNumero(&opcion,"Ingrese una opcion\n","Error\n,",1,4,2);
			bufferEmpleado = ll_get(pArrayListEmployee,i);
			switch(opcion)
			{
				case 1:
					if(!utn_getNombre(nombreMod,NOMBRE_LEN,"Ingrese nuevo nombre\n","Error al modificar\n",2))
					{
						printf("Nombre modificado con exito\n");
						employee_setNombre(bufferEmpleado,nombreMod);
						ll_set(pArrayListEmployee,i,bufferEmpleado);
						retorno = 0;
					}
					break;
				case 2:
					if(!utn_getNumero(&horasTrabajadasMod,"Ingrese nueva cantidad de horas trabajdas\n","Error al modificar\n",0,1000,2))
					{
						employee_setHorasTrabajadas(bufferEmpleado,horasTrabajadasMod);
						ll_set(pArrayListEmployee,i,bufferEmpleado);
						printf("Nombre modificado con exito\n");
						retorno = 0;

					}
					break;
				case 3:
					if(!utn_getNumero(&sueldoMod,"Ingrese nuevo sueldo\n","Error al modificar\n",0,1000,2))
					{
						employee_setSueldo(bufferEmpleado,sueldoMod);
						ll_set(pArrayListEmployee,i,bufferEmpleado);
						printf("Nombre modificado con exito\n");
						retorno = 0;
					}
					break;
				case 4:
					opcion = 1;
					break;
			}

		}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	int idAux;
	int tam = ll_len(pArrayListEmployee);
	Employee* bufferEmpleado;

	if(pArrayListEmployee != NULL)
	{
		printf(":::::Baja de empleado:::::\n");
		if(!controller_ListEmployee(pArrayListEmployee)&&
		   !utn_getNumero(&idAux,"ingrese id a eliminar\n","error\n",1,tam,2)&&
		   (i = employee_printPorId(pArrayListEmployee,idAux))>= 0)
		{
			bufferEmpleado = (Employee*)ll_pop(pArrayListEmployee,i);
			employee_delete(bufferEmpleado);
			retorno = 0;
			printf("Baja exitosa\n");
		}
	}
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* aux;
	if(pArrayListEmployee != NULL)
	{
		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			aux = ll_get(pArrayListEmployee,i);
			if(aux != NULL)
			{
				employee_print(aux);
			}
			retorno = 0;
		}
	}
   return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int opcion;
	int retorno = -1;

	if(!utn_getNumero(&opcion,"ingrese el tipo de ordenamiento\n", "error\n",0,1,2))
	{
		if(pArrayListEmployee != NULL && ll_sort(pArrayListEmployee,employee_funcionCriterio,opcion))
		{
			retorno = 0;
			printf("Se ordeno correctamente\n");
		}
	}
	else
	{
		printf("Error al ordenar\n");
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	int id;
	int horasTrabajadas;
	int sueldo;
	char nombre[NOMBRE_LEN];
	Employee* bufferEmpleado =employee_new();
	FILE* pF ;
	pF=fopen(path,"w");

	if(path != NULL && pArrayListEmployee != NULL && pF != NULL)
	{

		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			if(i==0)
			{
				fprintf(pF,"id,nombre,horasTrabajadas,sueldo\n");

			}

				bufferEmpleado = ll_get(pArrayListEmployee,i);
				if(!employee_getId(bufferEmpleado,&id)&&
					!employee_getNombre(bufferEmpleado,nombre)&&
					!employee_getHorasTrabajadas(bufferEmpleado,&horasTrabajadas)&&
					!employee_getSueldo(bufferEmpleado,&sueldo))
				{

					retorno = 0;
					fprintf(pF,"%d,%s,%d,%d\n",id,nombre,horasTrabajadas,sueldo);
				}


		}
		printf("\ndatos guardados en archivo de texto\n");

	}
	else
	{
		printf("No se pudo abrair el archivo\n");
	}
	fclose(pF);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* bufferEmpleado;
	FILE* pF;
	pF = fopen(path,"wb");


	if(path != NULL && pArrayListEmployee != NULL && pF!= NULL)
	{

		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			bufferEmpleado = ll_get(pArrayListEmployee,i);
			if(bufferEmpleado != NULL)
			{
				fwrite(bufferEmpleado,sizeof(Employee),1,pF);
				retorno = 0;
			}
		}
		printf("\ndatos guardados en archivo de binario\n");
	}
	else
	{
		printf("No se pudo abrair el archivo\n");
	}
	fclose(pF);
    return retorno;
}

