#include "build/temp/_test_DEC.c"
#include "mock_sapi.h"
#include "mock_MEFDEC.h"
#include "mock_MEFDBN.h"
#include "unity.h"




void test_init(void){

 gpioMap_t (tecla);

 DataDEC_t state;

 uint8_t lecturasensor;



 fsmDECInit (&state, tecla);

 fsmgetstate (&state);

 UnityAssertEqualNumber((UNITY_INT)((INIT)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

 getkeystate_CMockIgnoreAndReturn(27, 

1

);

 fsmDECUpdate(&state);

 UnityAssertEqualNumber((UNITY_INT)((MEASURED_VALUE)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

 fsmDECUpdate(&state);

 getkeystate_CMockIgnoreAndReturn(31, 

0

);

 UnityAssertEqualNumber((UNITY_INT)((IDLE)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);





}



void test_measuredvalue(void){

 gpioMap_t (tecla);

 DataDEC_t state;

 fsmgetstate (&state);

 getkeystate_CMockIgnoreAndReturn(41, 

0

);

 fsmDECUpdate(&state);



 UnityAssertEqualNumber((UNITY_INT)((IDLE)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);



}



void test_idle(void){



 gpioMap_t (tecla);

 DataDEC_t state;

 fsmgetstate (&state);

 getkeystate_CMockIgnoreAndReturn(53, 

0

);

 fsmDECUpdate(&state);

 UnityAssertEqualNumber((UNITY_INT)((IDLE)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

}



void test_mss(void){



 gpioMap_t (tecla);

 DataDEC_t state;

 fsmgetstate (&state);

 getkeystate_CMockIgnoreAndReturn(63, 

0

);

 fsmDECUpdate(&state);

 UnityAssertEqualNumber((UNITY_INT)((IDLE)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);



 getkeystate_CMockIgnoreAndReturn(67, 

1

);

 fsmDECUpdate(&state);

 UnityAssertEqualNumber((UNITY_INT)((MEASURED_VALUE)), (UNITY_INT)((fsmgetstate(&state))), (

((void *)0)

), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);



}
