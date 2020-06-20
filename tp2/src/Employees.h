/*
 * Employees.h
 *
 *  Created on: 4 may. 2020
 *      Author: JM
 */

#ifndef EMPLOYEES_H_
#define EMPLOYEES_H_

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

#define NAME_LEN 51
#define LASTNAME_LEN 51
typedef struct
{
	int id;
	char name[NAME_LEN];
	char lastName[LASTNAME_LEN];
	float salary;
	int sector;
	int isEmpty;
}Employees;

int menu();
int initEmployees(Employees* pEmployees, int len);
int getEmptyIndex(Employees* pEmployees, int len);
int printEmployee(Employees* pEmployees);
int printEmployeesArray(Employees* pEmployees, int len);
int getEmployee(Employees* pEmployees, int len, int* id);
int addEmployee(Employees* pEmployees, int len, int id, char name[],char lastName[],float salary,int sector);
int findEmployeeById(Employees* pEmployees, int len,int id);
int removeEmployee(Employees* pEmployees, int len, int id);
int getRemoveEmployees(Employees* pEmployees,int len);
int modifyEmployee(Employees* pEmployees, int len,int indice);
int Altaforzada(Employees* pEmployee, int limite,int indice,int* id,char* name,char* lastName, int sector,float salary);
int sortEmployees(Employees* pEmployee, int len, int order);
int totalYPromedioSalarios(Employees* pEmployee, int len);
int validarMenu(Employees* pEmployee, int len);
#endif /* EMPLOYEES_H_ */
