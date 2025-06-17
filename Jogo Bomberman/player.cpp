#include "Classes.hpp"
#include <raylib.h>

bool podeAndarPara(Vector2 novaPos, mapa* mapa) {
    // Tamanho do sprite com escala aplicada
    float largura_sprite = 48; // 16 * 3
    float altura_sprite = 72;  // 24 * 3

    // Hitbox dos pés: altura de 15px, largura total do sprite
    Rectangle hitboxPes = {
        novaPos.x,               // canto esquerdo
        novaPos.y + 57,          // parte de cima da hitbox (72 - 15)
        largura_sprite,          // largura total
        15                       // altura dos pés
    };

    // Verifica os 4 cantos da hitbox
    Vector2 pontos[4] = {
        { hitboxPes.x, hitboxPes.y },
        { hitboxPes.x + hitboxPes.width, hitboxPes.y },
        { hitboxPes.x, hitboxPes.y + hitboxPes.height },
        { hitboxPes.x + hitboxPes.width, hitboxPes.y + hitboxPes.height }
    };

    for (int i = 0; i < 4; i++) {
        int blocoX = pontos[i].x / 60;
        int blocoY = pontos[i].y / 60;

        if (blocoX < 0 || blocoX >= 15 || blocoY < 0 || blocoY >= 15)
            return false;

        int tipo = mapa->layout[blocoY][blocoX];
        if (tipo != 0)  // 0 = espaço livre
            return false;
    }

    return true; // todos os cantos estão em áreas livres
}



player::player(void) // Spawna o player na tela
{
    posplayer = {60, 60};
    velplayer = 2;
    playerSize = 3; // multiplicador de escala

    frameAtual = 0;
    tempoFrame = 0.15f;
    tempoAcumulado = 0;
    direcao = 0; // 0=baixo, 1=esq, 2=dir, 3=cima

    // Carrega texturas dos sprites
    sprites[0][0] = LoadTexture("sprites/frente1.png");
    sprites[0][1] = LoadTexture("sprites/frente2.png");
    sprites[0][2] = LoadTexture("sprites/frente3.png");

    sprites[1][0] = LoadTexture("sprites/esq1.png");
    sprites[1][1] = LoadTexture("sprites/esq2.png");
    sprites[1][2] = LoadTexture("sprites/esq3.png");

    sprites[2][0] = LoadTexture("sprites/dir1.png");
    sprites[2][1] = LoadTexture("sprites/dir2.png");
    sprites[2][2] = LoadTexture("sprites/dir3.png");

    sprites[3][0] = LoadTexture("sprites/tras1.png");
    sprites[3][1] = LoadTexture("sprites/tras2.png");
    sprites[3][2] = LoadTexture("sprites/tras3.png");
}

void player::updateposplayer(player* player, mapa* mapa) // Atualiza a posição do player
{
    bool seMoveu = false;

  Vector2 tentativa = player->posplayer;

if (IsKeyDown(KEY_D)) {
    tentativa.x += player->velplayer;
    player->direcao = 2;
    if (podeAndarPara(tentativa, mapa)) {
        player->posplayer = tentativa;
        seMoveu = true;
    }
}

if (IsKeyDown(KEY_A)) {
    tentativa = player->posplayer;
    tentativa.x -= player->velplayer;
    player->direcao = 1;
    if (podeAndarPara(tentativa, mapa)) {
        player->posplayer = tentativa;
        seMoveu = true;
    }
}

if (IsKeyDown(KEY_S)) {
    tentativa = player->posplayer;
    tentativa.y += player->velplayer;
    player->direcao = 0;
    if (podeAndarPara(tentativa, mapa)) {
        player->posplayer = tentativa;
        seMoveu = true;
    }
}

if (IsKeyDown(KEY_W)) {
    tentativa = player->posplayer;
    tentativa.y -= player->velplayer;
    player->direcao = 3;
    if (podeAndarPara(tentativa, mapa)) {
        player->posplayer = tentativa;
        seMoveu = true;
    }
}


    if (seMoveu) {
        player->tempoAcumulado += GetFrameTime();
        if (player->tempoAcumulado >= player->tempoFrame) {
            player->tempoAcumulado = 0;
            player->frameAtual = (player->frameAtual + 1) % 3;
        }
    } else {
        player->frameAtual = 1; // Frame central (parado)
    }
}

void player::desenhoplayer(void) // Desenha o player na tela com sprite
{
    DrawText("Desenhando sprite", 10, 10, 20, GREEN);
    Texture2D tex = sprites[direcao][frameAtual];
    DrawTextureEx(tex, posplayer, 0.0f, playerSize, WHITE);
}



