/*=====[Nombre del modulo]=====================================================
 * Copyright YYYY Nombre completo del autor <author@mail.com>
 * All rights reserved.
 * Licencia: Texto de la licencia o al menos el nombre y un link
         (ejemplo: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Fecha de creacion: YYYY/MM/DD
 */

/*=====[Evitar inclusion multiple comienzo]==================================*/
#ifndef _MEFDBN_H_
#define _MEFDBN_H_
/*=====[Inclusiones de dependencias de funciones publicas]===================*/

//#include "../test/support/sapi.h"
#include <sapi.h>
#include <stdbool.h>


/*=====[C++ comienzo]========================================================*/
#ifdef __cplusplus
extern "C" {
#endif
/*=====[Macros de definicion de constantes publicas]=========================*/
/*=====[Macros estilo funcion publicas]======================================*/

/*=====[Definiciones de tipos de datos publicos]=============================*/

// Tipo de datos que renombra un tipo basico

// Tipo de datos de puntero a funcion

// Tipo de datos enumerado
typedef enum {
	BUTTON_UP, BUTTONPRESSED, BUTTONDOWN, BUTTONRELEASED
} fsmDbnstate_t;  //MEF para el antirrebote del interruptor

// Tipo de datos estructura, union o campo de bits
typedef struct {
	gpioMap_t button;
	fsmDbnstate_t state;
	delay_t delay;
} Dbndata_t;  // Estructura de datos para el antirrebote

/*=====[Prototipos de funciones publicas]====================================*/
void buttonreleased(gpioMap_t);
void buttonpressed(gpioMap_t);
void fsmDbnInit(Dbndata_t *, gpioMap_t); // Inicializacion MEF antirrebote
void fsmDbnUpdate(Dbndata_t *); // Actualizacion MEF antirrebote
//extern bool_t getkeystate(gpioMap_t key);
//fsmDEC_t fsmgetstate(DataDEC_t * pDEC_state);
bool_t getkeystate(gpioMap_t key);


/*=====[Prototipos de funciones publicas de interrupcion]====================*/

/*=====[C++ fin]=============================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/

#endif /* End _MEFDBN_H_*/
