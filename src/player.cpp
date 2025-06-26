#include "Classes.hpp"
#include <raylib.h>
#include <vector>
#include <math.h>

bool bloqueiaPorBomba(Vector2 tentativa, Vector2 posJogador) {
    Rectangle hitboxJogadorNova = { tentativa.x, tentativa.y + 57, 48, 15 };
    Rectangle hitboxJogadorAtual = { posJogador.x, posJogador.y + 57, 48, 15 };

    for (auto& b : bombas) {
        if (b.explodiu) continue;

        Rectangle hitboxBomba = { b.pos.x - 24, b.pos.y - 24, 48, 48 };

        if (CheckCollisionRecs(hitboxJogadorNova, hitboxBomba)) {
            if (b.podeAtravessar && CheckCollisionRecs(hitboxJogadorAtual, hitboxBomba)) {
                return false; // ainda dentro, pode sair
            }
            return true; // bateu na bomba
        }
    }

    return false;
}

bool podeAndarPara(Vector2 novaPos, mapa* mapa, Vector2 posJogador) {
    Rectangle hitboxPes = {
        novaPos.x,
        novaPos.y + 57,
        48, // largura
        15  // altura
    };

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
        if (tipo != 0)
            return false;
    }

    // Testa colisão com bomba (somente após garantir que não colide com mapa)
    if (bloqueiaPorBomba(novaPos, posJogador)) return false;

    return true;
}

// --------------------------------------
// Implementações da classe player
// --------------------------------------

player::player(void) {
    posplayer = {60, 60};
    velplayer = 2;
    playerSize = 3;

    frameAtual = 0;
    tempoFrame = 0.15f;
    tempoAcumulado = 0;
    direcao = 0;

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

void player::updateposplayer(player* player, mapa* mapa) {
    bool seMoveu = false;
    Vector2 tentativa = player->posplayer;

    if (IsKeyDown(KEY_RIGHT)) {
        tentativa.x += player->velplayer;
        player->direcao = 2;
        if (podeAndarPara(tentativa, mapa, player->posplayer)) {
            player->posplayer = tentativa;
            seMoveu = true;
        }
    }

    if (IsKeyDown(KEY_LEFT)) {
        tentativa = player->posplayer;
        tentativa.x -= player->velplayer;
        player->direcao = 1;
        if (podeAndarPara(tentativa, mapa, player->posplayer)) {
            player->posplayer = tentativa;
            seMoveu = true;
        }
    }

    if (IsKeyDown(KEY_DOWN)) {
        tentativa = player->posplayer;
        tentativa.y += player->velplayer;
        player->direcao = 0;
        if (podeAndarPara(tentativa, mapa, player->posplayer)) {
            player->posplayer = tentativa;
            seMoveu = true;
        }
    }

    if (IsKeyDown(KEY_UP)) {
        tentativa = player->posplayer;
        tentativa.y -= player->velplayer;
        player->direcao = 3;
        if (podeAndarPara(tentativa, mapa, player->posplayer)) {
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
        player->frameAtual = 1;
    }
}

void player::desenhoplayer(void) {
    DrawText("Desenhando sprite", 10, 10, 20, GREEN);
    Texture2D tex = sprites[direcao][frameAtual];
    DrawTextureEx(tex, posplayer, 0.0f, playerSize, WHITE);
    DrawCircleV({poscentroplayer.x, poscentroplayer.y}, 8, RED);
}

void player::updatecentroplayer(void) {
    poscentroplayer = {
        (float)(((int)(posplayer.x + 25) / 60) * 60 + 30),
        (float)(((int)(posplayer.y + 60) / 60) * 60 + 30)
    };
}

void player::playerMorte(player* player){
    player->pontos = player->pontosAuxiliar; // Reseta os pontos do jogador
    player->posplayer = {60, 60}; // Reseta a posição do jogador
    player->numeroBombas = 1; // Reseta o número de bombas do jogador
    player->numeroBombasTotal = 1; // Reseta o número total de bombas do jogador
    player->alcance = 1; // Reseta o alcance da bomba do jogador
    player->velplayer = 2.0f; // Reseta a velocidade do jogador
}
