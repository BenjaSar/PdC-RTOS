/*=====[Nombre del programa]====================================================
 * Copyright YYYY Nombre completo del autor <fsarmiento@mail.com>
 * All rights reserved.
 * Licencia: Texto de la licencia o al menos el nombre y un link
 (ejemplo: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Fecha de creacion: YYYY/MM/DD
 */

/*=====[Inclusiones de dependencias de funciones]============================*/
#include <sapi.h>
#include <UART.h>
#include <MEFDEC.h>
#include <MEFDBN.h>

/*=====[Macros de definición de constantes privadas]=========================*/

/*=====[Definiciones de variables globales externas]=========================*/

/*=====[Definiciones de variables globales publicas]=========================*/

/*=====[Definiciones de variables globales privadas]=========================*/
static Dbndata_t datakey1, datakey2, datakey3;
static DataDEC_t dataDEC_key1, dataDEC_key2, dataDEC_key3;
/*=====[Funcion principal, punto de entrada al programa luego de encender]===*/

int main(void) {
	// ----- Configuraciones -------------------------

	DEC_Init();

	/*Inicializar estado de las teclas y del dispositivo de medicion*/
	fsmDbnInit(&datakey1, TEC1);
	fsmDbnInit(&datakey2, TEC2);
	fsmDbnInit(&datakey3, TEC3);
	fsmDECInit(&dataDEC_key1, TEC1);
	fsmDECInit(&dataDEC_key2, TEC2);
	fsmDECInit(&dataDEC_key3, TEC3);
	// ----- Repetir por siempre ---------------------
	while (1) {
		fsmDbnUpdate(&datakey1);
		fsmDbnUpdate(&datakey2);
		fsmDbnUpdate(&datakey3);
		fsmDECUpdate(&dataDEC_key1);
		fsmDECUpdate(&dataDEC_key2);
		fsmDECUpdate(&dataDEC_key3);
		sleepUntilNextInterrupt();
		void tickerCallback( void );   // Before SysTick_Handler




	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontrolador y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
