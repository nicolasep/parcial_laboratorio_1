/*
 * clientePublicacion.c
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

#define PUB_LEN 1000
#define CLI_LEN 100
#define CADENA_LEN 64
#define NOMBRE_LEN 64
#define APELLIDO_LEN 64
#define CUIT_LEN 21

/*
 * \brief pide los datos de una nueva publicacion al usuario, lo valida y lo carga en una posicion libre del array
 * \param array de publicaciones
 * \param longiud del array de publicaciones
 * \param puntero a la direcion de memoria del id inicial
 * \return devuelve 0 si pudo cargar y -1 si no pudo
 * */
int pub_altaPublicacion(Publicacion* listPub, int lenPub, int* idPub, Cliente* listCli,int lenCli)
{
	int retorno = -1;
	int idCliente;
	Publicacion auxPublicacion;

	int indice = pub_buscarLibre(listPub, lenPub);

	if(indice != -1)
	{
		if(listPub != NULL && lenPub > 0 && idPub != NULL && listCli != NULL && lenCli > 0)
		{
			cli_printClientes(listCli,lenCli);

			if(!utn_getNumero(&idCliente,"SELECCIONE EL NUMERO DE CLIENTE \n","ERROR, NO ES UN NUMERO VALIDO\n",0,CLI_LEN,2)&&
				cli_buscarClientePorId(listCli,lenCli,idCliente) >= 0 &&
			   !utn_getNumero(&auxPublicacion.numeroDeRubro,"INGRESE NUMERO DE RUBRO: ","ERROR\n",1,1000,2) &&
			   !utn_getCadena(auxPublicacion.texto,"INGRESE EL TEXTO DE LA PUBLICACION: ","ERROR\n",3,CADENA_LEN,2) )
			{

				listPub[indice] = auxPublicacion;
				listPub[indice].idCliente = idCliente;
				listPub[indice].estado = 0;
				listPub[indice].idPublicacion = *idPub;
				listPub[indice].isEmpty = 0;
				*idPub += 1;
				printf("ALTA EXITOSA\n");
				retorno = 0;
				pub_printPublicacion(&listPub[indice]);
			}
			else
			{
				printf("NO PUDO DARSE DE ALTA\n");
			}
		}
	}
	else
	{
		printf("NO HAY LUGAR DISPONIBLE\n");
	}


	return retorno;
}
/*
 * \brief pide al usuario que seleccion una publicacion y la modfica
 * \param array de publicaciones
 * \param longiud del aray de publicaciones
 * \return devuelve 0 si se pudo modificar y -1 si no
 * */
