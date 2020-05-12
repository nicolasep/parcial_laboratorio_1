/*
 * utn.c
 *
 *  Created on: 18 abr. 2020
 *      Author: nico
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static int myGets(char* cadena, int longitud);
static int esChar(char letra);
static int getChar(char* pResultado);

static int esNumerica(char* cadena,int limite);
static int getInt(int* pResultado);


static int getNombre(char* pResultado, int longitud);
static int esNombre(char* cadena,int longitud);


static int validarNumeroFloat(char* cadena);
static int getFloat(float* pResultado);

static int validarCadena(char* cadena, int len);
static int getCadena(char* pResultado, int len);

static int getNombre(char* pResultado, int longitud);
static int esNombre(char* cadena,int longitud);

static int getDescripcion(char* pResultado, int longitud);
static int esDescripcion(char* cadena,int longitud);

static int getDni(char* pResultado, int longitud);


static int esTelefono(char* telefono);
static int getTelefono(char* pResultado);

static int esEmail(char* cadena);
static int getEmail(char* pResultado);

static int getDireccion(char* pResultado, int longitud);
static int esDireccion(char* cadena,int longitud);

static int esCuit(char* cuit);
static int getCuit(char* pResultado, int longitud);




/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un maximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamañio de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
 *
 */
static int myGets(char* cadena, int longitud)
{
	int retorno = -1;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 0;
			}
		}
	}

	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un caracter
 * \param letra Letra de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si es un caracter y 0 (falso) si no lo es
 *
 */
static int esChar(char letra)
{
	int retorno = 0;
	if((letra <'a' && letra >'z') || (letra <'A' && letra >'Z'))
	{
		retorno = -1;
	}

	return retorno;
}
/**
 * \brief Obtiene un string valido como caracter
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un caracter y -1 (ERROR) si no
 *
 */
static int getChar(char* pResultado)
{
	int retorno = -1;
	char buffer;

	if(pResultado != NULL)
	{
		if(myGets(&buffer,sizeof(buffer))==0 && esChar(buffer) == 0)
		{
			*pResultado = buffer;
			retorno = 0;
		}
	}

	return retorno;
}
/**
 * \brief Solicita un caracter al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param caracter minimo
 * \param caracter maximo
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo un caracter valido y -1 si no
 *
 */
