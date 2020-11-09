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
#ifndef _MEFDEC_H_
#define _MEFDEC_H_
/*=====[Inclusiones de dependencias de funciones publicas]===================*/

#include <sapi.h>

/*=====[C++ comienzo]========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Macros de definicion de constantes publicas]=========================*/
#define Vumbral 1000
#define measuretime 500
#define delayshowmss 2000
/*=====[Macros estilo funcion publicas]======================================*/

/*=====[Definiciones de tipos de datos publicos]=============================*/

// Tipo de datos que renombra un tipo basico
// Tipo de datos de puntero a funcion
// Tipo de datos enumerado
typedef enum {
	INIT, MEASURED_VALUE, IDLE, MSS
} fsmDEC_t;  //MEF  detector de ejes calientes (DEC)

// Tipo de datos estructura, union o campo de bits
typedef struct {
    gpioMap_t AutomaticInterruptor; //Interruptor que indica la presencia del tren
    uint8_t temperature;      //Valor leido del ADC
    fsmDEC_t state;       // Estados del dispositivo DEC
    bool_t sleep_idle;    // Estado idle
    delay_t delaydec;        // Tiempo de medicion
} DataDEC_t; // Estructura de datos para estados DEC

/*=====[Prototipos de funciones publicas]====================================*/
void fsmDECInit(DataDEC_t *, gpioMap_t); //Inicializacion de la MEF del DEC
void fsmDECUpdate(DataDEC_t *); //Actualizacion de la MEF del DEC
void DEC_Init(void); //Initicializacion del Sistema
bool_t _sleep_idle (DataDEC_t * pDEC_Update);
fsmDEC_t fsmgetstate(DataDEC_t * pDEC_state);

/*=====[Prototipos de funciones publicas de interrupcion]====================*/

/*=====[C++ fin]=============================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Evitar inclusion multiple fin]=======================================*/

#endif  // End _MEFDEC_H_
