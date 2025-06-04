#include "Classes.hpp"
#include <raylib.h>
#include <vector>
#include <math.h>

struct BombaAtiva {
    Vector2 pos;
    float tempoCriacao;
    bool explodiu = false;
};

std::vector<BombaAtiva> bombas;

void bomba::lancaBomba(player * player) {
    if (IsKeyPressed(KEY_Q) && player->numeroBombas > 0) {
        player->numeroBombas--;
        BombaAtiva novaBomba;
        novaBomba.pos = { (float)(((int)player->posplayer.x/60)*60+30), (float)(((int)player->posplayer.y/60)*60+30)};
        novaBomba.tempoCriacao = GetTime();
        bombas.push_back(novaBomba);
    }
}
//Desenha a bomba e explode ela após um tempo
void bomba::desenhabomba(void) {
    for (auto& b : bombas) {
        if (!b.explodiu) {
            DrawCircleV(b.pos, 25, BROWN);
        }   
    }
}
void bomba::explodebomba(player* player) {
    for (auto& b : bombas) {
        if (!b.explodiu && (GetTime() - b.tempoCriacao > delaybomba)) {
            b.explodiu = true;

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
            DrawCircleV(b.pos, 25, RED); // Exemplo de explosão
            player->numeroBombas++;
        }
    }
}
