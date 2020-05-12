/*
 * Informes.h
 *
 *  Created on: 9 may. 2020
 *      Author: nico
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int info_printPublicacionesConCuit(Publicacion* listPublicaciones, int lenPub,Cliente* listCliente,int lenCli);

int info_clientesConPublicacionesActivas(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub);

int info_clientesConMasPublicacionesActivas(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub);

int info_clientesConMasPublicacionesPausadas(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub);

int info_clientesConMasPublicaciones(Cliente* listCli,int lenCli,Publicacion* listPub,int lenPub);

int info_imprimirCantidadDeRubros(Publicacion* list,int len);

#endif /* INFORMES_H_ */
