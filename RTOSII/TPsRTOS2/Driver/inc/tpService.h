/*
 * TODO: anadir formato
 */

#ifndef _TPSERVICE_H_
#define _TPSERVICE_H_

/*Indica el comando utilizado */
typedef enum {	OPZERO = 0, /* OpZero */
				OPONE  = 1 /*OpOne   */
			} Operacion_t;

typedef enum {	ENVIADO = 0,
				ESPERA  = 1
			} State_t;



void prototipoServicio(void* taskParameterPointer);
int validateOperacion(int* buff);

#endif /* _TPSERVICE_H_ */