int pub_modificarPublicacion(Publicacion* listPublicacion, int lenPublicacion, Cliente* listaClientes, int lenClientes)
{
	int retorno = -1;
	int idPublicacionAModificar;
	int opcionModificar;
	int bufferInt;
	int indice;
	char bufferChar[CADENA_LEN];

	if(listPublicacion != NULL && lenPublicacion > 0 && listaClientes != NULL && lenClientes > 0)
	{
		pub_printPublicaciones(listPublicacion,lenPublicacion);
		if(!utn_getNumero(&idPublicacionAModificar,"ELIJA LA PUBLICACION A MODIFICAR: ","ERROR, NO EXISTE LA PUBLICACION\n",1,PUB_LEN,2)&&
		   (indice = pub_buscarPublicacionPorId(listPublicacion,lenPublicacion,idPublicacionAModificar)) >= 0 &&
		     !utn_getNumero(&opcionModificar,"\nELIJA UNA OPCION\n"
												"1 - MODIFICAR ID CLIENTE\n"
												"2 - MODIFICAR RUBRO\n"
												"3 - MODIFICAR TEXTO\n"
												"4 - ESTADO\n"
		    		                            "5 - SALIR\n",
												"OPCION INCORRECTA\n",1,5,2))
		{
			switch(opcionModificar)
			{
			case 1:
				if(!cli_printClientes(listaClientes,lenClientes) &&
				   !utn_getNumero(&bufferInt,"INGRESE EL NUEVO ID: ","ERROR, NO ES UN ID VALIDO\n",1,CLI_LEN,2)&&
				   cli_buscarClientePorId(listaClientes,lenClientes,bufferInt) >= 0 &&
				   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL CLIENTE DE LA PUBLICACION? INGRESE S/N"))
				{
					listPublicacion[indice].idCliente = bufferInt;
					printf("ID CLIENTE MODIFICADO CON EXITO\n");
				}
				break;
			case 2:
				if(!utn_getNumero(&bufferInt,"INGRESE NUEVO RUBRO: ","ERROR, NO ES UN RUBRO VALIDO\n",1,1000,2)&&
				   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL RUBRO? INGRESE S/N"))
				{
					listPublicacion[indice].numeroDeRubro = bufferInt;
					printf("RUBRO MODIFICADO CON EXITO\n");
				}
				break;
			case 3:
				if(!utn_getCadena(bufferChar,"INGRESE NUEVO TEXTO: ","ERROR, NO ES UN TEXTO VALIDO\n",3,CADENA_LEN,2)&&
				   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL TEXTO? INGRESE S/N"))
				{
					strncpy(listPublicacion[indice].texto,bufferChar,CADENA_LEN);
					printf("TEXTO MODIFICADO CON EXITO\n");
				}
				break;
			case 4:
				if(!utn_getNumero(&bufferInt,"INGRESE NUEVO ESTADO:\n0 - ACTIVO\n1 - PAUSADA\n","ERROR, NO ES UN ESTADO VALIDO\n",0,1,2)&&
				   !utn_confirmacionAccionChar("SEGURO QUE QUIERE CAMBIAR EL ESTADO? INGRESE S/N"))
				{
					listPublicacion[indice].estado = bufferInt;
					printf("ESTADO MODIFICADO CON EXITO\n");
				}
				break;
			case 5:
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

	return retorno;
}

/*
 * \brief pide al usuario un cliente y lo da de baja con sus pubicaciones
 * \param array de clientes
 * \param longitud del array de clientes
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \return devuelve 0 si lo pudo dar de baja y -1 si no pudo
 * */
int cli_bajaCliente(Cliente* listCli, int lenCli, Publicacion* listPub, int lenPub)
{
	int retorno = -1;
	int clienteEliminar;
	int indice;
	if(listCli != NULL && lenCli > 0 && listPub != NULL && lenPub > 0)
	{

		if(!cli_printClientes(listCli,lenCli))
		{
			if(!utn_getNumero(&clienteEliminar,"INGRESE EL ID DEL CLIENTE A ELIMINAR ","ERROR, NO ES NUMERO VALIDO",1,CLI_LEN,2)&&
			   (indice = cli_buscarClientePorId(listCli,lenCli,clienteEliminar)) >= 0)
			{

				if(pub_printPublicacionesByIdCliente(listPub,lenPub,clienteEliminar) == -1)
				{
					printf("EL CLIENTE NO TIENE PUBLICACIONES\n");
				}
				if(!utn_confirmacionAccionChar("SEGURO DESEA ELIMINAR EL CLIENTE: ELIJA S/N\n"))
				{
					listCli[indice].isEmpty = -1;
					pub_eliminarPublicacionesByIdCliente(listPub,lenPub,clienteEliminar);
					retorno = 0;
				}

			}
			else
			{
				printf("NO EL CLIENTES IGRESADO\n");
			}
		}
		else
		{
			printf("NO EXISTEN CLIENTES\n");
		}



	}

	return retorno;
}
/*
 * \brief pide al usuario que seleccione una publicacion activa, muesta los datos del cliente al que pertenece y le cambia el estado a pausada
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \param array de clientes
 * \param longitud del array clientes
 * \return devuelve 0 si pudo pausarla o -1 si no pudo
 * */
int pub_pausarPublicacion(Publicacion* listPub,int lenPub,Cliente* listCli,int lenCli)
{
	int retorno = -1;
	int idPublicacion;
	int indice;

	if(listPub != NULL && lenPub > 0 && listCli != NULL && lenCli > 0)
	{
		if(!pub_printPublicacionesActivas(listPub,lenPub))
		{
			if(!utn_getNumero(&idPublicacion,"SELECCION PUBLICACION\n","ERROR\n",0,PUB_LEN,2)&&
				(indice = pub_buscarPublicacionPorId(listPub,lenPub,idPublicacion) >= 0)&&
				listPub[indice].estado == 0)
			{

					cli_printClienteById(listCli,lenCli,listPub[pub_buscarPublicacionPorId(listPub,lenPub,idPublicacion)].idCliente);
					if(!utn_confirmacionAccionChar("SEGURO DESEA PAUSAR ESTA PUBLICACION? S/N\n"))
					{
						listPub[indice].estado = 1;
						retorno = 0;
						printf("LA PUBLICACION FUE PAUSADA CON EXITO\n");
					}


			}
			else
			{
				printf("ERROR, LA PUBLICACION NO EXISTE O ESTA PAUSADA\n");
			}
		}
		else
		{
			printf("ERROR, NO EXISTEN PUBLICACION ACTIVASS\n");
		}

	}


	return retorno;
}

/*
 * \brief pide al usuario que seleccione una publicacion pausada, muesta los datos del cliente al que pertenece y le cambia el estado a activa
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \param array de clientes
 * \param longitud del array clientes
 * \return devuelve 0 si pudo activarla o -1 si no pudo
 * */
int pub_reanudaPublicacion(Publicacion* listPub,int lenPub,Cliente* listCli,int lenCli)
{
	int retorno = -1;
	int idPublicacion;
	int indice;

	if(listPub != NULL && lenPub > 0 && listCli != NULL && lenCli > 0)
	{
		if(!pub_printPublicacionesPausadas(listPub,lenPub))
		{
			if(!utn_getNumero(&idPublicacion,"SELECCION PUBLICACION\n","ERROR\n",0,PUB_LEN,2)&&
				(indice = pub_buscarPublicacionPorId(listPub,lenPub,idPublicacion) >= 0)&&
				listPub[indice].estado == 1)
			{

					cli_printClienteById(listCli,lenCli,listPub[pub_buscarPublicacionPorId(listPub,lenPub,idPublicacion)].idCliente);
					if(!utn_confirmacionAccionChar("SEGURO DESEA REANUDAR ESTA PUBLICACION? S/N\n"))
					{
						listPub[indice].estado = 0;
						retorno = 0;
						printf("LA PUBLICACION FUE ACTIVADA CON EXITO\n");
					}


			}
			else
			{
				printf("ERROR, LA PUBLICACION NO EXISTE O ESTA ACTIVA\n");
			}
		}
		else
		{
			printf("ERROR, NO EXISTEN PUBLICACION PAUSADAS\n");
		}

	}


	return retorno;
}
