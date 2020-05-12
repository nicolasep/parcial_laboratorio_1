/*
 * Cliente.c
 *
 *  Created on: 8 may. 2020
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Publicacion.h"
#include "Cliente.h"


#define CLI_LEN 100
#define CADENA_LEN 64
#define NOMBRE_LEN 64
#define APELLIDO_LEN 64
#define CUIT_LEN 21

/*
 * \brief inicializa el array de clientes cambiandole el isEmpy 1
 * \param lista de clientes
 * \param longitud del array clientes
 * \return devuelve 0 si fue un exito y -1 si no
 * */
int cli_inicializar(Cliente* list, int len)
{
	int retorno = -1;
	int i;
	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			list[i].isEmpty = 1;
		}
	  	retorno = 0;
	}

	return retorno;
}
/*
 * \brief busca una posicion libre en el array de clientes y la devuelve
 * \param array de clientes
 * \param longitud del array de clients
 * \return devuelve la primera posicion libre o -1 si no enuentra
 * */
int cli_buscarLibre(Cliente* list, int len)
{
	int retorno = -1;
	int i;
	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief imprime un cliente por pantalla
 * \param puntero a la direccion de memoria del elemento
 * \return devuelve 0 si pudo imprir y -1 si no encontro
 * */
int cli_printCliente(Cliente* pCliente)
{
	int retorno = -1;
	if(pCliente != NULL)
	{
		printf("ID: %d - NOMBRE: %s - APELLIDO: %s - CUIT: %s\n",pCliente->idCliente,pCliente->nombre,pCliente->apellido,pCliente->cuit);
		retorno = 0;
	}

	return retorno;
}
/*
 * \brief imprime la lista de clientes activos por pantalla
 * \param array de clientes
 * \param longitud del array de clientes
 * \return devuelve 0 si pudo imprimir y -1 si no pudo
 * */
int cli_printClientes(Cliente* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				cli_printCliente(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 *  \brief busca un cliente por ID y devuelve su posicion en el array
 *  \param array de clientes
 *  \param longitud del array de clientes
 *  \param id a ser buscado
 *  \return devuelve el lugar del array del cliente o -1 si no lo encuentra
 * */
int cli_buscarClientePorId(Cliente* list, int len, int id)
{
	int retorno = -1;
	int i;
	if(list != NULL && len > 0 && id > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == id)
			{
				retorno = i;
			}
		}
	}

	return retorno;
}
/*
 * \brief pide los datos de un nuevo cliente al usuario, lo valida y lo carga en una posicion libre del array
 * \param array de clientes
 * \param longiud del array de clientes
 * \param puntero a la direcion de memoria del id inicial
 * \return devuelve 0 si pudo cargar y -1 si no pudo
 * */
int cli_altaCliente(Cliente* list, int len, int* id)
{
	int retorno = -1;
	Cliente auxCliente;
	int indice = cli_buscarLibre(list, len);

	if(list != NULL && len > 0 && id != NULL)
	{
		if(indice >= 0)
		{
			if(!utn_getNombre(auxCliente.nombre,NOMBRE_LEN,"INGRESE NOMBRE: ","ERROR\n",2) &&
			   !utn_getApellido(auxCliente.apellido,APELLIDO_LEN,"INGRESE APELLIDO: ","ERROR\n",2) &&
			   !utn_getCuit(auxCliente.cuit,CUIT_LEN,"INGRESE CUIT: ","ERROR\n",2))
			{

				list[indice] = auxCliente;
				list[indice].idCliente = *id;
				list[indice].isEmpty = 0;
				*id += 1;
				printf("ALTA EXITOSA\n");
				retorno = 0;
				cli_printCliente(&list[indice]);
			}
			else
			{
				printf("NO PUDO DARSE DE ALTA\n");
			}
		}
		else
		{
			printf("NO HAY MAS LUGAR\n");
		}

	}

	return retorno;
}
/*
 * \brief pide al usuario que seleccion un cliente y lo modfica
 * \param array de clientes
 * \param longiud del aray de clientes
 * \return devuelve 0 si se pudo modificar y -1 si no
 * */
int cli_modificarCliente(Cliente* list, int len)
{
	int retorno = -1;
	int idClienteAModificar;
	int opcionModificar;
	char bufferChar[64];
	int indice;

	if(list != NULL && len > 0)
	{
		cli_printClientes(list,len);
		if(!utn_getNumero(&idClienteAModificar,"ELIJA EL CLIENTE A MODIFICAR: ","ERROR, NO EXISTE EL CLIENTE\n",1,21,2))
		{
			indice = cli_buscarClientePorId(list,len,idClienteAModificar);
			if(indice >= 0)
			{
				utn_getNumero(&opcionModificar,"\nELIJA UNA OPCION\n"
														  "1 - MODIFICAR NOMBRE\n"
									                      "2 - MODIFICAR APELLIDO\n"
									                      "3 - MODIFICAR CUIT\n"
									                      "4 - SALIR\n",
														  "OPCION INCORRECTA\n",
														   1,4,2);
				switch(opcionModificar)
				{
				case 1:
					if(!utn_getNombre(bufferChar,NOMBRE_LEN,"INGRESE NUEVO NOMBRE: ","ERROR, NO ES UN NOMBRE VALIDO",2)&&
					   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL NOMBRE? INGRESE S/N"))
					{
						strncpy(list[indice].nombre,bufferChar,NOMBRE_LEN);
						printf("NOMBRE MODIFICADO CON EXITO\n");
					}
					break;
				case 2:
					if(!utn_getApellido(bufferChar,APELLIDO_LEN,"INGRESE NUEVO APELLIDO: ","ERROR, NO ES UN APELLIDO VALIDO",2)&&
					   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL APELLIDO? INGRESE S/N"))
					{
						strncpy(list[indice].apellido,bufferChar,APELLIDO_LEN);
						printf("APELLIDO MODIFICADO CON EXITO\n");
					}
					break;
				case 3:
					if(!utn_getCuit(bufferChar,CUIT_LEN,"INGRESE NUEVO CUIT: ","ERROR, NO ES UN CUIT VALIDO",2)&&
					   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL CUIT? INGRESE S/N"))
					{
						strncpy(list[indice].cuit,bufferChar,CUIT_LEN);
						printf("CUIT MODIFICADO CON EXITO\n");
					}
					break;
				case 4:
					printf("OPERACION CANCELADA\n");
					break;
				}
				retorno = 0;

			}
			else
			{
				printf("EL ID INGRESADO NO EXISTE\n");
			}

		}
	}

	return retorno;
}
/*
 * \brief imprime un cliente activo por id en la pantalla
 * \param array de clientes
 * \param longitud del array de clientes
 * \param id a ser impreso
 * \return deuvle 0 si pudo imprimir o -1 si no lo encontro
 * */
int cli_printClienteById(Cliente* list, int len,int id)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == id)
			{
				cli_printCliente(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 * \brief permite cargar usuarios para prueba
 * \param array de clientes
 * \param longitud del array clientes
 * \param puntero a la direccion de memoria del id inicial
 * \param string con el nombre del cliente
 * \param string con el apellido del cliente
 * \param string con el cuit del cliente
 * \return devuelve 0 si se pudo cargar y -1 si no
 * */
int cli_altaForzadaArray(Cliente* array,int limite, int* id,char* nombre,char* apellido, char* cuit)

{
	int retorno = -1;
	int indice = cli_buscarLibre(array,limite);
	Cliente bufferCliente;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		    bufferCliente.idCliente = *id;
			strncpy(bufferCliente.nombre,nombre,NOMBRE_LEN);
			strncpy(bufferCliente.apellido,apellido,APELLIDO_LEN);
			strncpy(bufferCliente.cuit,cuit,CUIT_LEN);
			bufferCliente.isEmpty = 0;

			array[indice] = bufferCliente;
			*id+=1;
			retorno = 0;

	}
	return retorno;
}
/*
 * \brief verifia si hay clientes activos cargados y devuelve la cantidad
 * \param array de clientes
 * \param longitud del array de clientes
 * \return devuelve la cantidad de clientes activos o -1 si no hay
 * */
int cli_buscarClientesCargados(Cliente* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				if(retorno == -1)
				{
					retorno = 0;
				}
				retorno ++;
			}
		}
	}

	return retorno;
}

/**
 * \brief Ordenar el array de clientes por nombre y cuit
 * \param array Array de clientes
 * \param limite Limite del array de clientes
 * \return Retorna 0 si se pudo ordenar o -1 si no
 *
 */
int cli_ordenarPorNombreCuit(Cliente* list,int len)
{
	int retorno = -1;
	int flagSwap;
	int i;
	Cliente buffer;
	int auxiliarCmp;

	if(list != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<len-1;i++)
			{
				auxiliarCmp = strncmp(list[i].nombre,list[i+1].nombre,NOMBRE_LEN);
				if(auxiliarCmp > 0 || (auxiliarCmp == 0 &&  strncmp(list[i].cuit,list[i+1].cuit,CUIT_LEN) > 0 ))
				{
					flagSwap = 1;
					buffer = list[i];
					list[i] = list[i+1];
					list[i+1]=buffer;
					retorno = 0;
				}
			}
			len--;
		}while(flagSwap);
	}
	return retorno;
}
