// Includes de FreeRTOS
#include "FreeRTOS.h"   		// Motor del SO
#include "FreeRTOSConfig.h"		// Configuracion del SO
#include "task.h"				// API de control de tareas y temporización
#include "semphr.h"				// API de sincronización (sem y mutex)
#include "queue.h"      		// API de colas

// Include de sAPI
#include "sapi.h"
#include "board.h"

// Inclusion de archivos del TP
#include "tpGestorDeColas.h"
#include "tpDriver.h"
#include "tpService.h"
#include "tpOperacion.h"

int main(void) {
	uint8_t errorState = 0;
	boardConfig();
	// ASK: Puedo hacer que la unica funcion global de mi modulo driver
	// sea el task? y lo demas (configuracion) quede privado interno?
	printf("System Init\r\n");
	// Seguiria inicializacion de gestor de colas (comprobar errores de creacion)
	if (initGestorDeColas() != INIT_OK){
		errorState = 1;
	}

	xTaskCreate(prototipoServicio,             	// Funcion de la tarea a ejecutar
			(const char *) "Servicio", 			// Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, 		// Cantidad de stack de la tarea
			NULL,                          		// Parametros de tarea
			tskIDLE_PRIORITY + 1,         		// Prioridad de la tarea
			0                         			// Puntero a la tarea creada en el sistema
			);

	xTaskCreate(driverTask,             		// Funcion de la tarea a ejecutar
			(const char *) "Driver", 			// Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, 		// Cantidad de stack de la tarea
			NULL,                          		// Parametros de tarea
			tskIDLE_PRIORITY + 1,         		// Prioridad de la tarea
			0                         			// Puntero a la tarea creada en el sistema
			);

	xTaskCreate(prototipoOperacion,             // Funcion de la tarea a ejecutar
			(const char *) "Operacion", 		// Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, 		// Cantidad de stack de la tarea
			NULL,                          		// Parametros de tarea
			tskIDLE_PRIORITY + 1,         		// Prioridad de la tarea
			0                         			// Puntero a la tarea creada en el sistema
			);

	printf("Tasks Created\r\n");
	if (errorState == 0) {
		printf("Scheduler Starting\r\n");
		vTaskStartScheduler();
	} else {
		printf("Init Error.\r\n");
	}
	return 0;
}
