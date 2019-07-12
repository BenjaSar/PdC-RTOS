#include "tpGestorDeColas.h"
#include "tpOperacion.h"
#include "FreeRTOS.h"   		// Motor del SO
#include "task.h"				// API de control de tareas y temporización
#include "sapi.h"



void prototipoOperacion(void* taskParameterPointer) {
	char * recepcionCola;		/* Recepciona el puntero enviado por el servicio */
	while (TRUE) {
		/*Compruebo si existen mensajes provenientes del servicio*/
		if (messagesAvailableFromServiceToOpZero() > 0) {		/*Recepción OpZero*/
			if (receiveFromServiceToOpZero(&recepcionCola)){
				// Implementacion de la tarea TaskOpZero LowerCase to UpperCase
				while(*recepcionCola!='\0'){
					*recepcionCola = (*recepcionCola >= 'a' && *recepcionCola <= 'z') ? *recepcionCola-32 : *recepcionCola;
					recepcionCola++;
				}
				printf("\nOperacion One convirtiendo en letras mayusculas = %c\r\n",recepcionCola);
			}
			printf("\nOperacion recibio datos OpZero, procesando...");
			printf("\nOpZero: %p", recepcionCola);
			vTaskDelay(100);
			printf("\nDatos procesados OpZero, reenviando a servicio\r\n");
			sendToOpZeroFromService(recepcionCola);
		}

		else if (messagesAvailableFromServiceToOpOne() > 0) {	/*Recepción OpOne*/

			printf("\nOperacion recibio datos OpOne, procesando...");
			printf("\nOpOne: %p", recepcionCola);

			if (receiveFromServiceToOpOne(&recepcionCola)){

				// Implementacion de la tarea TaskOpZero UpperCase to LowerCase
				while(*recepcionCola!='\0'){
					*recepcionCola = (*recepcionCola >= 'A' && *recepcionCola <= 'Z') ? *recepcionCola+32 : *recepcionCola;
					recepcionCola++;				}

			}
			printf("\nOperacion One convirtiendo en letras mayusculas = %c\r\n",recepcionCola);
			vTaskDelay(100);
			printf("\nDatos procesados, reenviando a servicio\r\n");
			sendToOpZeroFromService(recepcionCola);
		}
		gpioToggle(LEDR);
		vTaskDelay(200);
	}
}
