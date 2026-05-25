#include "alien.h"
#include "constants.h"

void initAliens(Alien aliens[],
                int count) {

    int startX = 90;
    int startY = 70;

    int spacingX = 70;
    int spacingY = 45;

    int index = 0;

    for (int row = 0;
         row < ALIEN_ROWS;
         row++) {

        for (int col = 0;
             col < ALIEN_COLS;
             col++) {

            aliens[index].x =
                startX + (col * spacingX);

            aliens[index].y =
                startY + (row * spacingY);

            /*
            SMALLER ALIENS
            */

            aliens[index].width = 38;
            aliens[index].height = 30;

            /*
            STATE
            */

            aliens[index].alive = 1;

            aliens[index].exploding = 0;

            aliens[index].explosionTimer = 0;

            /*
            TYPES ALIENS 
            */

            if (row == 0) {

                aliens[index].type = 0;
            }

            else if (row == 1 ||
                     row == 2) {

                aliens[index].type = 1;
            }

            else {

                aliens[index].type = 2;
            }

            index++;
        }
    }
}