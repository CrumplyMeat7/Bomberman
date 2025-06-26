#include "Classes.hpp"
extern int faseAtual;

void mapa::criaMapaBomba(mapa * mapa) {
    for(int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            mapa->layoutBomba[linha][coluna] = mapa->layout[linha][coluna];
            if(mapa->layoutBomba[linha][coluna] == 2) { // Se for uma parede quebrável
                mapa->layoutBomba[linha][coluna] = 0; // Define como espaço vazio
            }
            if(mapa->layoutBomba[linha][coluna] == 1) { 
                mapa->layoutBomba[linha][coluna] = 2; 
            }
        }
    }
}


void mapa::desenhoMapa(mapa * mapa) {
    static Texture2D blocoSolido = LoadTexture("sprites/tiles/bloco.png");
    static Texture2D tijoloSheet = LoadTexture("sprites/tiles/tijolo.png");

    for (int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            Vector2 pos = {
                (float)(coluna * tamanhoBloco),
                (float)(linha * tamanhoBloco)
            };

            switch (mapa->layout[linha][coluna]) {
                case 0: // espaço vazio
                    Color corChao;
                    switch (faseAtual) {
                        case 1: corChao = Color{0x10, 0x78, 0x30, 255}; break; // verde
                        case 2: corChao = Color{0x20, 0x60, 0xAA, 255}; break; // azul
                        case 3: corChao = Color{0x60, 0x10, 0x60, 255}; break; // roxo
                        case 4: corChao = Color{0x88, 0x44, 0x00, 255}; break; // marrom
                        default: corChao = DARKGRAY; break;
                    }
                    DrawRectangle(pos.x, pos.y, tamanhoBloco, tamanhoBloco, corChao);

                    break;

                case 1: // parede sólida (bloco inquebrável)
                    DrawTextureEx(blocoSolido, pos, 0.0f, (float)tamanhoBloco / 16.0f, WHITE);
                    break;

                case 2: // parede quebrável (usa apenas o primeiro frame)
                {
                    Rectangle sourceRec = { 0, 0, 16, 16 }; // frame 0
                    DrawTexturePro(
                        tijoloSheet,
                        sourceRec,
                        { pos.x, pos.y, (float)tamanhoBloco, (float)tamanhoBloco },
                        { 0, 0 },
                        0.0f,
                        WHITE
                    );
                    break;
                }
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
    for (int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            mapa->layoutAuxiliar[linha][coluna] = mapa->layout[linha][coluna];
        }
    }
}

void mapa::criaFase(mapa * mapa) {
   if(!faseTerminada) { // Verifica se a fase já foi criada
        //Zera o mapa 
        int layoutInicial[15][15];

switch (faseAtual) {
    case 1:
    default: {
        int temp[15][15] = {
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
        for (int l = 0; l < 15; l++)
            for (int c = 0; c < 15; c++)
                layoutInicial[l][c] = temp[l][c];
        break;
    }

    case 2: {
        int temp[15][15] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        for (int l = 0; l < 15; l++)
            for (int c = 0; c < 15; c++)
                layoutInicial[l][c] = temp[l][c];
        break;
    }

    // Adicione outros layouts se quiser
}

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
    int tipoItem; // 0 = velocidade, 1 = alcance, 2 = numero de bombas, 3 = bomba remota
};
std::vector<Item> Itens;

struct Saida{
    Vector2 posSaida;
    bool saidaAchada = false;
    bool saidaAberta = false;

};
struct Saida saida;

int chegaNumeroBlocos(mapa * mapa) {
    int numeroBlocos = 0;
    for (int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            if (mapa->layout[linha][coluna] == 2) { // Conta blocos quebráveis
                numeroBlocos++;
            }
        }
    }
    return numeroBlocos;
}

void mapa::criaItens(mapa * mapa) {
    for(int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            if(mapa->layout[linha][coluna] != mapa->layoutAuxiliar[linha][coluna]) {
                mapa->layoutAuxiliar[linha][coluna] = mapa->layout[linha][coluna];
                if (mapa->layout[linha][coluna] == 0) { // Se for um espaço vazio
                    if((GetRandomValue(1,100) <= 4  || chegaNumeroBlocos(mapa) == 0) && !saida.saidaAchada) { // Chance de criar a saída ou se não houver blocos quebráveis
                        saida.posSaida = {(float)(coluna * tamanhoBloco + tamanhoBloco / 2),(float)(linha * tamanhoBloco + tamanhoBloco / 2)};
                        saida.saidaAchada = true; // Marca que a saída foi encontrada

                    }
                    else if (GetRandomValue(1, 100) <= 15) { // Chance de criar um item
                        Item novoItem;
                        novoItem.tipoItem = GetRandomValue(0, 3); // Tipo de item aleatório (0, 1, 2 ou 3)
                        novoItem.posItem = {static_cast<float>(coluna * tamanhoBloco + tamanhoBloco / 2), static_cast<float>(linha * tamanhoBloco + tamanhoBloco / 2)};
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
            case 3: // Item de bomba remota
                DrawCircle(item.posItem.x, item.posItem.y, 20, ORANGE);
        }
    }
}

void mapa::colisaoItens(player * player) {
    for (auto item = Itens.begin(); item != Itens.end();) {
        if (player->poscentroplayer.x == item->posItem.x && player->poscentroplayer.y == item->posItem.y) {
            // Colisão detectada
            switch (item->tipoItem) {
                case 0: // Aumenta a velocidade do jogador
                    player->velplayer += 0.5f;
                    break;
                case 1: // Aumenta o alcance da bomba
                    player->alcance++;
                    break;
                case 2: // Aumenta o número de bombas
                    player->numeroBombas++;
                    player->numeroBombasTotal++;
                    break;
                case 3:
                    player->bombaRemota = true; // Ativa a bomba remota
                    break;
            }
            item = Itens.erase(item); // Remove o item da lista
        } else {
            ++item; // Avança para o próximo item
        }
    }
}

void mapa::desenhaSaida(mapa * mapa) {
    if (saida.saidaAchada) {
        DrawCircle(saida.posSaida.x, saida.posSaida.y, 20, BLACK);
    }
}

void mapa::colisaoSaida(player * player,mapa * mapa) {
    if (saida.saidaAchada ) {
        if (player->poscentroplayer.x == saida.posSaida.x && player->poscentroplayer.y == saida.posSaida.y) {
            mapa->faseTerminada = false; // Marca a fase como terminada
            mapa->faseAtual++; // Avança para a próxima fase
            player->posplayer = {60, 60}; // Reseta a posição do jogador
            saida.saidaAchada = false; // Reseta a saída
            Itens.clear(); // Limpa os itens da fase anterior
            player->pontos += 500; // Adiciona pontos ao jogador por completar a fase
            player->vitoria = true; // Marca que o jogador venceu a fase
        }
    }
}

void mapa::HUD(player * player, mapa * mapa) {
    //HUD   
    DrawText("Fase:",20, 910,30,BLACK);
    DrawText("Pontuação:",200, 910, 30, BLACK);
    DrawText("Bombas:",500, 910, 30,  BLACK);
    DrawText("Alcance:", 700, 910, 30, BLACK);
    
    DrawText(TextFormat("%d", mapa->faseAtual), 120, 910, 30, BLACK);
    DrawText(TextFormat("%d", player->pontos), 400, 910, 30, BLACK);
    DrawText(TextFormat("%d/%d", player->numeroBombas, player->numeroBombasTotal), 630, 910, 30, BLACK);
    DrawText(TextFormat("%d", player->alcance), 840, 910, 30, BLACK);
}

void mapa::mapaMorte(mapa* mapa) {
    for(int linha = 0; linha < 15; linha++) {
        for (int coluna = 0; coluna < 15; coluna++) {
            mapa->layoutBomba[linha][coluna] = mapa->layout[linha][coluna];
            if(mapa->layoutBomba[linha][coluna] == 2) { // Se for uma parede quebrável
                mapa->layoutBomba[linha][coluna] = 0; // Define como espaço vazio
            }
            if(mapa->layoutBomba[linha][coluna] == 1) {
                mapa->layoutBomba[linha][coluna] = 0; 
            }
        }
    }
    Itens.clear(); // Limpa os itens do mapa
    saida.saidaAchada = false; // Reseta a saída
    mapa->faseTerminada = false; // Reseta a fase terminada
    mapa->mapaPersonalizado = false; // Reseta o mapa personalizado
}

