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

void player::updateposplayer(player * player) // Atualiza a posição do player
{
    if(IsKeyDown(KEY_D)){
        player->posplayer.x = player->posplayer.x + player->velplayer;
    }
    if(IsKeyDown(KEY_A)){
        player->posplayer.x = player->posplayer.x - player->velplayer;
    }
    if(IsKeyDown(KEY_S)){
        player->posplayer.y = player->posplayer.y + player->velplayer;
    }
    if(IsKeyDown(KEY_W)){
        player->posplayer.y = player->posplayer.y - player->velplayer;
    }
}
