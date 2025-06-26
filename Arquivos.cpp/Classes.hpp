#pragma once
#include <raylib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream> 

class mapa;
class inimigo;
class menu;
// Classe que define as caracteristicas do jogador
class player {
    public:
        Vector2 posplayer;
        Texture2D texplayer;
        Vector2 poscentroplayer;
        //int playerSize = 40;
        float velplayer;
        int alcance = 1; //Alcance da bomba
        int numeroBombas = 1; //Número de bombas
        int numeroBombasTotal = numeroBombas; //Número total de bombas que o jogador pode carregar
        bool vivo = true; //ta vivo ou nao
        int pontos = 0; //Pontos do jogador
        int pontosAuxiliar = 0; //Pontos do jogador auxiliar
        bool vitoria = false; //Vitoria ou nao
        void updateposplayer(player * player, mapa* mapa);
        void desenhoplayer();
        void updatecentroplayer(void);
        player(void);
        void playerMorte(player* player);
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
        int layout[15][15];
        int layoutAuxiliar[15][15];
        int layoutBomba[15][15]; // Mapa auxiliar para bombas
        int layoutDestruir[15][15] = {0};
        int tamanhoBloco = 60;
        int FaseAtual = 1; // Fase atual
        bool mapaPersonalizado = false; // Mapa personalizado
        Vector2 posMapa; // Posições dos blocos do mapa
        bool faseTerminada = false; // Fase terminada
        void desenhoMapa(mapa * mapa);
        void criaFase(mapa * mapa);
        void HUD(player * player, mapa * mapa);
        void criaItens(mapa * mapa);
        void desenhaItens(mapa * mapa);
        void colisaoItens(player * player);
        void carregaMapa(mapa * mapa);
        void criaMapaBomba(mapa * mapa);
        void desenhaSaida(mapa * mapa);
        void colisaoSaida(player * player,mapa * mapa);
        void mapaMorte(mapa* mapa);
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
        void morteplayer(player* player, mapa* mapa);
        void limpaBombas();
        void bombasMorte(player* player, mapa* mapa);
        void explosaoCadeia(mapa* mapa);
        void destroiMapa(bomba* bomba, mapa* mapa);

        Texture2D texbomba = LoadTexture("Texturas/bomba.png");

};

class menu{
    public:
        int opcaoMenu = 1;
        int escolhaMenu = 0;
        int opcaoGameover = 1;
        int escolhaGameover = 0;
        void desenhomenuInicial(menu * menu);
        void escolhamenuInicial(menu * menu);
        void gameover(menu * menu, player * player);
        void escolhagameover(menu * menu);
        void saveJogo(player * player, mapa * mapa);
        void loadJogo(player * player, mapa * mapa);
};

class inimigo {
public:
    void spawnInimigo(mapa * mapa);
    void desenhaInimigo();
    void moveInimigo(player * player, mapa * mapa);
    void updatecentroInimigo(inimigo * inimigo);
    void morteinimigo(inimigo * inimigo, mapa* mapa);

};
