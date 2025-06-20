#pragma once
#include <raylib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream> 

class mapa;
// Classe que define as caracteristicas do jogador
class player {
    public:
        Vector2 posplayer;
        Texture2D texplayer;
        //int playerSize = 40;
        float velplayer;
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
        int layoutAuxiliar[15][15];
        int tamanhoBloco = 60;
        Vector2 posMapa; // Posições dos blocos do mapa
        bool faseTerminada = false; // Fase terminada
        void desenhoMapa(mapa * mapa);
        void updateMapa(mapa * mapa);
        void criaFase(mapa * mapa);
        void HUD(player * player);
        void criaItens(mapa * mapa);
        void desenhaItens(mapa * mapa);
};
// Classe que define as caracteristicas da bomba
class bomba{
    public:
        
        Vector2 posBomba;
        float delaybomba = 2.0f; //Delay da bomba em segundos
        void lancaBomba(player* player);
        void desenhabomba(player* player,mapa* mapa);
        void explodebomba(player* player);
        void explodemapa(player* player, mapa* mapa);
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

class inimigo{
    public:
        Vector2 posinimigo;
        float velocidadeInimigo = 1.5f; //Velocidade do inimigo
        void perseguir(player* jogador, inimigo* inimigo);
        void desenhoInimigo(inimigo* inimigo);
};

