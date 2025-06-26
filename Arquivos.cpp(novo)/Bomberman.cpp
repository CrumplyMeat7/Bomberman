#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "Classes.hpp"
#include <math.h>
int faseAtual = 2;

// Declare inimigos e funções
extern std::vector<Inimigo> inimigos;
void gerarInimigos(mapa* mapa, player* jogador);
void atualizarInimigos(mapa* mapa);
void desenharInimigos();

int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Mini Bomberman");
    SetTargetFPS(60);

    player PLAYER;
    mapa MAPA;
    bomba BOMBA;
    menu MENU;

    //int faseAtual = 1;
    bool iniciouFase = false;
    bool jogoIniciado = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (MENU.escolhaMenu == 0) {
            MENU.desenhomenuInicial(&MENU);
            MENU.escolhamenuInicial(&MENU);

            switch (MENU.escolhaMenu) {
                case 1: // NOVO JOGO
                    faseAtual = 2;
                    PLAYER.vivo = true;
                    inimigos.clear();
                    if (!MAPA.mapaPersonalizado)
                        MAPA.criaFase(&MAPA);
                    gerarInimigos(&MAPA, &PLAYER);
                    iniciouFase = true;
                    jogoIniciado = true;
                    break;

                case 2: // CONTINUAR
                    if (!jogoIniciado) {
                        faseAtual = 1;
                        PLAYER.vivo = true;
                        inimigos.clear();
                        if (!MAPA.mapaPersonalizado)
                            MAPA.criaFase(&MAPA);
                        gerarInimigos(&MAPA, &PLAYER);
                        iniciouFase = true;
                        jogoIniciado = true;
                    }
                    break;

                case 3: // CARREGAR MAPA
                    MAPA.carregaMapa(&MAPA);
                    break;

                case 4: // SAIR
                    exit(0);
                    break;
            }
        } else {
            if (!PLAYER.vivo) {
                MENU.gameover(&MENU, &PLAYER);
            } else {
                atualizarInimigos(&MAPA);

                if (!MAPA.mapaPersonalizado)
                    MAPA.criaFase(&MAPA);

                MAPA.criaMapaBomba(&MAPA);
                PLAYER.updateposplayer(&PLAYER, &MAPA);
                PLAYER.updatecentroplayer();
                BOMBA.lancaBomba(&PLAYER);
                BOMBA.explodebomba(&PLAYER);
                BOMBA.explodemapa(&PLAYER, &MAPA);
                BOMBA.limpaBombas();
                MAPA.criaItens(&MAPA);
                MAPA.colisaoItens(&PLAYER);
                BOMBA.morteplayer(&PLAYER, &MAPA);

                MAPA.desenhoMapa(&MAPA);
                BOMBA.desenhabomba(&PLAYER, &MAPA);
                MAPA.HUD(&PLAYER);
                MAPA.desenhaItens(&MAPA);
                PLAYER.desenhoplayer();
                desenharInimigos();
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
