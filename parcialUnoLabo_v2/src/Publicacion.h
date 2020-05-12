/*
 * Publicacion.h
 *
 *  Created on: 9 may. 2020
 *      Author: nico
 */
//
#ifndef PUBLICACION_H_
#define PUBLICACION_H_

#include "Cliente.h"
typedef struct
{
	int idPublicacion;
	int idCliente;
	int numeroDeRubro;
	char texto[64];
	int estado;
	int isEmpty;

}Publicacion;

int pub_inicializar(Publicacion* list, int len);
int pub_buscarLibre(Publicacion* list, int len);
int pub_printPublicacion(Publicacion* pCliente);
int pub_printPublicaciones(Publicacion* list, int len);
int pub_buscarPublicacionPorId(Publicacion* list, int len, int id);
int pub_printPublicacionesByIdCliente(Publicacion* list, int len, int idCliente);
int pub_eliminarPublicacionesByIdCliente(Publicacion* list, int len, int idCliente);
int pub_eliminarPublicacion(Publicacion* listPub,int lenPub);
int pub_printPublicacionesActivas(Publicacion* list, int len);
int pub_printPublicacionesPausadas(Publicacion* list, int len);
int pub_altaForzadaArray(Publicacion* array,int limite, int* id,int idCliente,int rubro, char* texto,int estado);
int pub_printPublicacionesActivasByIdCliente(Publicacion* list, int len, int idCliente);
int pub_buscarPublicacionesCargadas(Publicacion* list, int len);


int pub_ordenarPorIdRubro(Publicacion* list,int len);

#endif /* PUBLICACION_H_ */
