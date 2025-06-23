#include "Classes.hpp"
#include <raylib.h>
#include <vector>
#include <math.h>
#include <algorithm>

void inimigo::perseguir(player* jogador, inimigo * inimigo) {
    // Calcula a distância entre o inimigo e o jogador
    float distancia = sqrt(pow(jogador->posplayer.x - inimigo->posinimigo.x, 2) +
                           pow(jogador->posplayer.y - inimigo->posinimigo.y, 2));

    // Normaliza o vetor de direção
    if (distancia > 0) {
        inimigo->posinimigo.x += (jogador->posplayer.x - inimigo->posinimigo.x) / distancia * inimigo->velocidadeInimigo;
        inimigo->posinimigo.y += (jogador->posplayer.y - inimigo->posinimigo.y) / distancia * inimigo->velocidadeInimigo;
    }
}

void inimigo::desenhoInimigo(inimigo* inimigo) {
    // Desenha o inimigo na tela
    DrawRectangle(inimigo->posinimigo.x, inimigo->posinimigo.y, 40, 40, GREEN);
}