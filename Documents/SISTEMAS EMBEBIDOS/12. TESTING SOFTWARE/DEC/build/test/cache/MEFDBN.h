#include "sapi.h"
typedef enum {

 BUTTON_UP, BUTTONPRESSED, BUTTONDOWN, BUTTONRELEASED

} fsmDbnstate_t;





typedef struct {

 gpioMap_t button;

 fsmDbnstate_t state;

 delay_t delay;

} Dbndata_t;





void buttonreleased(gpioMap_t);

void buttonpressed(gpioMap_t);

void fsmDbnInit(Dbndata_t *, gpioMap_t);

void fsmDbnUpdate(Dbndata_t *);





bool_t getkeystate(gpioMap_t key);
