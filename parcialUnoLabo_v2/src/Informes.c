/*
 * Informes.c
 *
 *  Created on: 9 may. 2020
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#include "Cliente.h"
#include "Publicacion.h"
#include "clientePublicacion.h"
#include "Informes.h"

#define CLI_LEN 100
#define PUB_LEN 1000

/*
 * \brief informa todas la publicaciones con los cuit del propietarios
 * \param array publicaciones
 * \param longitud del array publicaciones
 * \param array de clientes
 * \param longitud del array de clientes
 * \return devuelve 0 si pudo imprimir y -1 si no
 * */
int info_printPublicacionesConCuit(Publicacion* listPublicaciones, int lenPub,Cliente* listCliente,int lenCli)
{
	int retorno = -1;
	int i;

	if(listPublicaciones != NULL && lenPub > 0)
	{
		for(i=0; i<lenPub; i++)
		{
			if(listPublicaciones[i].isEmpty == 0)
			{
				printf("CUIT: %s ",listCliente[cli_buscarClientePorId(listCliente,lenCli,listPublicaciones[i].idCliente)].cuit);
				pub_printPublicacion(&listPublicaciones[i]);
				retorno = 0;
			}
		}
	}

	return retorno;
}
/*
 * \brief informa los clientes con sus publicaciones activas
 * \param array de clientes
 * \param longitud del array de clientes
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \return devuelve 0 si pudo imprimir y -1 si no
 * */
int info_clientesConPublicacionesActivas(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub)
{
	int retorno = -1;
	int i;

	if(listCli != NULL && lenCli > 0 &&  listPub != NULL && lenPub > 0)
	{
		for(i=0; i<lenCli; i++)
		{
			if(listCli[i].isEmpty == 0)
			{
				printf("\n----CLIENTE----\n");
				cli_printCliente(&listCli[i]);

				printf("----PUBLICACIONES----\n");
				pub_printPublicacionesActivasByIdCliente(listPub,lenPub,listCli[i].idCliente);
				printf("---------------------\n");
				retorno = 0;
			}
		}
	}

	return retorno;
}
/*
 * \brief informa el cliente con mas publicaciones activas
 * \param array de clientes
 * \param longitud del array clientes
 * \param array de publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si lo encontro y -1 si no pudo
 * */
int info_clientesConMasPublicacionesActivas(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub)
{
	int retorno = -1;
	int indiceClienteMax;
	int clienteMax;
	int contadorMaximoActivas=0;
	int i;
	int j;

	if(listCli != NULL && lenCli > 0 && listPub != NULL && lenPub > 0)
	{
		for(i=0; i<lenCli; i++)
		{
			if(listCli[i].isEmpty == 0)
			{
				for(j=0; j<lenPub; j++)
				{
					if(listPub[j].idCliente == listCli[i].idCliente &&
					   listPub[j].estado == 0 &&
					   listPub[j].isEmpty == 0)
					{
							contadorMaximoActivas++;
							retorno = 0;
					}
				}
				if(i==0)
				{
					clienteMax = contadorMaximoActivas;
					indiceClienteMax = i;
					contadorMaximoActivas = 0;
				}
				else if(contadorMaximoActivas > clienteMax)
				{
					clienteMax = contadorMaximoActivas;
					indiceClienteMax = i;
				}
				contadorMaximoActivas = 0;

			}

		}
		if(retorno == 0)
		{
			printf("EL CLIENTE CON MAS AVISOS ACTIVOS ES: \n");
			cli_printClienteById(listCli,lenCli,listCli[indiceClienteMax].idCliente);
			printf("CANTIDAD DE PUBLICACIONES: %d\n\n",clienteMax);
		}
	}

	return retorno;
}
/*
 * \brief informa el cliente con mas publicaciones pausadas
 * \param array de clientes
 * \param longitud del array clientes
 * \param array de publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si lo encontro y -1 si no pudo
 * */
int info_clientesConMasPublicacionesPausadas(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub)
{
	int retorno = -1;
	int indiceClienteMax;
	int clienteMax;
	int contadorMaximoPausadas = 0;
	int i;
	int j;

	if(listCli != NULL && lenCli > 0 && listPub != NULL && lenPub > 0)
	{
		for(i=0; i<lenCli; i++)
		{
			if(listCli[i].isEmpty == 0)
			{
				for(j=0; j<lenPub; j++)
				{
					if(listPub[j].idCliente == listCli[i].idCliente &&
					   listPub[j].estado == 1 &&
					   listPub[j].isEmpty == 0)
					{
						contadorMaximoPausadas++;
							retorno = 0;
					}
				}
				if(i==0)
				{
					clienteMax = contadorMaximoPausadas;
					indiceClienteMax = i;
					contadorMaximoPausadas = 0;
				}
				else if(contadorMaximoPausadas > clienteMax)
				{
					clienteMax = contadorMaximoPausadas;
					indiceClienteMax = i;
				}
				contadorMaximoPausadas = 0;
			}

		}
		if(retorno == 0)
		{
			printf("EL CLIENTE CON MAS PUBLICACIONES PAUSADAS ES: \n");
			cli_printClienteById(listCli,lenCli,listCli[indiceClienteMax].idCliente);
			printf("CANTIDAD DE PUBLICACIONES: %d\n\n",clienteMax);
		}
	}

	return retorno;
}
/*
 * \brief informa el cliente con mas publicaciones
 * \param array de clientes
 * \param longitud del array clientes
 * \param array de publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si lo encontro y -1 si no pudo
 * */
