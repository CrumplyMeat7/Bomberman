#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "Classes.hpp"
#include <math.h>

// Declare inimigos e funções
extern std::vector<Inimigo> inimigos;
void gerarInimigos(mapa* mapa, player* jogador);
void atualizarInimigos(mapa* mapa);
void desenharInimigos();
void ResetarJogo(player * player, mapa * mapa);


int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Mini Bomberman");
    SetTargetFPS(60);

    player PLAYER;
    mapa MAPA;
    bomba BOMBA;
    menu MENU;


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (MENU.escolhaMenu == 0) {
            MENU.desenhomenuInicial(&MENU);
            MENU.escolhamenuInicial(&MENU);

            switch (MENU.escolhaMenu) {
                case 1: // NOVO JOGO
                    FILE *arq;
                    arq = fopen("save.txt", "w");
                    fclose(arq);
                    ResetarJogo(&PLAYER, &MAPA); // Reseta o jogo
                    inimigos.clear();
                    break;

                case 2: // CONTINUAR
                    MENU.loadJogo(&PLAYER, &MAPA);
                    inimigos.clear();
                    
                    break;

                case 3: // CARREGAR MAPA
                    inimigos.clear();
                    MAPA.carregaMapa(&MAPA);
                    gerarInimigos(&MAPA, &PLAYER);
                    break;

                case 4: // SAIR
                    exit(0);
                    break;
            }
        } else {
            if(!PLAYER.vivo) {
                MENU.escolhaGameover = 0; // Reseta a escolha do game over
                MENU.gameover(&MENU, &PLAYER);
                MENU.escolhagameover(&MENU);
                switch (MENU.escolhaGameover)  // Verifica a opção do menu
                {
                    case 1:
                        //TENTAR NOVAMENTE
                        PLAYER.vivo = true; // Reseta o estado do player
                        MAPA.faseTerminada = false; // Reseta a fase terminada
                        break;
                    case 2:
                        //SALVAR E SAIR
                        MENU.escolhaMenu = 0; // Volta para o menu inicial
                        MENU.opcaoMenu = 1; // Reseta a opção do menu
                        PLAYER.vivo = true; // Reseta o estado do player
                        break;
                }

            } else {

                if (!MAPA.mapaPersonalizado && !MAPA.faseTerminada){
                    gerarInimigos(&MAPA, &PLAYER);
                    MAPA.criaFase(&MAPA);
                    PLAYER.numeroBombas = PLAYER.numeroBombasTotal; // Reseta o número de bombas do jogador
                    PLAYER.pontosAuxiliar = PLAYER.pontos; // Salva os pontos do jogador antes de iniciar a fase
                    PLAYER.vitoria = false; // Reseta a vitória do jogador
                }
                atualizarInimigos(&MAPA);
                MAPA.criaMapaBomba(&MAPA);
                PLAYER.updateposplayer(&PLAYER, &MAPA);
                PLAYER.updatecentroplayer();
                BOMBA.lancaBomba(&PLAYER);
                BOMBA.explodebomba(&PLAYER);
                BOMBA.explodemapa(&PLAYER, &MAPA);
                BOMBA.explosaoCadeia(&MAPA);
                BOMBA.explosaoRemota(&PLAYER, &MAPA);
                BOMBA.destroiMapa(&BOMBA, &MAPA);
                
                BOMBA.limpaBombas();
                MAPA.criaItens(&MAPA);
                MAPA.colisaoItens(&PLAYER);
                MAPA.colisaoSaida(&PLAYER, &MAPA);
                BOMBA.morteplayer(&PLAYER, &MAPA);
                if(PLAYER.vitoria){
                    MENU.saveJogo(&PLAYER, &MAPA);
                }

                if (!PLAYER.vivo) {
                    MAPA.mapaMorte(&MAPA); // Reseta o mapa se o jogador morrer
                    PLAYER.playerMorte(&PLAYER); // Reseta o jogador se ele morrer
                    BOMBA.bombasMorte(&PLAYER, &MAPA); // Reseta as bombas
                }

                MAPA.desenhoMapa(&MAPA);
                BOMBA.desenhabomba(&PLAYER, &MAPA);
                MAPA.HUD(&PLAYER, &MAPA);
                MAPA.desenhaItens(&MAPA);
                PLAYER.desenhoplayer();
                MAPA.desenhaSaida(&MAPA);
                desenharInimigos();
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ResetarJogo(player * player, mapa * mapa) {
    player->posplayer = {60, 60}; // Reseta a posição do jogador
    player->vivo = true; // Reseta o estado do jogador
    player->bombaRemota = false;
    mapa->faseAtual = 1; // Reseta a fase atual
    player->pontos = 0; // Reseta os pontos do jogador
    mapa->faseTerminada = false; // Reseta a fase terminada
    mapa->mapaPersonalizado = false; // Reseta o mapa personalizado
    player->numeroBombas = 1; // Reseta o número de bombas do jogador
    player->numeroBombasTotal = 1; // Reseta o número total de bombas do jogador
    player->alcance = 1; // Reseta o alcance da bomba do jogador
    player->velplayer = 2.0f; // Reseta a velocidade do jogador
}