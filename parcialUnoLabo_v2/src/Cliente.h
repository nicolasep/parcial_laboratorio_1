/*
 * Cliente.h
 *
 *  Created on: 8 may. 2020
 *      Author: nico
 */


#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Publicacion.h"

typedef struct
{
	int idCliente;
	char nombre[64];
	char apellido[64];
	char cuit[22];
	int isEmpty;

}Cliente;


int cli_inicializar(Cliente* list, int len);
int cli_buscarLibre(Cliente* list, int len);
int cli_printCliente(Cliente* pCliente);
int cli_printClientes(Cliente* list, int len);
int cli_buscarClientePorId(Cliente* list, int len, int id);
int cli_altaCliente(Cliente* list, int len, int* id);
int cli_modificarCliente(Cliente* list, int len);
int cli_printClienteById(Cliente* list, int len,int id);
int cli_altaForzadaArray(Cliente* array,int limite, int* id,char* nombre,char* apellido, char* cuit);
int cli_buscarClientesCargados(Cliente* list, int len);


int cli_ordenarPorNombreCuit(Cliente* list,int len);

#endif /* CLIENTE_H_ */
