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
    
    while (!WindowShouldClose())
    {
        PLAYER.updateposplayer(&PLAYER.posplayer.x, &PLAYER.posplayer.y);
        BOMBA.lancaBomba(PLAYER.posplayer.x, PLAYER.posplayer.y, PLAYER.playerSize);
        BOMBA.explodebomba();
        BeginDrawing();
        ClearBackground(WHITE);
        MAPA.desenhoMapa();
        BOMBA.desenhabomba(PLAYER.posplayer.x, PLAYER.posplayer.y, PLAYER.playerSize);
        PLAYER.desenhoplayer();
        EndDrawing();
      

    }  

    CloseWindow();
    return 0;
}


void update(void){



}