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
    bool jogoRodando = true;
    while (jogoRodando &&!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (MENU.escolhaMenu == 0) {
            // Mostra o menu inicial
            MENU.desenhomenuInicial(&MENU);
            MENU.escolhamenuInicial(&MENU);
            switch (MENU.escolhaMenu)  // Verifica a opção do menu
            {
            case 1:
                //NOVO JOGO
                break;
            
            case 2:
                //CONTINUAR JOGO
                break;
            case 3:
                //CARREGAR MAPA
                break;
            case 4:
                //SAIR DO JOGO
                jogoRodando = false;
                break;
            }
        } else {
            //LOGICA
            MAPA.criaFase(&MAPA);
            PLAYER.updateposplayer(&PLAYER, &MAPA);
            MAPA.updateMapa(&MAPA);
            BOMBA.lancaBomba(&PLAYER);
            BOMBA.explodebomba(&PLAYER);
            BOMBA.explodemapa(&PLAYER, &MAPA);
            MAPA.criaItens(&MAPA);


            //DESENHO
            MAPA.desenhoMapa(&MAPA);
            BOMBA.desenhabomba(&PLAYER, &MAPA);
            PLAYER.desenhoplayer();
            MAPA.HUD(&PLAYER);
            MAPA.desenhaItens(&MAPA);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}