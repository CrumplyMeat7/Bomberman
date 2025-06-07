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
        
        // Fazer uma função de update depois
        PLAYER.updateposplayer(&PLAYER);
        BOMBA.lancaBomba(&PLAYER);
        BOMBA.explodebomba(&PLAYER);
        
        
        
        BeginDrawing();
        ClearBackground(WHITE);
        MAPA.desenhoMapa();
        BOMBA.desenhabomba(&PLAYER);
        PLAYER.desenhoplayer();
        MAPA.HUD(&PLAYER);
        EndDrawing();
      

    }  

    CloseWindow();
    return 0;
}