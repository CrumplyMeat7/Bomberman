#include "Classes.hpp"
#include <raylib.h>

void bomba::lancaBomba(float x, float y, float z) {
    if(IsKeyPressed(KEY_Q)&& numeroBombas > 0) {
        numeroBombas--;
        posBomba.x = x + z / 2;
        posBomba.y = y + z / 2;
        DrawCircleV(posBomba, 30, BROWN);
    }
    
}

void bomba::explodebomba(void) {
    
}

void bomba::desenhabomba(float x, float y, float z) {
    if(IsKeyPressed(KEY_Q)&& numeroBombas > 0) {
        DrawCircleV(posBomba, 30, BROWN);
    }
    
}