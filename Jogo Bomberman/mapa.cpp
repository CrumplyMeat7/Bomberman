#include "Classes.hpp"



void mapa::desenhoMapa(mapa * mapa) {
    for (int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            switch (mapa->layout[linha][coluna]) {
                case 1: // parede sólida
                    DrawRectangle( coluna * tamanhoBloco,  linha * tamanhoBloco, 60, 60, BLACK);
                    break;
                case 2: // parede quebrável
                    DrawRectangle( coluna * tamanhoBloco,  linha * tamanhoBloco, 60, 60, DARKGRAY);
                    break;
                case 0: // espaço vazio
                            DrawRectangleLines( coluna * tamanhoBloco,  linha * tamanhoBloco, 60, 60, BLACK);
                        break;
            }
        }
    }

}

void mapa::updateMapa(mapa * mapa){
   
}

void mapa::criaFase(mapa * mapa) {
   if(!faseTerminada){
        //Zera o mapa 
        int layoutInicial[15][15] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        for (int linha = 0; linha < 15; linha++) {
            for (int coluna = 0; coluna < 15; coluna++) {
                mapa->layout[linha][coluna] = layoutInicial[linha][coluna];
            }
        }
        for (int linha = 0; linha < 15; linha++) {
            for (int coluna = 0; coluna < 15; coluna++) {
                if (mapa->layout[linha][coluna] == 0) { 
                    if (GetRandomValue(1, 10) <= 5 ) { //chance de criar uma parede quebrável
                        mapa->layout[linha][coluna] = 2; // Define como parede quebrável
                    }
                }
            }
        }
        for (int linha = 0; linha < 15; linha++) {
            for (int coluna = 0; coluna < 15; coluna++) {
                mapa->layoutAuxiliar[linha][coluna] = mapa->layout[linha][coluna];
            }
        }
        //TEMPORARIO, por enquanto apenas para teste e garantir que o jogador nao fique preso em um bloco
        mapa->layout[1][1] = 0;
        mapa->layout[1][2] = 0;
        mapa->layout[2][1] = 0;
    }
    mapa->faseTerminada = true; // Marca a fase como criada
}


struct Item{
    Vector2 posItem;
    Texture2D texItem;
};
std::vector<Item> Itens;

void mapa::criaItens(mapa * mapa) {
    for(int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            if(mapa->layout[linha][coluna] != mapa->layoutAuxiliar[linha][coluna]) {
                mapa->layoutAuxiliar[linha][coluna] = mapa->layout[linha][coluna];
                if (mapa->layout[linha][coluna] == 0) { // Se for um espaço vazio
                    if (GetRandomValue(1, 10) <= 2) { // Chance de criar um item
                        Item novoItem;
                        novoItem.posItem = {static_cast<float>(coluna * tamanhoBloco + tamanhoBloco / 2), static_cast<float>(linha * tamanhoBloco + tamanhoBloco / 2)};
                        //novoItem.texItem = LoadTexture("sprites/item.png"); // Carrega a textura do item
                        Itens.push_back(novoItem);
                    }
                }
            }
        }
    }
}
    
void mapa::desenhaItens(mapa * mapa) {
    for (const auto& item : Itens) {
        DrawCircle(item.posItem.x, item.posItem.y, 20, WHITE);
    }
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