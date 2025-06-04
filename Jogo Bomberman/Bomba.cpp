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

void bomba::lancaBomba(float x, float y, float z) {
    if (IsKeyPressed(KEY_Q) && numeroBombas > 0) {
        numeroBombas--;
        BombaAtiva novaBomba;
        novaBomba.pos = { (float)(((int)x/60)*60+30), (float)(((int)y/60)*60+30) };
        novaBomba.tempoCriacao = GetTime();
        bombas.push_back(novaBomba);
    }
}
//Desenha a bomba e explode ela após um tempo
void bomba::desenhabomba(float x, float y, float z) {
    for (auto& b : bombas) {
        if (!b.explodiu) {
            DrawCircleV(b.pos, 25, BROWN);
        }   
    }
}
void bomba::explodebomba(void) {
    for (auto& b : bombas) {
        if (!b.explodiu && (GetTime() - b.tempoCriacao > delaybomba)) {
            b.explodiu = true;

            for(int i = -alcance; i <= alcance; i++){
                b.pos.x = b.pos.x + i * 60;
                DrawCircleV(b.pos, 25, RED);
                b.pos.x = b.pos.x - i * 60;
            }
            for(int i = -alcance; i <= alcance; i++){
                b.pos.y = b.pos.y + i * 60;
                DrawCircleV(b.pos, 25, RED);
                b.pos.y = b.pos.y - i * 60;
            } 
            DrawCircleV(b.pos, 25, RED); // Exemplo de explosão
            numeroBombas++;
        }
    }
}
