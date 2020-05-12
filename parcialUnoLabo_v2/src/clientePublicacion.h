/*
 * clientePublicacion.h
 *
 *  Created on: 9 may. 2020
 *      Author: nico
 */

#ifndef CLIENTEPUBLICACION_H_
#define CLIENTEPUBLICACION_H_


int pub_altaPublicacion(Publicacion* listPub, int lenPub, int* idPub,Cliente* listCli,int lenCli);
int pub_modificarPublicacion(Publicacion* list, int len, Cliente* listaClientes, int lenClientes);

int cli_bajaCliente(Cliente* listCli, int lenCli,Publicacion* listPub, int lenPub);
int pub_pausarPublicacion(Publicacion* listPub,int lenPub,Cliente* listCli,int lenCli);
int pub_reanudaPublicacion(Publicacion* listPub,int lenPub,Cliente* listCli,int lenCli);

#endif /* CLIENTEPUBLICACION_H_ */
