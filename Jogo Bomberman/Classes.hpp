#pragma once
#include <raylib.h>


// Classe que define as caracteristicas do jogador
class player {
    public:
        Vector2 posplayer;
        Texture2D texplayer;
        int playerSize = 40;
        int velplayer = 3;
        player(void);
        void updateposplayer(float *x,float *y);
        void bombas();
        void desenhoplayer();


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




};
// Classe que define as caracteristicas da bomba
class bomba{
    public:
        int alcance = 1; //Alcance da bomba
        int numeroBombas = 1; //Número de bombas
        Vector2 posBomba;
        float delaybomba = 2.0f; //Delay da bomba em segundos
        void lancaBomba(float x, float y,float z);
        void desenhabomba(float x, float y, float z);
        void explodebomba(void);

};




