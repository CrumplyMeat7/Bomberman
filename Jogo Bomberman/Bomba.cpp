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
};

std::vector<BombaAtiva> bombas;

void bomba::lancaBomba(player * player) {
    if (IsKeyPressed(KEY_Q) && player->numeroBombas > 0) {
        player->numeroBombas--;
        BombaAtiva novaBomba;
        novaBomba.pos = {(float)(((int)(player->posplayer.x+25)/60)*60+30), (float)(((int)(player->posplayer.y+60)/60)*60+30)}; // Posiciona a bomba no grid
        novaBomba.tempoCriacao = GetTime();
        bombas.push_back(novaBomba);
    }
}
//Desenha a bomba e explode ela após um tempo
void bomba::desenhabomba(player* player, mapa* mapa) {
    for (auto& b : bombas) {
        if (!b.explodiu) {

            DrawCircleV(b.pos, 25, BROWN);
        }   
        else if (b.explosaoAtiva) {
            //DIREITA
            for(int i = 0; i <= player->alcance; i++){
                if(mapa->layout[(int)(b.pos.y / 60)][(int)((b.pos.x + i * 60) / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x + i * 60, b.pos.y };
                DrawCircleV(temp, 25, RED);
                
            }
            //ESQUERDA
            for(int i = 0; i >= -player->alcance; i--){
                if(mapa->layout[(int)(b.pos.y / 60)][(int)((b.pos.x + i * 60) / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x + i * 60, b.pos.y };
                DrawCircleV(temp, 25, RED);
            }
            //BAIXO
            for(int i = 0; i <= player->alcance; i++){
                if(mapa->layout[(int)((b.pos.y + i  * 60) / 60)][(int)(b.pos.x  / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = {b.pos.x , b.pos.y + i * 60 };
                DrawCircleV(temp, 25, RED);
              
            }
            //CIMA
            for(int i = 0; i >= -player->alcance; i--){
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
//Remover bombas que já explodiram e não estão mais ativas
    bombas.erase(
        std::remove_if(bombas.begin(), bombas.end(),
            [](const BombaAtiva& b) { return b.explodiu && !b.explosaoAtiva; }),
        bombas.end()
    );
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
            for(int i = 0; i <= player->alcance; i++){
                int y = (int)(b.pos.y / 60);
                int x = (int)((b.pos.x + i * 60) / 60);
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    break;
                }
            }
            //ESQUERDA
            for(int i = 0; i >= -player->alcance; i--){
                int y = (int)(b.pos.y / 60);
                int x = (int)((b.pos.x + i * 60) / 60);
                if(mapa->layout[y][x] != 0){ // Encontrou parede
                    if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                    if (mapa->layout[y][x] == 2) { // Parede quebrável
                        mapa->layout[y][x] = 0;   // Destrói a primeira e para
                        break;
                }
                }
            }
            //BAIXO
            for(int i = 0; i <= player->alcance; i++){
                int y = (int)((b.pos.y + i * 60) / 60);
                int x = (int)(b.pos.x / 60);
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    break;
                }
            }
            //CIMA
            for(int i = 0; i >= -player->alcance; i--){
                int y = (int)((b.pos.y + i * 60) / 60);
                int x = (int)(b.pos.x / 60);
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2) { // Parede quebrável
                    mapa->layout[y][x] = 0;   // Destrói a primeira e para
                    break;
                }
            }
        }

    }
}



