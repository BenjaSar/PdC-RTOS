// Includes de FreeRTOS
#include "FreeRTOS.h"   		// Motor del SO
#include "task.h"				// API de control de tareas y temporización
#include "semphr.h"				// API de sincronización (sem y mutex)

// Include de sAPI
#include "sapi.h"
#include "board.h"

#include "tpDriver.h"
#include "tpGestorDeColas.h"

#define BUFFER_SIZE 200
static char rxBuffer[BUFFER_SIZE];
static uint8_t bufferPos = 0;

static bool frameControl = FALSE;
static bool flagEnvioBuffer = FALSE;

void rxDone(void* args) {
	char c = uartRxRead(UART_USB);
	if (c == '{') {
		frameControl = TRUE;
		takeMutexDriverToServiceISR();
//		bufferPos = 0;	// Reinicia todo cuando vuelve a recibir un {
	}
	gpioToggle(LED1);
	// TODO: anadir control de overflow?

	if (frameControl) {
		rxBuffer[bufferPos++] = c;
		if (c == '}') {
			frameControl = FALSE;
			flagEnvioBuffer = TRUE;
			// ToDo: Poner en running la tarea?
		}
	}
}

void uartDriverInit(void) {
	uartConfig(UART_USB, 115200);
	uartCallbackSet(UART_USB, UART_RECEIVE, rxDone, NULL);
	uartInterrupt(UART_USB, TRUE);
}

void driverTask(void* taskParameterPointer) {
	char recepcionCola;
	uartDriverInit();

	while (TRUE) {
		if (flagEnvioBuffer == TRUE) {
			printf("Enviando trama al servicio\r\n");
			for (uint8_t i = 0; i < bufferPos; i++) {
				sendToServiceFromDriver(rxBuffer + i);
			}
			bufferPos = 0;
			giveMutexDriverToService();
			flagEnvioBuffer = FALSE;
		}

		if (messagesAvailableFromServiceToDriver() > 0) {
			takeMutexServiceToDriver();
			while (messagesAvailableFromServiceToDriver() > 0) {
				receiveFromServiceToDriver(&recepcionCola);
				printf("Driver: %c\n", recepcionCola);
			}
			giveMutexServiceToDriver();
		}

		gpioToggle(LED2);
		taskYIELD();
	}
}

