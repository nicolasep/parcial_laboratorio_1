/*
 * Publicacion.c
 *
 *  Created on: 9 may. 2020
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Publicacion.h"
#include "Cliente.h"

#define PUB_LEN 1000
#define CLI_LEN 100
#define CADENA_LEN 64
#define NOMBRE_LEN 64
#define APELLIDO_LEN 64
#define CUIT_LEN 21

static const char TXT_ESTADOS[2][8]={"ACTIVA","PAUSADA"};

/*
 * \brief inicializa el array de publicaciones cambiandole el isEmpy 1
 * \param lista de publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si fue un exito y -1 si no
 * */
int pub_inicializar(Publicacion* list, int len)
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
 * \brief busca una posicion libre en el array de publicaciones y la devuelve
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \return devuelve la primera posicion libre o -1 si no enuentra
 * */
int pub_buscarLibre(Publicacion* list, int len)
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
 * \brief imprime un publicacion por pantalla
 * \param puntero a la direccion de memoria del elemento
 * \return devuelve 0 si pudo imprir y -1 si no encontro
 * */
int pub_printPublicacion(Publicacion* pPublicacion)
{
	int retorno = -1;
	if(pPublicacion != NULL)
	{
		printf("ID PUBLICACION: %d - ID CLIENTE: %d - NUMERO DE RUBRO: %d - TEXTO: %15s - ESTADO: %5s\n",pPublicacion->idPublicacion,pPublicacion->idCliente,pPublicacion->numeroDeRubro,pPublicacion->texto,TXT_ESTADOS[pPublicacion->estado]);
		retorno = 0;
	}

	return retorno;
}
/*
 * \brief imprime la lista de publicaciones activos por pantalla
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \return devuelve 0 si pudo imprimir y -1 si no pudo
 * */
int pub_printPublicaciones(Publicacion* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				pub_printPublicacion(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 *  \brief busca un pubicacion por ID y devuelve su posicion en el array
 *  \param array de pubicaciones
 *  \param longitud del array de pubicaciones
 *  \param id a ser buscado
 *  \return devuelve el lugar del array de la pubicacion o -1 si no lo encuentra
 * */
int pub_buscarPublicacionPorId(Publicacion* list, int len, int id)
{
	int retorno = -1;
	int i;
	if(list != NULL && len > 0 && id > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idPublicacion == id)
			{
				retorno = i;

				break;
			}
		}
	}

	return retorno;
}
/*
 * \brief imprime por parntalla las publicaciones de un ciente
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \param id del cliente a buscar
 * \return devuelve 0 si pudo mostrar y -1 si no
 * */
int pub_printPublicacionesByIdCliente(Publicacion* list, int len, int idCliente)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == idCliente)
			{
				pub_printPublicacion(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 * \brief elimina las publicaciones de un cliente ingresado
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \param id del cliente buscado
 * \return devuelve 0 si pudo borrar y -1 si no
 * */
int pub_eliminarPublicacionesByIdCliente(Publicacion* list, int len, int idCliente)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == idCliente)
			{
				list[i].isEmpty = -1;
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 * \brief pide al usauario que ingrese el id de una publicacion y la elimina
 * \param array de publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si pudo eliminar y -1 si no
 * */
int pub_eliminarPublicacion(Publicacion* listPub,int lenPub)
{
	int retorno = -1;
	int idPublicacion;
	int indice;

	if(listPub != NULL && lenPub > 0)
	{

		if(!pub_printPublicaciones(listPub,lenPub) &&
		   !utn_getNumero(&idPublicacion,"SELECCION PUBLICACION\n","ERROR\n",1,PUB_LEN,2)&&
		   (indice = pub_buscarPublicacionPorId(listPub,lenPub,idPublicacion)) >= 0 &&
		   !pub_printPublicacion(&listPub[indice]) &&
		   !utn_confirmacionAccionChar("SEGURO DESEA ELIMINAR ESTA PUBLICACION? S/N\n"))
		{
			listPub[indice].isEmpty = -1;
			retorno = 0;
			printf("PUBLICACION ELIMINADA CON EXITO\n");
		}
	}
	return retorno;
}
/*
 * \brief imprime por pantalla todas las publicaciones activas
 * \param array publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si pudo imprimir y -1 si no
 * */
int pub_printPublicacionesActivas(Publicacion* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].estado == 0)
			{
				pub_printPublicacion(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 * \brief imprime por pantalla todas las publicaciones pausadas
 * \param array de publicaciones
 * \param longitud del array publicaciones
 * \return devuelve 0 si pudo imprimir y -1 si no pudo
 * */
int pub_printPublicacionesPausadas(Publicacion* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].estado == 1)
			{
				pub_printPublicacion(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 * \brief imprime por pantalla las publicaciones activas de un cliente
 * \param array publicaciones
 * \param longitud del array publicaciones
 * \param id del cliente a buscar
 * \return devuelve 0 si pudo imprimir y -1 si no pudo
 * */
int pub_printPublicacionesActivasByIdCliente(Publicacion* list, int len, int idCliente)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == idCliente && list[i].estado == 0)
			{
				pub_printPublicacion(&list[i]);
				retorno = 0;
			}
		}

	}

	return retorno;
}
/*
 * \brief permite cargar publicaciones manualmente para prueba
 * \param array de publicaciones
 * \param longitud del array publicaciones
 * \param puntero al espacio de memoria del id inicial
 * \param id cliente a cargar
 * \param rubro a cargar
 * \param string a cargar
 * \param estado a cargar
 * \return devuelve 0 si lo pudo cargar y -1 si no pudo
 * */
int pub_altaForzadaArray(Publicacion* array,int limite, int* id,int idCliente,int rubro, char* texto,int estado)

{
	int retorno = -1;
	int indice = pub_buscarLibre(array,limite);
	Publicacion bufferPublicacion;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		bufferPublicacion.idPublicacion = *id;
		bufferPublicacion.idCliente = idCliente;
		bufferPublicacion.numeroDeRubro = rubro;
		strncpy(bufferPublicacion.texto,texto,CADENA_LEN);
		bufferPublicacion.estado = estado;
		bufferPublicacion.isEmpty = 0;
		array[indice] = bufferPublicacion;
		*id += 1;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief verifia si hay publicaciones activos cargados y devuelve la cantidad
 * \param array de publicaciones
 * \param longitud del array de publicaciones
 * \return devuelve la cantidad de publicaciones activas o -1 si no hay
 * */
int pub_buscarPublicacionesCargadas(Publicacion* list, int len)
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
				retorno++;
			}
		}
	}

	return retorno;
}
/**
 * \brief Ordenar el array de publicaciones por id y rubro
 * \param array Array de publicaciones
 * \param limite Limite del array de publicaciones
 * \return Retorna 0 si se pudo ordenar o -1 si no
 *
 */
int pub_ordenarPorIdRubro(Publicacion* list,int len)
{
	int retorno = -1;
	int flagSwap;
	int i;
	Publicacion buffer;

	if(list != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<len-1;i++)
			{
				if((list[i].idCliente > list[i+1].idCliente) ||
				  (list[i].idCliente == list[i+1].idCliente && list[i].numeroDeRubro > list[i+1].numeroDeRubro))
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

