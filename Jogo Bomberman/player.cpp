#include "Classes.hpp"
#include <raylib.h>

void player::desenhoplayer(void){ //Desenha o player na tela
    
    DrawRectangle(posplayer.x, posplayer.y, playerSize, playerSize, RED);
    //DrawTextureEx(texplayer,posplayer,0.0f,1.0f,WHITE);
}

player::player(void) //Spawna o player na tela
{
    //texplayer = LoadTexture("Texturas/bomberman.png");
    posplayer.x = 60;
    posplayer.y = 60;
}

void player::updateposplayer(float *x,float *y) // Atualiza a posição do player
{
    if(IsKeyDown(KEY_D)){
        *x = *x + velplayer;
    }
    if(IsKeyDown(KEY_A)){
        *x = *x - velplayer;
    }
    if(IsKeyDown(KEY_S)){
        *y = *y + velplayer;
    }
    if(IsKeyDown(KEY_W)){
        *y = *y - velplayer;
    }
}
