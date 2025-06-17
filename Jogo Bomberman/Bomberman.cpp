#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "Classes.hpp"
#include <math.h>

int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Mini Bomberman");
    SetTargetFPS(60);

    player PLAYER;
    mapa MAPA;
    bomba BOMBA;
    menu MENU;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (MENU.escolhaMenu == 0) {
            // Mostra o menu inicial
            MENU.desenhomenuInicial(&MENU);
            MENU.escolhamenuInicial(&MENU);
        } else {
            // Roda o jogo normalmente
            PLAYER.updateposplayer(&PLAYER, &MAPA);
            BOMBA.lancaBomba(&PLAYER);
            BOMBA.explodebomba(&PLAYER);

            MAPA.desenhoMapa();
            BOMBA.desenhabomba(&PLAYER);
            PLAYER.desenhoplayer();
            MAPA.HUD(&PLAYER);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}