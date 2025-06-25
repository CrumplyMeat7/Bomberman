#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "Classes.hpp"
#include <math.h>

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
    inimigo INIMIGO;
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
                ResetarJogo(&PLAYER, &MAPA); // Reseta o jogo
                FILE *arq;
                arq = fopen("save.txt", "w");
                fclose(arq);
                break;
            
            case 2:
                //CONTINUAR JOGO
                MENU.loadJogo(&PLAYER, &MAPA);
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

            }else{

            //LOGICA
            if (!MAPA.mapaPersonalizado && !MAPA.faseTerminada) { // Só cria fase se não for mapa personalizado
                MAPA.criaFase(&MAPA);
                INIMIGO.spawnInimigo(&MAPA);
                PLAYER.pontosAuxiliar = PLAYER.pontos; // Salva os pontos do jogador antes de iniciar a fase
                PLAYER.vitoria = false; // Reseta a vitória do jogador
            }
            MAPA.criaMapaBomba(&MAPA);
            PLAYER.updateposplayer(&PLAYER, &MAPA);
            PLAYER.updatecentroplayer();
            INIMIGO.moveInimigo(&PLAYER, &MAPA);
            INIMIGO.updatecentroInimigo(&INIMIGO);
            BOMBA.lancaBomba(&PLAYER);
            BOMBA.explodebomba(&PLAYER);
            BOMBA.explodemapa(&PLAYER, &MAPA);
            BOMBA.explosaoCadeia(&MAPA);
            BOMBA.destroiMapa(&BOMBA, &MAPA);
            BOMBA.limpaBombas();
            MAPA.criaItens(&MAPA);
            MAPA.colisaoItens(&PLAYER);
            MAPA.colisaoSaida(&PLAYER, &MAPA);
            BOMBA.morteplayer(&PLAYER, &MAPA);
            INIMIGO.morteinimigo(&INIMIGO, &MAPA);
            if(PLAYER.vitoria){
                MENU.saveJogo(&PLAYER, &MAPA);
            }
            //RESETA CASO O JOGADOR MORRA
            if (!PLAYER.vivo) {
                MAPA.mapaMorte(&MAPA); // Reseta o mapa se o jogador morrer
                PLAYER.playerMorte(&PLAYER); // Reseta o jogador se ele morrer
                BOMBA.bombasMorte(&PLAYER, &MAPA); // Reseta as bombas
            }


            //DESENHO
            MAPA.desenhoMapa(&MAPA);
            BOMBA.desenhabomba(&PLAYER, &MAPA);
            
            MAPA.HUD(&PLAYER, &MAPA);
            MAPA.desenhaItens(&MAPA);
            PLAYER.desenhoplayer();
            INIMIGO.desenhaInimigo();
            MAPA.desenhaSaida(&MAPA);

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
    player->pontos = 0; // Reseta os pontos do jogador
    mapa->FaseAtual = 1; // Reseta a fase atual
    mapa->faseTerminada = false; // Reseta a fase terminada
    mapa->mapaPersonalizado = false; // Reseta o mapa personalizado
    player->numeroBombas = 1; // Reseta o número de bombas do jogador
    player->numeroBombasTotal = 1; // Reseta o número total de bombas do jogador
    player->alcance = 1; // Reseta o alcance da bomba do jogador
    player->velplayer = 2.0f; // Reseta a velocidade do jogador
}
