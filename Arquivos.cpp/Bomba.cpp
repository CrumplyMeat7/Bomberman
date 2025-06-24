#include "Classes.hpp"
#include <raylib.h>
#include <vector>
#include <math.h>
#include <algorithm>

struct BombaAtiva {
    Vector2 pos;
    float tempoCriacao;
    bool explodiu = false;
    float tempoExplosao = 0.0f; 
    bool explosaoAtiva = false;
    int alcancebomba;
    Vector4 encontrouParede = {0, 0, 0, 0}; // Direção da explosão (direita, esquerda, baixo, cima)
};

std::vector<BombaAtiva> bombas;

void bomba::lancaBomba(player * player) {
    if (IsKeyPressed(KEY_Q) && player->numeroBombas > 0) {
        player->numeroBombas--;
        BombaAtiva novaBomba;
        novaBomba.pos = {player->poscentroplayer.x, player->poscentroplayer.y}; // Posiciona a bomba no grid
        novaBomba.tempoCriacao = GetTime();
        novaBomba.alcancebomba = player->alcance; // Define o alcance da bomba
        bombas.push_back(novaBomba);
    }
}
//Desenha a bomba e explode ela após um tempo
void bomba::desenhabomba(player* player, mapa* mapa) {
    for (auto& b : bombas) {
        if (!b.explodiu) {

            DrawCircleV(b.pos, 25, BROWN);
        } else if (b.explosaoAtiva) {
            //DIREITA
            for(int i = 0; i <= b.alcancebomba; i++){
                if(mapa->layout[(int)(b.pos.y / 60)][(int)((b.pos.x + i * 60) / 60)] != 0){ // Verifica se é parede sólida
                    break;
                }
                Vector2 temp = { b.pos.x + i * 60, b.pos.y };
                DrawCircleV(temp, 25, RED);
                
            }
            //ESQUERDA
            for(int i = 0; i >= -b.alcancebomba; i--){
                if(mapa->layout[(int)(b.pos.y / 60)][(int)((b.pos.x + i * 60) / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x + i * 60, b.pos.y };
                DrawCircleV(temp, 25, RED);
            }
            //BAIXO
            for(int i = 0; i <= b.alcancebomba; i++){
                if(mapa->layout[(int)((b.pos.y + i  * 60) / 60)][(int)(b.pos.x  / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = {b.pos.x , b.pos.y + i * 60 };
                DrawCircleV(temp, 25, RED);
              
            }
            //CIMA
            for(int i = 0; i >= -b.alcancebomba; i--){
               if(mapa->layout[(int)((b.pos.y + i  * 60) / 60)][(int)(b.pos.x  / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x , b.pos.y + i * 60 };
                DrawCircleV(temp, 25, RED);
            }
            if (GetTime() - b.tempoExplosao > 0.5f) { 
                b.explosaoAtiva = false; 
            }

        }   
    }
}

void bomba::explodebomba(player* player) {
    for (auto& b : bombas) {
         if(!b.explodiu && (GetTime() - b.tempoCriacao > delaybomba)){
            b.explodiu = true;
            player->numeroBombas++;
            b.tempoExplosao = GetTime();
            b.explosaoAtiva = true;
        }
    }
}

void bomba::explodemapa(player* player, mapa* mapa) {
    for (auto& b : bombas) {
        if (b.explodiu && b.explosaoAtiva) {
            //DIREITA
            for(int i = 0; i <= b.alcancebomba; i++){
                int y = (int)(b.pos.y / 60);
                int x = (int)((b.pos.x + i * 60) / 60);
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.x == 0) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    b.encontrouParede.x = 1; // Marca que encontrou parede na direção direita
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
            }
            //ESQUERDA
            for(int i = 0; i >= -b.alcancebomba; i--){
                int y = (int)(b.pos.y / 60);
                int x = (int)((b.pos.x + i * 60) / 60);
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
                    if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.y == 0) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    b.encontrouParede.y = 1; // Marca que encontrou parede na direção esquerda
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
            }
            //BAIXO
            for(int i = 0; i <= b.alcancebomba; i++){
                int y = (int)((b.pos.y + i * 60) / 60);
                int x = (int)(b.pos.x / 60);
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.z == 0) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    b.encontrouParede.z = 1; // Marca que encontrou parede na direção baixo
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
            }
            //CIMA
            for(int i = 0; i >= -b.alcancebomba; i--){
                int y = (int)((b.pos.y + i * 60) / 60);
                int x = (int)(b.pos.x / 60);
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.w == 0) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    b.encontrouParede.w = 1; // Marca que encontrou parede na direção cima
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
            }
        }
        if(b.explodiu && !b.explosaoAtiva){
            for(int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    if (mapa->layoutBomba[i][j] == 1) {
                        mapa->layoutBomba[i][j] = 0; // Limpa o mapa auxiliar de bombas
                    }
                }
            }
        }
    }
}

void bomba::limpaBombas() {
    // Remove bombas que já explodiram e não estão mais ativas
    bombas.erase(std::remove_if(bombas.begin(), bombas.end(), [](const BombaAtiva& b) {
        return b.explodiu && !b.explosaoAtiva;
    }), bombas.end());
}

void bomba::morteplayer(player* player, mapa* mapa) {
    if(mapa->layoutBomba[(int)(player->poscentroplayer.y / 60)][(int)(player->poscentroplayer.x / 60)] == 1) {
        player->posplayer = {60, 60}; // Reseta a posição do player
        player->vivo = false; // Marca o player como morto
    }
}


