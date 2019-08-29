/*=====[Nombre del programa]====================================================
 * Copyright YYYY Nombre completo del autor <fsarmientor@mail.com>
 * All rights reserved.

 /*=====[Inclusiones de dependencias de funciones]============================*/

#include "MEFDBN.h"
#include "MEFDEC.h"
#include <UART.h>

/*=====[Macros de definición de constantes privadas]=========================*/

/*=====[Definiciones de variables globales externas]=========================*/

/*=====[Definiciones de variables globales publicas]=========================*/
/*=====[Definiciones de variables globales privadas]=========================*/

/*=====[Funcion principal, punto de entrada al programa luego de encender]===*/

// Tipo de datos enumerado
// Tipo de datos estructura, union o campo de bits
/* Inicializacion  del DEC*/
void fsmDECInit(DataDEC_t * structdata_DEC, gpioMap_t entrytrain) { //Entrytrain es simulado por la TEC1
	structdata_DEC->AutomaticInterruptor = entrytrain;
	structdata_DEC->state = INIT;
}

/* Actualizacion de los estados del DEC*/
void fsmDECUpdate(DataDEC_t * ptrDEC_Update) {
	static uint8_t lecturesensor;
	static bool_t statetec;
	statetec = getkeystate(ptrDEC_Update->AutomaticInterruptor);

	switch (ptrDEC_Update->state) {

	case INIT:

		if (statetec) { // Interruptor automatico ==1
			ptrDEC_Update->state = MEASURED_VALUE;
			gpioWrite(LED1, ON);

		} else {
			ptrDEC_Update->state = IDLE; // Interruptor automatico no detecta el tren
		}

		break;

		/*Una vez detectado el tren, la lectura de datos comienza*/
	case MEASURED_VALUE:

		if (!ptrDEC_Update->delaydec.running) {
			delayConfig(&ptrDEC_Update->delaydec, measuretime);
		}
		if (delayRead(&ptrDEC_Update->delaydec)) { //Leo el delay
			lecturesensor = adcRead(CH1);
			ptrDEC_Update->temperature = lecturesensor;
			ptrDEC_Update->state = MSS;
		}
		break;

	case IDLE:
		/*ptrDEC_Update->sleep_idle = TRUE;*/
		if (statetec) { // Si detecto el estado de las teclas, vuelvo a INIT
			ptrDEC_Update->state = INIT;
		}
		break;

	case MSS:
		uartSensorLecture(); 		// Valor de Temperatura enviado por la UART
		if (!statetec) { //Cuando la lectura de temperatura sea 0 ir al estado idle
			ptrDEC_Update->state = IDLE;}
			else {
				ptrDEC_Update->state = MEASURED_VALUE;
			}
		break;
	default:
		ptrDEC_Update->state = INIT; // Configuraciones del sistema
		DEC_Init();
		break;

	}
}

void DEC_Init(void) {

	boardConfig();
	uartConfig(UART_USB, 115200);
	adcConfig(ADC_ENABLE);
}


fsmDEC_t fsmgetstate(DataDEC_t * pDEC_state) {
	return pDEC_state-- > state;
}

