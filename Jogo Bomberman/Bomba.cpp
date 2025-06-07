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
        novaBomba.pos = {(float)(((int)player->posplayer.x/60)*60+30), (float)(((int)player->posplayer.y/60)*60+30)}; // Posiciona a bomba no grid};
        novaBomba.tempoCriacao = GetTime();
        bombas.push_back(novaBomba);
    }
}
//Desenha a bomba e explode ela após um tempo
void bomba::desenhabomba(player* player) {
    for (auto& b : bombas) {
        if (!b.explodiu) {

            DrawCircleV(b.pos, 25, BROWN);
        }   
        else if (b.explosaoAtiva) {
            for(int i = -player->alcance; i <= player->alcance; i++){
                b.pos.x = b.pos.x + i * 60;
                DrawCircleV(b.pos, 25, RED);
                b.pos.x = b.pos.x - i * 60;
                
            }
            for(int i = -player->alcance; i <= player->alcance; i++){
                b.pos.y = b.pos.y + i * 60;
                DrawCircleV(b.pos, 25, RED);
                b.pos.y = b.pos.y - i * 60;
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

