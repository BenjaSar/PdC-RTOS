#include "tpGestorDeColas.h"
#include "tpService.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"

void prototipoServicio(void* taskParameterPointer) {
	char recepcionCola;						/* Recepciona cada Char enviado por el driver */
	unsigned char buff[100] = {};			// Alocado dinamicamente por la tarea

	printf("\nPuntero del buffer: %p", &buff);
	uint8_t pos = 0;
	while (TRUE) {
		if (messagesAvailableFromDriverToService() > 0) {
			takeMutexDriverToService();
			while (messagesAvailableFromDriverToService() > 0) {
				receiveFromDriverToService(&recepcionCola);
				buff[pos++] = recepcionCola;
				printf("%c", recepcionCola);
			}
			char *pmem = buff;
			printf("\nComando %c", buff[1]);
			if(buff[1] == '0'){
				sendToOpZeroFromService(&pmem);
			}
			else if (buff[1] == '1'){
				sendToOpOneFromService(&pmem);
			}
			else {
				printf("\nError!");
			}
			printf("\nService Address Send: %p\n", &buff);
			giveMutexDriverToService();
			//printf("Servicio recibio datos, procesando\r\n");
			//vTaskDelay(100);
			//printf("Datos procesados, reenviando\r\n");

			/* Envío al driver*/
			//takeMutexServiceToDriver();
			//for (uint8_t i = 0; i < pos; i++){
			//	sendToDriverFromService(buff + i);
			//}
			//giveMutexServiceToDriver();
			pos = 0;
		}
		gpioToggle(LED3);
		vTaskDelay(200);
	}
}



