#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

Employee* employee_new()
{
	return (Employee*)malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* punteroEmpleado = NULL;
	punteroEmpleado = employee_new();
	int flagOk = 0;
	if(punteroEmpleado != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		if(!employee_setId(punteroEmpleado,atoi(idStr))&&
		   !employee_setNombre(punteroEmpleado,nombreStr)&&
		   !employee_setHorasTrabajadas(punteroEmpleado,atoi(horasTrabajadasStr))&&
		   !employee_setSueldo(punteroEmpleado,atoi(sueldoStr)))
		{
			flagOk = 1;
		}
	}
	if(flagOk == 0)
	{
		employee_delete(punteroEmpleado);
		punteroEmpleado = NULL;
	}
	return punteroEmpleado;
}

int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	static int maximoId = -1;
	if(this != NULL)
	{
		retorno = 0;
		if(id < 0)
		{
			maximoId++;
			this->id = maximoId;
		}
		else if(id > maximoId)
		{
			maximoId = id;
			this-> id = id;
		}
	}
	return retorno;
}

int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL && id > 0)
	{
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int retorno =-1;
	if(this != NULL && nombre != NULL)
	{
		strncpy(this->nombre,nombre,NOMBRE_LEN);
		retorno = 0;
	}
	return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int retorno =-1;
	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre,this->nombre,NOMBRE_LEN);
		retorno = 0;
	}
	return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}


int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	{
		retorno = 0;
		this->sueldo = sueldo;
	}
	return retorno;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		retorno = 0;
		 *sueldo = this->sueldo;
	}
	return retorno;
}


int employee_delete(Employee* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int employee_print(Employee* this)
{
	int retorno = -1;
	int id;
	int horasTrabajadas;
	int sueldo;
	char nombre[NOMBRE_LEN];
	if(this != NULL)
	{
		employee_getId(this,&id);
		employee_getNombre(this,nombre);
		employee_getHorasTrabajadas(this,&horasTrabajadas);
		employee_getSueldo(this,&sueldo);
		printf("ID: %d - NOMBRE: %s - HORAS TRABAJaDAS: %d - SUELDO: %d\n",id,nombre,horasTrabajadas,sueldo);
		retorno = 0;
	}
	return retorno;
}

int employee_printAll(Employee* this,LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* aux;
	if(this != NULL && pArrayListEmployee != NULL)
	{
		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			aux = ll_get(pArrayListEmployee,i);
			if(aux != NULL)
			{
				employee_print(aux);
				retorno = 0;
			}
		}
	}
   return retorno;
}

int employee_funcionCriterio(void* item1, void* item2)
{
	int retorno = 0;
	char nombre1[NOMBRE_LEN];
	char nombre2[NOMBRE_LEN];
	Employee* bufferAux1;
	Employee* bufferAux2;


	bufferAux1 = item1;
	bufferAux2 = item2;

	if(!employee_getNombre(bufferAux1,nombre1) && !employee_getNombre(bufferAux2,nombre2))
	{
		if(strcmp(nombre1,nombre2) > 1)
		{
			retorno = 1;
		}
		else if(strcmp(nombre1,nombre2) < 0)
		{
			retorno =-1;
		}
	}


	return retorno;
}

int menu(void)
{

	int opcion;
	printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto)\n");
	printf("2. Cargar los datos de los empleados desde el archivo data.csv (modo binario)\n");
	printf("3. Alta de empleado\n");
	printf("4. Modificar datos de empleado\n");
	printf("5. Baja de empleado\n");
	printf("6. Listar empleados\n");
	printf("7. Ordenar empleados\n");
	printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
	printf("9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n");
	printf("10. Salir\n");

	utn_getNumero(&opcion,"Ingrese una opcion\n","Error\n",0,11,2);


	return opcion;

}
