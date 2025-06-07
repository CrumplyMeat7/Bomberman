#pragma once
#include <raylib.h>


// Classe que define as caracteristicas do jogador
class player {
    public:
        Vector2 posplayer;
        Texture2D texplayer;
        int playerSize = 40;
        float velplayer = 3;
        player(void);
        void updateposplayer(player * player);
        void bombas();
        void desenhoplayer();
        int alcance = 1; //Alcance da bomba
        int numeroBombas = 1; //Número de bombas

};
//Classe que define as caracteristicas do mapa
class mapa{
    public:
        int layout[15][15] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        int tamanhoBloco = 60;
        void desenhoMapa(void);
        void HUD(player * player);




};
// Classe que define as caracteristicas da bomba
class bomba{
    public:
        
        Vector2 posBomba;
        float delaybomba = 2.0f; //Delay da bomba em segundos
        void lancaBomba(player* player);
        void desenhabomba(player* player);
        void explodebomba(player* player);
        Texture2D texbomba = LoadTexture("Texturas/bomba.png");

};

class powerup{
    public:
        Vector2 pospowerup;
        int tipoPowerup; 
        void upgrade(void);
};


