#include "Classes.hpp"
#include <raylib.h>
#include <vector>
#include <algorithm>
#include <cmath>

extern int faseAtual;

float Vector2Distance(Vector2 v1, Vector2 v2) {
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return sqrtf(dx*dx + dy*dy);
}

std::vector<Inimigo> inimigos;

bool podeMoverParaCelula(int x, int y, mapa* mapa) {
    if (x < 0 || x >= 15 || y < 0 || y >= 15) return false;
    int tipo = mapa->layout[y][x];
    return tipo == 0 || tipo == 2;
}

// Quantidade por tipo de inimigo em cada fase
void gerarInimigos(mapa* mapa, player* jogador) {
    inimigos.clear(); // sempre limpar antes de gerar

    struct InfoInimigo {
        int tipo;
        int quantidade;
    };

    std::vector<InfoInimigo> tipos;

    switch (faseAtual) {
        case 1: tipos = { {1, 3} }; break;
        case 2: tipos = { {1, 4}, {2, 2} }; break;
        case 3: tipos = { {1, 3}, {2, 2}, {3, 1} }; break;
        case 4: tipos = { {2, 3}, {3, 3} }; break;
        default: tipos = { {1, 2} }; break;
    }

    for (auto info : tipos) {
        int gerados = 0;
        while (gerados < info.quantidade) {
            int x = GetRandomValue(0, 14);
            int y = GetRandomValue(0, 14);
            if (mapa->layout[y][x] == 2) {
                Vector2 pos = { x * 60.0f + 30, y * 60.0f + 30 };
                if (Vector2Distance(pos, jogador->poscentroplayer) > 60) {
                    Inimigo novo = { pos, {0, 0}, info.tipo };
                    int dir = GetRandomValue(0, 3);
                    switch (dir) {
                        case 0: novo.dir = {0, -1}; break;
                        case 1: novo.dir = {0, 1}; break;
                        case 2: novo.dir = {-1, 0}; break;
                        case 3: novo.dir = {1, 0}; break;
                    }
                    inimigos.push_back(novo);
                    gerados++;
                }
            }
        }
    }
}

void atualizarInimigos(mapa* mapa) {
    for (auto& inimigo : inimigos) {
        inimigo.pos.x += inimigo.dir.x * 1.5f;
        inimigo.pos.y += inimigo.dir.y * 1.5f;

        int col = (int)(inimigo.pos.x) / 60;
        int lin = (int)(inimigo.pos.y) / 60;

        float distX = fabs(fmod(inimigo.pos.x, 60.0f) - 30);
        float distY = fabs(fmod(inimigo.pos.y, 60.0f) - 30);

        if (distX < 3.0f && distY < 3.0f) {
            std::vector<Vector2> opcoes;

            if (podeMoverParaCelula(col, lin - 1, mapa)) opcoes.push_back({0, -1});
            if (podeMoverParaCelula(col, lin + 1, mapa)) opcoes.push_back({0, 1});
            if (podeMoverParaCelula(col - 1, lin, mapa)) opcoes.push_back({-1, 0});
            if (podeMoverParaCelula(col + 1, lin, mapa)) opcoes.push_back({1, 0});

            Vector2 oposta = {-inimigo.dir.x, -inimigo.dir.y};
            opcoes.erase(std::remove_if(opcoes.begin(), opcoes.end(),
                [&](Vector2 d) { return d.x == oposta.x && d.y == oposta.y; }),
                opcoes.end());

            if (!opcoes.empty()) {
                Vector2 novaDir = opcoes[GetRandomValue(0, (int)opcoes.size() - 1)];
                inimigo.dir = novaDir;
            }
        }
    }
}

void desenharInimigos() {
    for (auto& inimigo : inimigos) {
        Color cor;
        switch (inimigo.tipo) {
            case 1: cor = RED; break;
            case 2: cor = GREEN; break;
            case 3: cor = PURPLE; break;
            case 4: cor = ORANGE; break;
            default: cor = GRAY; break;
        }
        DrawRectangleV({inimigo.pos.x - 20, inimigo.pos.y - 20}, {40, 40}, cor);
    }
}
