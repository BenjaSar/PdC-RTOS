/*=====[Nombre del programa]====================================================
 * Copyright YYYY Nombre completo del autor <fsarmiento1805@gmail.com>
 * All rights reserved.
 * Licencia: Texto de la licencia o al menos el nombre y un link
 (ejemplo: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Fecha de creacion: YYYY/MM/DD
 */

/*=====[Inclusiones de dependencias de funciones]============================*/

#include "MEFDBN.h"
#include "MEFDEC.h"
#include <UART.h>

/*=====[Macros de definición de constantes privadas]=========================*/

/*=====[Definiciones de variables globales externas]=========================*/

/*=====[Definiciones de variables globales publicas]=========================*/

/*=====[Definiciones de variables globales privadas]=========================*/
static bool_t flag_TEC1;
static bool_t flag_TEC2;
static bool_t flag_TEC3;

/*=====[Funcion principal, punto de entrada al programa luego de encender]===*/

// Tipo de datos enumerado
// Tipo de datos estructua, union o campo de bits
void fsmDbnInit(Dbndata_t * structdatastate, gpioMap_t buttonumber) {
	structdatastate->button = buttonumber;
	structdatastate->state = BUTTON_UP;
	return;
}

void fsmDbnUpdate(Dbndata_t * ptrbuttonupdate) {

	switch (ptrbuttonupdate->state) {

	case BUTTON_UP:
		if (!gpioRead(ptrbuttonupdate->button))
			ptrbuttonupdate->state = BUTTONPRESSED;
		break;

	case BUTTONPRESSED:
		if (!ptrbuttonupdate->delay.running) {
			delayConfig(&ptrbuttonupdate->delay, DBNTIME);
			delayRead(&ptrbuttonupdate->delay);
		}

		if (delayRead(&ptrbuttonupdate->delay)) {
			if (!gpioRead(ptrbuttonupdate->button)) {
				buttonpressed(ptrbuttonupdate->button);
				ptrbuttonupdate->state = BUTTONDOWN;
			} else
				ptrbuttonupdate->state = BUTTON_UP;
		}

		break;

	case BUTTONDOWN:
		if (gpioRead(ptrbuttonupdate->button))
			ptrbuttonupdate->state = BUTTONRELEASED;
		break;

	case BUTTONRELEASED:
		if (gpioRead(ptrbuttonupdate->button))
			buttonreleased(ptrbuttonupdate->button);
		ptrbuttonupdate->state = BUTTONPRESSED;
		break;
	default:
		ptrbuttonupdate->state = BUTTON_UP;
		break;
	}

}

//*Funcion que indica cuando uno de los interruptores automaticos esta oprimido por las ruedas del tren*/
/* Los interruptores automaticos son representados por las teclas*/
void buttonpressed(gpioMap_t tecla) {
	switch (tecla) {
	case TEC1:
		flag_TEC1 = TRUE;
		gpioWrite(LEDB,ON);
		break;
	case TEC2:
		flag_TEC2 = TRUE;
		break;
	case TEC3:
		flag_TEC3 = TRUE;
		break;
	default:
		break;
	}
}

/*Funcion que indica cuando el ultimo vagon del tren termino de pasar*/
void buttonreleased(gpioMap_t tecla) {
	switch (tecla) {
	case TEC1:
		flag_TEC1 = FALSE;
		gpioWrite(LEDB, OFF);
		break;
	case TEC2:
		flag_TEC2 = FALSE;
		break;
	case TEC3:
		flag_TEC3 = FALSE;
		break;
	default:
		break;
	}
}

void fsmError(Dbndata_t * errorstate) {
	errorstate->state = BUTTON_UP;
}

bool_t getkeystate(gpioMap_t key) { //Devuelve estado del flag de la tecla correspondiente
	if (key == TEC1) {
		return flag_TEC1;
	} else if (key == TEC2) {
		return flag_TEC2;
	} else if (key == TEC3) {
		return flag_TEC3;
	}
	return 0;
}