int utn_getChar(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
	int retorno = -1;
	char bufferChar;
	do
	{
		printf("%s",mensaje);
		if(getChar(&bufferChar) == 0 &&
		   bufferChar >= minimo &&
		   bufferChar <= maximo)
		{
			retorno = 0;
			*pResultado = bufferChar;
			break;
		}
		printf("%s",mensajeError);
		reintentos--;
	}while(reintentos>=0);

	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un numero valido
 * \param cadena Cadena de caracteres a ser analizada
 * \param limite de la cadena
 * \return Retorna 1 (verdadero) si el numero es valido y 0 (falso) si no lo es
 *
 */
static int esNumerica(char* cadena,int limite)
{
	int retorno = 1;
	int i;

	for(i=0; i<limite && cadena[i] !='\0'; i++)
	{
		if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
		{
			continue;
		}
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
	}


	return retorno;
}
/**
 * \brief Obtiene un string valido como numero y si es correcto lo convierte a numero
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char bufferString[50];

	if(pResultado != NULL &&
	   !myGets(bufferString,sizeof(bufferString)) &&
	   esNumerica(bufferString,sizeof(bufferString)))
	{
		retorno = 0;
		*pResultado = atoi(bufferString);
	}

	return retorno;
}
/**
 * \brief Solicita un numero entero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param numero minimo
 * \param numero maximo
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo un numero entero y -1 si no
 *
 */

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	do
	{
		printf("%s",mensaje);
		if(getInt(&bufferInt) == 0 &&
		   bufferInt >= minimo &&
		   bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s",mensajeError);
		reintentos--;
	}while(reintentos>=0);

	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada sea un numero flotante
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si es un numero flotante y 0 (falso) si no lo es
 *
 */
static int validarNumeroFloat(char* cadena)
{
    int retorno=1;
	int i;
	int contadorPuntos=0;

    for(i=0;cadena[i]!='\0';i++)
    {
        if(cadena[i]<'0' || cadena[i]>'9')
        {

        	if(cadena[i]=='.')
        	{
        		contadorPuntos++;
        		if(contadorPuntos>1)
        		{

                    retorno=0;
                    break;
        		}
        	}
        	else
        	{

        		if(i==0)
        		{

        			if(cadena[i]!='+' && cadena[i]!='-')
        			{
        				retorno=0;
        				break;
        			}
        		}
        		else
        		{
        			retorno=0;
        			break;
        		}
        	}
        }
    }
    return retorno;
}

/**
 * \brief Obtiene un string valido como flotante
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 &&  validarNumeroFloat(buffer))
	{
		retorno = 0;
		*pResultado =(float) atof(buffer);
	}

	return retorno;
}
/**
 * \brief solicita un numero flotante al usuario y devuelve el resultado verificado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje a mostrar
 * \param mensaje de error a mostrar
 * \param numero minimo
 * \param numero maximo
 * \param cantidad de reintentos permitidos
 * \return retorna 0 si es un numero flotante y -1 si esta mal
 */
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;

		if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
		{
			do
			{
				printf("%s\n",mensaje);

				if(!getFloat(&bufferFloat) && bufferFloat >= minimo && bufferFloat <= maximo)
				{
					*pResultado = bufferFloat;
					retorno = 0;
					break;
				}
				else
				{
					printf("%s",mensajeError);
					reintentos--;
				}
			}while(reintentos >= 0);


		}

		return retorno;
}
//cadenas
/**
 * \brief Verifica si la cadena ingresada es una cadena de texto valida
 * \param cadena Cadena de caracteres a ser analizada
 * \param longitud de la cadena
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int validarCadena(char* cadena, int len)
{
    int retorno= 1;
	int i;

    for(i=0;cadena[i]!='\0' && i<len;i++)
    {
      if((cadena[i]<'a' || cadena[i]>'z') && (cadena[i]<'A' || cadena[i]>'Z') &&
    	  cadena[i] != '.'  && cadena[i] != '-' && cadena[i] != '@' && cadena[i] != ' ' &&
		  cadena[i] != ','  && cadena[i] != ':'  && (cadena[i] < '0' || cadena[i] > '9')  )
      {
    	  retorno = 0;
    	  break;
      }
    }
    return retorno;
}
/**
 * \brief Obtiene un string valido como cadena de texto
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud de la cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena de texto y -1 (ERROR) si no
 *
 */
static int getCadena(char* pResultado, int len)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 &&  validarCadena(buffer,len))
	    {
		retorno = 0;
		strncpy(pResultado,buffer,len);
	    }
	}


	return retorno;
}

/**
 * \brief solicita una cadena de texto al usuario y devuelve el resultado verificado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje a mostrar
 * \param mensaje de error a mostrar
 * \param cantidad de carecteres minimo
 * \param cantidad de carecteres maximo
 * \param cantidad de reintentos permitidos
 * \return retorna 0 si la cadena se valido correctamente y -1 si esta mal
 */
int utn_getCadena(char* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	char buffer[4096];

		if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
		{
			do
			{
				printf("%s\n",mensaje);

				if(getCadena(buffer,maximo)==0 && strnlen(buffer,sizeof(buffer)) >= minimo && strnlen(buffer,sizeof(buffer)) <= maximo)
				{
					strncpy(pResultado,buffer,maximo);
					retorno = 0;
					break;
				}
				else
				{
					printf("%s",mensajeError);
					reintentos--;
				}
			}while(reintentos >= 0);


		}

		return retorno;
}
/**
 * \brief Obtiene un string valido como nombre
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un nombre y -1 (ERROR) si no
 *
 */
static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	myGets(buffer,sizeof(buffer))==0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita un nombre al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo un nombre y -1 si no
 *
 */
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getNombre(bufferString,sizeof(bufferString)) == 0 &&
		   strnlen(bufferString,sizeof(bufferString)) < longitud &&
		   strnlen(bufferString,sizeof(bufferString)) > 0)
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief Solicita un apellido al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo un apellido y -1 si no
 *
 */
