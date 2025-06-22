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

void mapa::carregaMapa(mapa * mapa) {
    mapa->mapaPersonalizado = true;
    FILE *arq = fopen("mapa.txt", "r");
    if(arq == NULL) {
        DrawText("Erro ao carregar o mapa", 10, 10, 20, RED);
        WindowShouldClose();
    }
    char linhaBuffer[17];
    for (int linha = 0; linha < 15; linha++) {
        if (fgets(linhaBuffer, sizeof(linhaBuffer), arq) == NULL) {
            DrawText("Carregamento de mapa falhou", 10, 10, 20, RED);
            fclose(arq);
            return;
        }
        for (int coluna = 0; coluna < 15; coluna++) {
            char c = linhaBuffer[coluna];
            switch (c) {
                case '1': mapa->layout[linha][coluna] = 1; break;
                case '2': mapa->layout[linha][coluna] = 2; break;
                case ' ': mapa->layout[linha][coluna] = 0; break;
                default: mapa->layout[linha][coluna] = 0; break; // caractere estranho vazio
            }
        }
    }
    fclose(arq);
}

void mapa::criaFase(mapa * mapa) {
   if(!faseTerminada) { // Verifica se a fase já foi criada
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
        //TEMPORARIO, por enquanto apenas para teste e garantir que o jogador nao fique preso em um bloco
        mapa->layout[1][1] = 0;
        mapa->layout[1][2] = 0;
        mapa->layout[2][1] = 0;

        for (int linha = 0; linha < 15; linha++) {
            for (int coluna = 0; coluna < 15; coluna++) {
                mapa->layoutAuxiliar[linha][coluna] = mapa->layout[linha][coluna];
            }
        }
        
    }
    mapa->faseTerminada = true; // Marca a fase como criada
}


struct Item{
    Vector2 posItem;
    Texture2D texItem;
    int tipoItem; // 0 = velocidade, 1 = alcance, 2 = numero de bombas
};
std::vector<Item> Itens;

void mapa::criaItens(mapa * mapa) {
    for(int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            if(mapa->layout[linha][coluna] != mapa->layoutAuxiliar[linha][coluna]) {
                mapa->layoutAuxiliar[linha][coluna] = mapa->layout[linha][coluna];
                if (mapa->layout[linha][coluna] == 0) { // Se for um espaço vazio
                    if (GetRandomValue(1, 10) <= 3) { // Chance de criar um item
                        Item novoItem;
                        novoItem.tipoItem = GetRandomValue(0, 2); // Tipo de item aleatório (0, 1 ou 2)
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
    for (auto& item : Itens) {
        switch (item.tipoItem) {
            case 0: // Item de velocidade
                DrawCircle(item.posItem.x, item.posItem.y, 20, GREEN);
                break;
            case 1: // Item de alcance
                DrawCircle(item.posItem.x, item.posItem.y, 20, BLUE);
                break;
            case 2: // Item de número de bombas
                DrawCircle(item.posItem.x, item.posItem.y, 20, PURPLE);
                break;
        }
    }
}

void mapa::colisaoItens(player * player) {
    for (auto item = Itens.begin(); item != Itens.end();) {
        if (player->poscentroplayer.x == item->posItem.x && player->poscentroplayer.y == item->posItem.y) {
            // Colisão detectada
            switch (item->tipoItem) {
                case 0: // Aumenta a velocidade do jogador
                    player->velplayer += 1.0f;
                    break;
                case 1: // Aumenta o alcance da bomba
                    player->alcance++;
                    break;
                case 2: // Aumenta o número de bombas
                    player->numeroBombas++;
                    break;
            }
            item = Itens.erase(item); // Remove o item da lista
        } else {
            ++item; // Avança para o próximo item
        }
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

void mapa::criaMapaBomba(mapa * mapa) {
    for(int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            mapa->layoutBomba[linha][coluna] = mapa->layout[linha][coluna];
            if(mapa->layoutBomba[linha][coluna] == 2) { // Se for uma parede quebrável
                mapa->layoutBomba[linha][coluna] = 0; // Define como espaço vazio
            }
        }
    }
}
