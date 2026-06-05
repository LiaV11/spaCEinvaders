#include "pico/stdlib.h"
#include <stdio.h>

/*
Pines GPIO
*/

#define BTN_MOVE  2
#define BTN_SHOOT 3

/*
Tiempos en milisegundos
*/

#define DOUBLE_TAP_MS 300
#define REPEAT_MS     80
#define DEBOUNCE_MS   30

/*
Maquina de estados para el boton de movimiento:
  IDLE         - esperando primer toque
  WAIT_DOUBLE  - primer toque detectado, esperando segundo
  MOVING_LEFT  - moviendo a la izquierda (boton sostenido)
  MOVING_RIGHT - moviendo a la derecha (boton sostenido)
*/

typedef enum {
    STATE_IDLE,
    STATE_WAIT_DOUBLE,
    STATE_MOVING_LEFT,
    STATE_MOVING_RIGHT
} MoveState;

int main() {

    stdio_init_all();

    /*
    Configurar botones con pull-up interno.
    El boton conecta el pin a GND, por lo tanto
    el pin lee LOW cuando esta presionado.
    */

    gpio_init(BTN_MOVE);
    gpio_set_dir(BTN_MOVE, GPIO_IN);
    gpio_pull_up(BTN_MOVE);

    gpio_init(BTN_SHOOT);
    gpio_set_dir(BTN_SHOOT, GPIO_IN);
    gpio_pull_up(BTN_SHOOT);

    MoveState state = STATE_IDLE;

    uint32_t firstPressTime = 0;
    uint32_t lastMoveSent   = 0;

    bool prevBtn1 = false;
    bool prevBtn2 = false;

    while (true) {

        uint32_t now = to_ms_since_boot(
            get_absolute_time()
        );

        /*
        Leer botones: activo en LOW por el pull-up,
        invertimos para que true = presionado.
        */

        bool btn1 = !gpio_get(BTN_MOVE);
        bool btn2 = !gpio_get(BTN_SHOOT);

        bool btn1Pressed  = btn1  && !prevBtn1;
        bool btn1Released = !btn1 && prevBtn1;
        bool btn2Pressed  = btn2  && !prevBtn2;

        /*
        Logica del boton de movimiento
        */

        switch (state) {

            case STATE_IDLE:

                if (btn1Pressed) {
                    state = STATE_WAIT_DOUBLE;
                    firstPressTime = now;
                }
                break;

            case STATE_WAIT_DOUBLE:

                if (btn1Pressed) {

                    /*
                    Segundo toque dentro de la ventana:
                    doble toque = mover a la DERECHA
                    */

                    putchar('R');
                    fflush(stdout);
                    lastMoveSent = now;
                    state = STATE_MOVING_RIGHT;
                }

                else if (now - firstPressTime > DOUBLE_TAP_MS) {

                    /*
                    Tiempo expirado sin segundo toque:
                    toque simple = mover a la IZQUIERDA
                    */

                    putchar('L');
                    fflush(stdout);
                    lastMoveSent = now;

                    state = btn1
                        ? STATE_MOVING_LEFT
                        : STATE_IDLE;
                }
                break;

            case STATE_MOVING_LEFT:

                if (!btn1) {

                    state = STATE_IDLE;

                } else if (now - lastMoveSent >= REPEAT_MS) {

                    putchar('L');
                    fflush(stdout);
                    lastMoveSent = now;
                }
                break;

            case STATE_MOVING_RIGHT:

                if (!btn1) {

                    state = STATE_IDLE;

                } else if (now - lastMoveSent >= REPEAT_MS) {

                    putchar('R');
                    fflush(stdout);
                    lastMoveSent = now;
                }
                break;
        }

        /*
        Boton de disparo: un toque = un disparo
        */

        if (btn2Pressed) {
            putchar('S');
            fflush(stdout);
        }

        prevBtn1 = btn1;
        prevBtn2 = btn2;

        sleep_ms(10);
    }

    return 0;
}
