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
                MAPA.carregaMapa(&MAPA);
                break;
            case 4:
                //SAIR DO JOGO
                exit(0);
                break;
            }
        } else {
            //GAME OVER
            if(!PLAYER.vivo) {
                MENU.gameover(&MENU, &PLAYER);
                MENU.escolhagameover(&MENU);
                switch (MENU.escolhaGameover)  // Verifica a opção do menu
                {
                    case 1:
                        //TENTAR NOVAMENTE
                        break;
                    case 2:
                        //SALVAR E SAIR
                        MENU.escolhaMenu = 0; // Volta para o menu inicial
                        MENU.opcaoMenu = 1; // Reseta a opção do menu
                        PLAYER.vivo = true; // Reseta o estado do player
                        break;
                }

            }else{

            //LOGICA
            if (!MAPA.mapaPersonalizado) { // Só cria fase se não for mapa personalizado
                MAPA.criaFase(&MAPA);
            }
            MAPA.criaMapaBomba(&MAPA);
            PLAYER.updateposplayer(&PLAYER, &MAPA);
            PLAYER.updatecentroplayer();
            BOMBA.lancaBomba(&PLAYER);
            BOMBA.explodebomba(&PLAYER);
            BOMBA.explodemapa(&PLAYER, &MAPA);
            BOMBA.limpaBombas();
            MAPA.criaItens(&MAPA);
            MAPA.colisaoItens(&PLAYER);
            MAPA.colisaoSaida(&PLAYER, &MAPA);
            BOMBA.morteplayer(&PLAYER, &MAPA);


            //DESENHO
            MAPA.desenhoMapa(&MAPA);
            BOMBA.desenhabomba(&PLAYER, &MAPA);
            
            MAPA.HUD(&PLAYER, &MAPA);
            MAPA.desenhaItens(&MAPA);
            PLAYER.desenhoplayer();
            MAPA.desenhaSaida(&MAPA);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}