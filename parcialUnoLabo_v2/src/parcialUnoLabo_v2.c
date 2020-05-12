/*
 ============================================================================
 Name        : parcialUnoLabo_v2.c
 Author      : nicolas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
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

int main(void) {

	setbuf(stdout,NULL);

	Cliente listaClientes[CLI_LEN];
	Publicacion listaPublicaciones[PUB_LEN];

	int opcion;

	int idInicialCliente = 1;
	int idInicialPublicacion = 1;




	if(!cli_inicializar(listaClientes,CLI_LEN)&&
	   !pub_inicializar(listaPublicaciones,PUB_LEN))
	{
		cli_altaForzadaArray(listaClientes,CLI_LEN,&idInicialCliente,"JOSE","NOGUEIRA","20-355422-1");
		cli_altaForzadaArray(listaClientes,CLI_LEN,&idInicialCliente,"NICOLAS","GOMEZ","21-352222-2");
		cli_altaForzadaArray(listaClientes,CLI_LEN,&idInicialCliente,"MATIAS","GIL","22-355422-3");
		cli_altaForzadaArray(listaClientes,CLI_LEN,&idInicialCliente,"ALEJANDRO","AVILA","23-355422-4");
		cli_altaForzadaArray(listaClientes,CLI_LEN,&idInicialCliente,"CRISTIAN","PEREZ","24-355422-5");

		pub_altaForzadaArray(listaPublicaciones,PUB_LEN,&idInicialPublicacion,2,7,"hoy apruebo",0);
		pub_altaForzadaArray(listaPublicaciones,PUB_LEN,&idInicialPublicacion,2,2,"cuarentena",0);
		pub_altaForzadaArray(listaPublicaciones,PUB_LEN,&idInicialPublicacion,3,7,"ruta",1);
		pub_altaForzadaArray(listaPublicaciones,PUB_LEN,&idInicialPublicacion,1,7,"viajar",0);
		pub_altaForzadaArray(listaPublicaciones,PUB_LEN,&idInicialPublicacion,2,2,"arriba alberto",0);
		pub_altaForzadaArray(listaPublicaciones,PUB_LEN,&idInicialPublicacion,2,9,"macri gato",0);

		do
		{
			utn_getNumero(&opcion,"INGRESE UNA OPCION\n"
								  "1 - ALTA CLIENTE\n"
								  "2 - MODIFICAR DATOS DEL CLIENTE\n"
								  "3 - BAJA DE CLIENTE\n"
								  "4 - PUBLICAR\n"
								  "5 - PAUSAR PUBLICACION\n"
								  "6 - REANUDAR PUBLICACION\n"
								  "7 - IMPRIMIR CLIENTES\n"
								  "8 - IMPRIMIR PUBLICACIONES\n"
								  "9 - INFORMAR CLIENTES\n"
								  "10 - INFORMAR PUBLICACIONES\n"
					              "PARA SALIR INGRESE 0\n"
								 ,"ERROR",0,10,2);
			switch(opcion)
			{
			case 1:
				cli_altaCliente(listaClientes,CLI_LEN,&idInicialCliente);
			    break;
			case 2:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) > 0)
				{
					cli_modificarCliente(listaClientes,CLI_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES CARGADOS\n");
				}
				break;
			case 3:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) >0)
				{
					cli_bajaCliente(listaClientes,CLI_LEN,listaPublicaciones,PUB_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES CARGADOS\n");
				}
				break;
			case 4:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) >0 )
				{
					pub_altaPublicacion(listaPublicaciones,PUB_LEN,&idInicialPublicacion,listaClientes,CLI_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES CARGADOS\n");
				}

				break;
			case 5:
				if(pub_buscarPublicacionesCargadas(listaPublicaciones,PUB_LEN) >0)
				{
					pub_pausarPublicacion(listaPublicaciones,PUB_LEN,listaClientes,CLI_LEN);
				}
				else
				{
					printf("NO HAY PUBLICACIONES CARGADAS\n");
				}

				break;
			case 6:
				if(pub_buscarPublicacionesCargadas(listaPublicaciones,PUB_LEN) >0)
				{
					pub_reanudaPublicacion(listaPublicaciones,PUB_LEN,listaClientes,CLI_LEN);
				}
				else
				{
					printf("NO HAY PUBLICACIONES CARGADAS\n");
				}

				break;
			case 7:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) >0)
				{
					info_clientesConPublicacionesActivas(listaClientes,CLI_LEN,listaPublicaciones,PUB_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES CARGADOS\n");
				}

				break;
			case 8:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) >0 &&
				   pub_buscarPublicacionesCargadas(listaPublicaciones,PUB_LEN) >0)
				{
					info_printPublicacionesConCuit(listaPublicaciones,PUB_LEN,listaClientes,CLI_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES O PUBLICACIONES CARGADAS\n");
				}

				break;
			case 9:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) >0 &&
				   pub_buscarPublicacionesCargadas(listaPublicaciones,PUB_LEN) >0)
				{
					info_clientesConMasPublicacionesActivas(listaClientes,CLI_LEN,listaPublicaciones,PUB_LEN);
					info_clientesConMasPublicacionesPausadas(listaClientes,CLI_LEN,listaPublicaciones,PUB_LEN);
					info_clientesConMasPublicaciones(listaClientes,CLI_LEN,listaPublicaciones,PUB_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES O PUBLICACIONES CARGADAS\n");
				}

				break;
			case 10:
				if(cli_buscarClientesCargados(listaClientes,CLI_LEN) >0 &&
				   pub_buscarPublicacionesCargadas(listaPublicaciones,PUB_LEN) >0)
				{
					info_imprimirCantidadDeRubros(listaPublicaciones,PUB_LEN);
				}
				else
				{
					printf("NO HAY CLIENTES O PUBLICACIONES CARGADAS\n");
				}

				break;
			}


		}while(opcion != 0);

	}
	else
	{
		printf("ERROR NO SE PUDO INICIALIZAR LOS ARRAYS\n");
	}



	return EXIT_SUCCESS;
}