int utn_getApellido(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getNombre(bufferString,sizeof(bufferString)) == 0 &&
		   strnlen(bufferString,sizeof(bufferString)) < longitud &&
		   strnlen(bufferString,sizeof(bufferString)) > 0)
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como descripcion
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene una descripcion y -1 (ERROR) si no
 *
 */
static int getDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(myGets(buffer,sizeof(buffer))==0 &&
    		esDescripcion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita una descripcion al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo una descripcion y -1 si no
 *
 */
int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDescripcion(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}


/**
 * \brief Obtiene un string valido como DNI
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un dni y -1 (ERROR) si no
 *
 */
static int getDni(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(myGets(buffer,sizeof(buffer))==0 &&
    		esNumerica(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Solicita un DNI al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo un dni y -1 si no
 *
 */
int utn_getDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDni(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

/**
 * \brief verifica si la cadena es un telefono valido
 * \param telefono Telefono a ser analizado
 * \return devuelve 0 si la cadena es un telefono y -1 si no lo es
 */
static int esTelefono(char* telefono)
{
	int retorno = 1;
	int contadorGuiones = 0;
	int i;

	for(i=0; telefono[i]!='\0' ; i++)
	{
		if(telefono[i]<'0' || telefono[i]>'9')
		{

			retorno = 0;
		}
		else
		{
			if(telefono[i] =='-')
			{
				contadorGuiones ++;
			}
		}
	}

	if(contadorGuiones<2)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}


	return retorno;

}
/**
 * \brief obtien una telefono y lo valida
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return devuelve 1 si la cadena es un telefono valido y 0 si no lo es
 */
static int getTelefono(char* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 &&  esTelefono(buffer))
	{
		retorno = 0;
		strncpy(pResultado,buffer,(sizeof(*pResultado)));
	}

	return retorno;
}
/**
 * \brief pide un telefono al usuario y devuelve el resultado validado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje a mostrar
 * \param mensaje de error a mostrar
 * \param cantidad de numero minimo
 * \param cantidad de numeros maximo
 * \param cantidad de reintentos aceptados
 * \return devuelve 0 si es un telefono valido y -1 si no lo es
 */
int utn_getTelefono(char* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	char buffer[4096];

		if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
		{
			do
			{
				printf("%s\n",mensaje);

				if(getTelefono(buffer)==0 && sizeof(buffer) >= minimo && sizeof(buffer) <= maximo)
				{
					strncpy(pResultado,buffer,sizeof(*pResultado));
					retorno = 0;
					break;
				}
				else
				{
					printf("%s",mensajeError);
					reintentos--;
				}

			}while(reintentos >= 0);


		}

		return retorno;
}
//funciones email

/**
 * \brief analiza si la cadena es un email
 * \param cadena Cadena a ser analizada
 * \return devuelve 1 si es un email valido y 0 si no lo es
 */
static int esEmail(char* cadena)
{
	int retorno = 1;
	int i;
	int contadorArroba = 0;
	int contadorPuntos = 0;
	int tienePuntoCom = 0;

	if(cadena != NULL)
	{
		for(i=0; cadena[i] !='\0'; i++)
		{
			if(cadena[i]=='@')
			{
				contadorArroba++;
				if(contadorArroba > 1)
				{
					retorno = 0;
				}
			}
			else
			{
				if(cadena[i]=='.')
				{
					contadorPuntos++;
					if(contadorPuntos > 3)
					{
						retorno = 0;
					}
					else
					{
						if((cadena[i+1]=='c' && cadena[i+2]=='o' && cadena[i+3]=='m')||(cadena[i+1]=='C' && cadena[i+2]=='O' && cadena[i+3]=='M'))
						{
							tienePuntoCom++;
							if((tienePuntoCom > 1 || tienePuntoCom == 0) && contadorArroba == 1)
							{
								retorno = 0;
							}
						}
					}
				}
			}
		}
		if(tienePuntoCom == 0 || contadorArroba == 0)
		{
			retorno=0;
		}
	}

	return retorno;
}
/**
 * \brief obtiene un email y lo valida
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return devuelve 0 si es un email valido y -1 si no lo es
 */
static int getEmail(char* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 &&  esEmail(buffer))
	{
		retorno = 0;
		strncpy(pResultado,buffer,sizeof(*pResultado));
	}

	return retorno;
}
/**
 * \brief pide un email al usuario y lo devuelve validado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje a ser mostrado
 * \param mensaje de error a ser mostrado
 * \param cantidad de letras minima
 * \param cantidad de letras maxima
 * \param cantidad de reintentos permitidos
 * \return devuelve 0 si es un email valido y -1 si no lo es
 */
int utn_getEmail(char* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s\n",mensaje);

			if(getEmail(buffer) == 0 && strnlen(buffer,sizeof(buffer))>=minimo && strnlen(buffer,sizeof(buffer))<=maximo)
			{
				strncpy(pResultado,buffer,sizeof(*pResultado));
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}

		}while(reintentos >= 0);

	}

	return retorno;
}
////////////////////////////////////////
/**
 * \brief Obtiene un string valido como direccion
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene una direccion y -1 (ERROR) si no
 *
 */
