
#include "unity.h"

#include <stdbool.h>
#include <mock_MEFDBN.h>
#include <mock_MEFDEC.h>
#include <mock_sapi.h>




/**- Estado Inicial Init,  estado measured value sino estado Idle
   - En measured value, lectura sensor  y mensaje
   - En estado Idle, si  tecla == 1 vuelvo al Init
   - En estado Mensaje, si tecla == 0, vuelvo  a idle, sino paso a estado de medicion
   - Estado por defecto Init
*/

void test_init(void){
	gpioMap_t (tecla);
	DataDEC_t state;
	uint8_t lecturasensor;

	fsmDECInit (&state, tecla);
	fsmgetstate (&state);
	TEST_ASSERT_EQUAL (INIT, fsmgetstate(&state));
	getkeystate_IgnoreAndReturn (true);
	fsmDECUpdate(&state);
	TEST_ASSERT_EQUAL(MEASURED_VALUE, fsmgetstate(&state));
	fsmDECUpdate(&state);
	getkeystate_IgnoreAndReturn (false);
	TEST_ASSERT_EQUAL(IDLE, fsmgetstate(&state));

	//hacer mock de delay y canal de lctur...
}

void test_measuredvalue(void){
	gpioMap_t (tecla);
	DataDEC_t state;
	fsmgetstate (&state);
	getkeystate_IgnoreAndReturn (false);
	fsmDECUpdate(&state);

	TEST_ASSERT_EQUAL(IDLE, fsmgetstate(&state));
	
}

void test_idle(void){

	gpioMap_t (tecla);
	DataDEC_t state;
	fsmgetstate (&state);
	getkeystate_IgnoreAndReturn (false);
	fsmDECUpdate(&state);
	TEST_ASSERT_EQUAL(IDLE, fsmgetstate(&state));
}

void test_mss(void){

	gpioMap_t (tecla);
	DataDEC_t state;
	fsmgetstate (&state);
	getkeystate_IgnoreAndReturn (false);
	fsmDECUpdate(&state);
	TEST_ASSERT_EQUAL(IDLE, fsmgetstate(&state));

	getkeystate_IgnoreAndReturn (true);
	fsmDECUpdate(&state);
	TEST_ASSERT_EQUAL(MEASURED_VALUE, fsmgetstate(&state));

}


