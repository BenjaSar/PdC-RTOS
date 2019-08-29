
#include "sapi_datatypes.h"

/* Define Boolean Data Type */
bool_t delayRead( delay_t * delay );
typedef uint64_t tick_t;
typedef uint8_t bool_t;
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;





void delayConfig( delay_t * delay, tick_t duration );


