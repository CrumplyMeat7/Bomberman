#pragma once
#include <raylib.h>

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

class bomba{
    public:
        int alcance = 1; //Alcance da bomba
        int numeroBombas = 1; //Número de bombas
        Vector2 posBomba;
        int delaybomba = 3; //Delay da bomba em segundos
        void lancaBomba(float x, float y,float z);
        void desenhabomba(float x, float y, float z);
        void explodebomba(void);

};




