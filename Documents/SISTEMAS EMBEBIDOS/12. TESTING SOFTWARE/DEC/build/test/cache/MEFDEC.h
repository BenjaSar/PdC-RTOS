#include "sapi.h"
typedef enum {

 INIT, MEASURED_VALUE, IDLE, MSS

} fsmDEC_t;





typedef struct {

    gpioMap_t AutomaticInterruptor;

    uint8_t temperature;

    fsmDEC_t state;

    bool_t sleep_idle;

    delay_t delaydec;

} DataDEC_t;





void fsmDECInit(DataDEC_t *, gpioMap_t);

void fsmDECUpdate(DataDEC_t *);

void DEC_Init(void);

bool_t _sleep_idle (DataDEC_t * pDEC_Update);

fsmDEC_t fsmgetstate(DataDEC_t * pDEC_state);
