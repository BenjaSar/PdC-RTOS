/*
 * TODO: anadir formato
 */

// Includes de sAPI
#include "sapi.h"
#include "board.h"

#ifndef _TPGESTORDECOLAS_H_
#define _TPGESTORDECOLAS_H_

/*
 * 	Definicion de tipo de datos para gestionar posibles errores
 */
typedef enum{
	QUEUE_INIT_ERROR,
	MUTEX_INIT_ERROR,
	INIT_OK,
	RECEIVE_ERROR,
	RECEIVE_OK,
	SEND_ERROR,
	SEND_OK,
	TAKE_ERROR,
	TAKE_OK,
	GIVE_ERROR,
	GIVE_OK
} StateType_t;


/*
 *
 * 	Declaracion de funciones globales, explicadas en el archivo .c
 *
 *
 */

StateType_t initGestorDeColas(void);

uint8_t messagesAvailableFromDriverToService(void);
uint8_t messagesAvailableFromServiceToDriver(void);
uint8_t messagesAvailableFromServiceToOpZero(void);
uint8_t messagesAvailableFromServiceToOpOne(void);
uint8_t messagesAvailableFromOpToService(void);


StateType_t receiveFromDriverToService(char* recepcion);	/*Recive Driver To Service*/
StateType_t receiveFromServiceToDriver(char* recepcion);	/*Service To Driver */

StateType_t receiveFromServiceToOpZero(void* recepcion);	/*Recive Service To OpZero*/
StateType_t receiveFromServiceToOpOne(void* recepcion);		/*Recive Service To OpOne */
StateType_t receiveFromOpToService(void* recepcion);		/*Recive Op To Service*/


StateType_t sendToServiceFromDriver(char* envio);
StateType_t sendToDriverFromService(char* envio);
StateType_t sendToServiceFromDriverISR(char* envio);

StateType_t sendToOpZeroFromService(char* envio);
StateType_t sendToOpOneFromService(char* envio);
StateType_t sendToServiceFromOp(char* envio);


StateType_t takeMutexDriverToService(void);
StateType_t takeMutexDriverToServiceISR(void);
StateType_t giveMutexDriverToService(void);
StateType_t giveMutexDriverToServiceISR(void);

StateType_t takeMutexServiceToDriver(void);
StateType_t giveMutexServiceToDriver(void);

#endif /* _TPGESTORDECOLAS_H_ */
