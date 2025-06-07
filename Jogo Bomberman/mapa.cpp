#include "Classes.hpp"
#include <raylib.h>


void mapa::desenhoMapa(void){
    for (int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            int tipo = layout[linha][coluna];
            int x = coluna * tamanhoBloco;
            int y = linha * tamanhoBloco;

            switch (tipo) {
                case 1: // parede sólida
                    DrawRectangle(x, y, 60, 60, BLACK);
                    break;
                case 2: // parede quebrável
                    DrawRectangle(x, y, 60, 60, DARKGRAY);
                    break;
                default: // espaço vazio
                            DrawRectangleLines(x, y, 60, 60, BLACK);
                        break;
            }
        }
    }




    //HUD   
    DrawText("Fase:",20, 910,30,BLACK);
    DrawText("Pontuação:",200, 910, 30, BLACK);
    DrawText("Bombas:",500, 910, 30,  BLACK);
    DrawText("Alcance:", 700, 910, 30, BLACK);
}
void mapa::HUD(player * player){
    //HUD   
    DrawText("Fase:",20, 910,30,BLACK);
    DrawText("Pontuação:",200, 910, 30, BLACK);
    DrawText("Bombas:",500, 910, 30,  BLACK);
    DrawText("Alcance:", 700, 910, 30, BLACK);
    
    //DrawText(TextFormat("%d", player->fase), 100, 910, 30, BLACK);
    //DrawText(TextFormat("%d", player->pontuacao), 300, 910, 30, BLACK);
    DrawText(TextFormat("%d", player->numeroBombas), 630, 910, 30, BLACK);
    DrawText(TextFormat("%d", player->alcance), 840, 910, 30, BLACK);
}