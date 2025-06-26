#include "Classes.hpp"
#include <raylib.h>

void menu::desenhomenuInicial(menu * menu){
       DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), LIGHTGRAY);
    DrawText("Mini Bomberman", 300, 200, 40, BLACK);

    // Desenha as opçoes do menu
    const char* opcoes[] = { "Novo Jogo", "Continuar Jogo", "Carregar", "Sair" };
    int yInicial = 300;
    for (int i = 0; i < 4; i++) {
        int tamanho = (opcaoMenu == i + 1) ? 50 : 30; //<-operador ternario(condicao ? valor_se_verdadeiro : valor_se_falso)
        Color cor = (opcaoMenu == i + 1) ? RED : BLACK; 
        DrawText(opcoes[i], 350, yInicial + i * 50, tamanho, cor);
    }
}

 void menu::escolhamenuInicial(menu * menu){
    if((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))&& menu->opcaoMenu > 1) {
        menu->opcaoMenu = menu->opcaoMenu - 1;
    }
    if((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))&& menu->opcaoMenu < 4) {
        menu->opcaoMenu = menu->opcaoMenu + 1;
    }
    if(IsKeyPressed(KEY_ENTER)) 
       menu->escolhaMenu = menu->opcaoMenu;
}

void menu::gameover(menu * menu, player * player) {   
        ClearBackground(LIGHTGRAY);
        DrawText("Game Over", 250, 200, 80, BLACK);
    const char* opcoes[] = { "Tentar Novamente", "Salvar e Sair"};
    int yInicial = 350;
    for (int i = 0; i < 2; i++) {
        int tamanho = (opcaoGameover == i + 1) ? 50 : 30; //<-operador ternario(condicao ? valor_se_verdadeiro : valor_se_falso)
        Color cor = (opcaoGameover == i + 1) ? RED : BLACK; 
        DrawText(opcoes[i], 350, yInicial + i * 50, tamanho, cor);
    }
}

void menu::escolhagameover(menu * menu){
    if((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))&& menu->opcaoGameover > 1) {
        menu->opcaoGameover = menu->opcaoGameover - 1;
    }
    if((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))&& menu->opcaoGameover < 2) {
        menu->opcaoGameover = menu->opcaoGameover + 1;
    }
    if(IsKeyPressed(KEY_ENTER)) 
       menu->escolhaGameover = menu->opcaoGameover;
}

void menu::saveJogo(player * player, mapa * mapa) {
    FILE *arq = fopen("save.txt", "w");
    if (arq != NULL) {
        fprintf(arq, "%d %d  %d %f %d %d\n", player->pontos, player->alcance, player->numeroBombasTotal, player->velplayer, mapa->faseAtual, player->bombaRemota);
        fclose(arq);
    }
}

void menu::loadJogo(player * player, mapa * mapa) {
    FILE *arq = fopen("save.txt", "r");
    if (arq != NULL) {
        fscanf(arq, "%d %d %d %f %d %d", &player->pontos, &player->alcance, &player->numeroBombasTotal, &player->velplayer, &mapa->faseAtual, &player->bombaRemota);
        fclose(arq);
    } 
}