int info_clientesConMasPublicaciones(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub)
{
	int retorno = -1;
	int indiceClienteMax;
	int clienteMax;
	int contadorMaximo = 0;
	int i;
	int j;

	if(listCli != NULL && lenCli > 0 && listPub != NULL && lenPub > 0)
	{
		for(i=0; i<lenCli; i++)
		{
			if(listCli[i].isEmpty == 0)
			{
				for(j=0; j<lenPub; j++)
				{
					if(listPub[j].idCliente == listCli[i].idCliente &&
					   listPub[j].isEmpty == 0)
					{
						contadorMaximo++;
							retorno = 0;
					}
				}
				if(i==0)
				{
					clienteMax = contadorMaximo;
					indiceClienteMax = i;
					contadorMaximo = 0;
				}
				else if(contadorMaximo > clienteMax)
				{
					clienteMax = contadorMaximo;
					indiceClienteMax = i;
				}
				contadorMaximo = 0;
			}

		}
		if(retorno == 0)
		{
			printf("EL CLIENTE CON MAS PUBLICACIONES ES: \n");
			cli_printClienteById(listCli,lenCli,listCli[indiceClienteMax].idCliente);
			printf("CANTIDAD DE PUBLICACIONES: %d\n\n",clienteMax);
		}
	}

	return retorno;
}
/*
 * \brief informa la cantidad de publicaciones de un rubro, el rubro con mayor publicaciones y el rubro con menos publicaciones
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \return devuelve 0 si puedo realizar las acciones y -1 si no
 * */
int info_imprimirCantidadDeRubros(Publicacion* list,int len)
{

	int retorno = -1;
	int listaRubros[1000];
	int i;
	int j;
	int flagExisteRubro;
	int indiceRubro = 0;
	int rubroSeleccionado;
	int rubroMayorActivas;
	int contador = 0;
	int contadorMaxRubros = 0;
	int rubroConMenosActivas;
	int contadorrubroConMenosActivas = 0;

	if(list != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			flagExisteRubro = 0;
			if(list[i].isEmpty == 0)
			{
				for(j=0;j<indiceRubro;j++)
				{
					if(list[i].numeroDeRubro == listaRubros[j])
					{
						flagExisteRubro = 1;
						break;
					}
				}
				if(flagExisteRubro == 0)
				{
					listaRubros[indiceRubro] = list[i].numeroDeRubro;
					indiceRubro++;
				}
			}
		}
		if(!utn_getNumero(&rubroSeleccionado,"INGRESE UN NUMERO DE RUBRO: ","ERROR, DEBE SER UN NUMERO\n",0,1000,2))
		{
			for(i=0; i<len; i++)
			{
				if(list[i].estado == 0 && list[i].numeroDeRubro == rubroSeleccionado)
				{
					pub_printPublicacion(&list[i]);
				}
			}
		}
		for(i=0; i<indiceRubro; i++)
		{
			for(j=0; j<len; j++)
			{
				if(list[j].isEmpty == 0 && list[j].estado == 0 &&
				   list[j].numeroDeRubro == listaRubros[i])
				{
					contador++;
				}
			}
			if(i == 0)
			{

				rubroMayorActivas = i;
				contadorMaxRubros = contador;
				rubroConMenosActivas = i;
				contadorrubroConMenosActivas = contador;


			}
			else if(contador > contadorMaxRubros)
			{
				rubroMayorActivas = i;
				contadorMaxRubros = contador;
			}
			else if(contador < contadorrubroConMenosActivas)
			{
				rubroConMenosActivas = i;
				contadorrubroConMenosActivas = contador;
			}
			contador = 0;

		}
		if(contadorMaxRubros > 0)
		{
			printf("EL RUBRO CON MAYOR PUBLICACIONES ACTIVAS ES EL NUMERO: %d\n",listaRubros[rubroMayorActivas]);
			printf("EL RUBRO CON MENOR PUBLICACIONES ACTIVAS ES EL NUMERO: %d\n",listaRubros[rubroConMenosActivas]);
		}
		retorno = 0;

	}

	return retorno;
}

