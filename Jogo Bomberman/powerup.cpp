#include "Classes.hpp"
#include <raylib.h>

void upgradePowerup(player &PLAYER, powerup &POWERUP) {
    if (POWERUP.tipoPowerup == 1) { // Upgrade de bombas
        PLAYER.numeroBombas = PLAYER.numeroBombas + 1 ;
    } else if (POWERUP.tipoPowerup == 2) { // Upgrade de alcance
        PLAYER.alcance = PLAYER.alcance + 1;
    } else if (POWERUP.tipoPowerup == 3) { // Upgrade de velocidade
        PLAYER.velplayer = PLAYER.velplayer + 0.5f;
    }
}