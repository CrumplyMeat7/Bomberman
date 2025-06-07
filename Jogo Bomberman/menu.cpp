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