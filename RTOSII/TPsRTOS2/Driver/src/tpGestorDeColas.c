/*
 * 	Includes de FreeRTOS
 */
#include "FreeRTOS.h"   					// Motor del SO
#include "FreeRTOSConfig.h"					// Configuracion del SO
#include "task.h"							// API de control de tareas y temporización
#include "semphr.h"							// API de sincronización (sem y mutex)
#include "queue.h"      					// API de colas

/*
 * 	Includes del TP
 */
#include "tpGestorDeColas.h"				// Archivo en donde estan todos los prototipos de funciones globales

/*
 * 	Defines de tamano de colas
 */
#define TAMANO_COLA_DRIVER_SERVICIO		102
#define TAMANO_COLA_SERVICIO_OPERACION 	5

/*
 * 	Hanlders de colas
 */
static xQueueHandle colaDriverToService;	// Cola Driver->Servicio
static xQueueHandle colaServiceToDriver;	// Cola Servicio->Driver
static xQueueHandle colaServiceToOpZero;	// Cola Servicio->Operacion 0
static xQueueHandle colaServiceToOpOne;		// Cola Servicio->Operacion 1
static xQueueHandle colaOpToService;		// Cola Operacion x->Servicio

/*
 * 	Handlers de mutexes
 */
static SemaphoreHandle_t mutexDriverToService; // Mutex que sincroniza el envio de datos del driver al servicio
static SemaphoreHandle_t mutexServiceToDriver; // Mutex que sincroniza el envio de datos del servicio al driver

/*
 *	Creacion de funcion de inicializacion del gestor
 *
 *	@param none
 *
 *	@return INIT_OK, no considera posibles errores de creacion
 *	@TODO: Agregar condiciones de error
 */

StateType_t initGestorDeColas(void) {
	colaDriverToService = xQueueCreate(TAMANO_COLA_DRIVER_SERVICIO,
			sizeof(char));
	colaServiceToDriver = xQueueCreate(TAMANO_COLA_DRIVER_SERVICIO,
			sizeof(char));
	colaServiceToOpZero = xQueueCreate(TAMANO_COLA_SERVICIO_OPERACION,
			sizeof(uint32_t*));
	colaServiceToOpOne = xQueueCreate(TAMANO_COLA_SERVICIO_OPERACION,
			sizeof(uint32_t*));
	colaOpToService = xQueueCreate(TAMANO_COLA_SERVICIO_OPERACION,
			sizeof(uint32_t*));
	mutexDriverToService = xSemaphoreCreateMutex();
	mutexServiceToDriver = xSemaphoreCreateMutex();

	return INIT_OK;
}

/*
 *	Funciones para saber si hay algun dato en la cola
 *
 *	@param none
 *
 *	@return numero de mensajes esperando en la cola
 *
 */

uint8_t messagesAvailableFromDriverToService(void) {
	return (uint8_t) (uxQueueMessagesWaiting(colaDriverToService));
}

uint8_t messagesAvailableFromServiceToDriver(void) {
	return (uint8_t) (uxQueueMessagesWaiting(colaServiceToDriver));
}

uint8_t messagesAvailableFromServiceToOpZero(void) {
	return (uint8_t) (uxQueueMessagesWaiting(colaServiceToOpZero));
}

uint8_t messagesAvailableFromServiceToOpOne(void) {
	return (uint8_t) (uxQueueMessagesWaiting(colaServiceToOpOne));
}

uint8_t messagesAvailableFromOpToService(void) {
	return (uint8_t) (uxQueueMessagesWaiting(colaOpToService));
}

/*
 *	Creacion de las funciones para recibir de las colas
 *
 *	@param recepcion: puntero al buffer donde se guardara lo que retorne la funcion
 *
 *	@return RECEIVE_OK si recibio correctamente, RECEIVE_ERROR si no
 */

StateType_t receiveFromDriverToService(char* recepcion) {
	if (xQueueReceive(colaDriverToService, recepcion, portMAX_DELAY) == pdTRUE) {
		return RECEIVE_OK;
	} else {
		return RECEIVE_ERROR;
	}
}

StateType_t receiveFromOpToService(void* recepcion) {
	if (xQueueReceive(colaOpToService, recepcion, portMAX_DELAY) == pdTRUE) {
		return RECEIVE_OK;
	} else {
		return RECEIVE_ERROR;
	}
}

StateType_t receiveFromServiceToOpZero(void* recepcion) {
	if (xQueueReceive(colaServiceToOpZero, recepcion, portMAX_DELAY) == pdTRUE) {
		return RECEIVE_OK;
	} else {
		return RECEIVE_ERROR;
	}
}

StateType_t receiveFromServiceToOpOne(void* recepcion) {
	if (xQueueReceive(colaServiceToOpOne, recepcion, portMAX_DELAY) == pdTRUE) {
		return RECEIVE_OK;
	} else {
		return RECEIVE_ERROR;
	}
}

StateType_t receiveFromServiceToDriver(char* recepcion) {
	if (xQueueReceive(colaServiceToDriver, recepcion, portMAX_DELAY) == pdTRUE) {
		return RECEIVE_OK;
	} else {
		return RECEIVE_ERROR;
	}
}

/*
 *	Creacion de las funciones para enviar datos entre tareas por las colas
 *
 *	@param envio: puntero que indica el dato a enviar
 *
 *	@return SEND_OK unica condicion de error considerada por el momento
 *	@TODO: Anadir condiciones de error
 */

StateType_t sendToServiceFromDriver(char* envio) {
	xQueueSend(colaDriverToService, envio, portMAX_DELAY);
	return SEND_OK;
}

StateType_t sendToServiceFromDriverISR(char* envio) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xQueueSendFromISR(colaDriverToService, envio, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	return SEND_OK;
}

StateType_t sendToOpZeroFromService(char* envio) {
	xQueueSend(colaServiceToOpZero, envio, portMAX_DELAY);
	return SEND_OK;
}

StateType_t sendToOpOneFromService(char* envio) {
	xQueueSend(colaServiceToOpOne, envio, portMAX_DELAY);
	return SEND_OK;
}

StateType_t sendToServiceFromOp(char* envio) {
	xQueueSend(colaDriverToService, envio, portMAX_DELAY);
	return SEND_OK;
}

StateType_t sendToDriverFromService(char* envio) {
	xQueueSend(colaServiceToDriver, envio, portMAX_DELAY);
	return SEND_OK;
}

/*
 *	Creacion de funciones para tomar o ceder los mutex
 *
 *	@param none
 *
 *	@return TAKE_OK cuando logra tomarlo, no considera mas opciones de error
 *	@return GIVE_OK cuando logra cederlo, no considera mas opciones de error
 *	@TODO: anadir condiciones de error
 */

StateType_t takeMutexDriverToService(void) {
	xSemaphoreTake(mutexDriverToService, portMAX_DELAY);
	return TAKE_OK;
}

StateType_t takeMutexDriverToServiceISR(void) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreTakeFromISR(mutexDriverToService, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	return SEND_OK;
}

StateType_t giveMutexDriverToService(void) {
	xSemaphoreGive(mutexDriverToService);
	return GIVE_OK;
}

StateType_t giveMutexDriverToServiceISR(void) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(mutexDriverToService, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	return SEND_OK;
}

StateType_t takeMutexServiceToDriver(void) {
	xSemaphoreTake(mutexServiceToDriver, portMAX_DELAY);
	return TAKE_OK;
}

StateType_t giveMutexServiceToDriver(void) {
	xSemaphoreGive(mutexServiceToDriver);
	return GIVE_OK;
}

