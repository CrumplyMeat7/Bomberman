#pragma once
#include <raylib.h>

class mapa;
// Classe que define as caracteristicas do jogador
class player {
    public:
        Vector2 posplayer;
        Texture2D texplayer;
        //int playerSize = 40;
        float velplayer = 3;
        player(void);
        void updateposplayer(player * player, mapa* mapa);
        void bombas();
        void desenhoplayer();
        int alcance = 1; //Alcance da bomba
        int numeroBombas = 1; //Número de bombas
//sprites
Texture2D sprites[4][3];
int frameAtual;
float tempoFrame;
float tempoAcumulado;
int direcao; // 0=baixo, 1=esquerda, 2=direita, 3=cima
int playerSize;

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

class menu{
    public:
        int opcaoMenu = 1;
        int escolhaMenu = 0;
        void desenhomenuInicial(menu * menu);
        void escolhamenuInicial(menu * menu); 
};