static int getDireccion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(myGets(buffer,sizeof(buffer))==0 &&
    		esDireccion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es una direccion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */

static int esDireccion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i]!=' ')&&(cadena[i] < 'a' || cadena[i] > 'z') && (cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < '0' || cadena[i] > '9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita una direccion al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo una direccion y -1 si no
 *
 */
int utn_getDireccion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDireccion(bufferString,sizeof(bufferString)) == 0 &&
		   strnlen(bufferString,sizeof(bufferString)) < longitud &&
		   strnlen(bufferString,sizeof(bufferString)) > 0)
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

/**
 * \brief analiza si la cadena es un cuit
 * \param cadena Cadena a ser analizada
 * \return devuelve 1 si es un cuit valido y 0 si no lo es
 */
static int esCuit(char* cuit)
{
	int retorno = 1;
	int contadorGuiones = 0;
	int i;

	for(i=0; cuit[i]!='\0'; i++)
	{
		if(((cuit[i]<'0' || cuit[i]>'9') && cuit[i]!='-') || contadorGuiones > 2)
		{

			retorno = 0;
			break;
		}
		else
		{
			if(cuit[i] =='-')
			{
				contadorGuiones ++;
			}
		}
	}

	return retorno;

}
/**
 * \brief obtien una cuit y lo valida
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud maxima de la cadena
 * \return devuelve 1 si la cadena es un telefono valido y 0 si no lo es
 */
static int getCuit(char* pResultado, int longitud)
{
	int retorno = -1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 &&  esCuit(buffer) && strnlen(buffer,sizeof(buffer)) < longitud)
	{
		retorno = 0;
		strncpy(pResultado,buffer,longitud);
	}

	return retorno;
}
/**
 * \brief pide un cuit al usuario y devuelve el resultado validado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud maxima de la cadena
 * \param mensaje de error a mostrar
 * \param cantidad de reintentos aceptados
 * \return devuelve 0 si es un cuit valido y -1 si no lo es
 */
int utn_getCuit(char* pResultado,int longitud ,char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char buffer[4096];

		if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && longitud >= 0)
		{
			do
			{
				printf("%s\n",mensaje);

				if(getCuit(buffer,sizeof(buffer))==0 &&
				   strnlen(buffer,sizeof(buffer)) < longitud &&
				   strnlen(buffer,sizeof(buffer)) > 0)
				{
					strncpy(pResultado,buffer,longitud);
					retorno = 0;
					break;
				}
				else
				{
					printf("%s",mensajeError);
					reintentos--;
				}

			}while(reintentos >= 0);


		}

		return retorno;
}

/*
 * brief pide una letra de confirmacion al usuario y la valida
 * param mensaje a mostrar
 * return devuelve 0 si la letra es s o S y -1 si no lo es
 */
int utn_confirmacionAccionChar(char* mensaje)
{
	int retorno = -1;
	char confirmacion;
	if(mensaje != NULL)
	{
		printf("%s\n",mensaje);
	    if(!myGets(&confirmacion,sizeof(confirmacion)) && (confirmacion == 's' || confirmacion == 'S'))
	    {
	    	retorno = 0;
	    }
	}



	return retorno;
}
