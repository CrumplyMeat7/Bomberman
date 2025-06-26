#include "Classes.hpp"
#include <raylib.h>
extern "C" float Vector2Distance(Vector2 v1, Vector2 v2);
#include <vector>
#include <math.h>
#include <algorithm>
Rectangle getHitboxBomba(Vector2 pos) {
    return { pos.x - 24, pos.y - 24, 48, 48 }; // mesma do desenho
}


std::vector<BombaAtiva> bombas;

void bomba::lancaBomba(player * player) {
    if (IsKeyPressed(KEY_Q) && player->numeroBombas > 0) {
        player->numeroBombas--;
        BombaAtiva novaBomba;
        //novaBomba.pos = {player->poscentroplayer.x, player->poscentroplayer.y}; // Posiciona a bomba no grid
        novaBomba.pos = {
    (float)(((int)(player->posplayer.x + 25) / 60) * 60 + 30),
    (float)(((int)(player->posplayer.y + 60) / 60) * 60 + 30)
};

        novaBomba.tempoCriacao = GetTime();
        novaBomba.alcancebomba = player->alcance; // Define o alcance da bomba
        bombas.push_back(novaBomba);
    }
}
//Desenha a bomba e explode ela após um tempo
void bomba::desenhabomba(player* player, mapa* mapa) {
    static Texture2D bombaSprite = LoadTexture("sprites/bomba/bomba.png");

   

    static float tempoEntreFrames = 0.25f; // velocidade da animação
    static float acumuladorTempo = 0.0f;
    static int frameAtual = 0;

    acumuladorTempo += GetFrameTime();
    if (acumuladorTempo >= tempoEntreFrames) {
        acumuladorTempo = 0.0f;
        frameAtual = (frameAtual + 1) % 3;
    }

    for (auto& b : bombas) {
        if (!b.explodiu) {
            // Centraliza a bomba no grid
            Rectangle source = { (float)(frameAtual * 16), 0, 16, 16 };
            Rectangle dest = {
                b.pos.x - 30, // 60x60 centralizado
                b.pos.y - 30,
                60, 60
            };

            DrawTexturePro(bombaSprite, source, dest, { 0, 0 }, 0.0f, WHITE);
/////////////////

        // Atualiza podeAtravessar
Rectangle hitboxBomba = getHitboxBomba(b.pos);


DrawRectangleLines(hitboxBomba.x, hitboxBomba.y, hitboxBomba.width, hitboxBomba.height, RED); // debug

if (b.podeAtravessar) {
    Rectangle hitboxJogador = { player->posplayer.x, player->posplayer.y + 57, 48, 15 };
    Rectangle hitboxBomba = { b.pos.x - 24, b.pos.y - 24, 48, 48 };

    if (!CheckCollisionRecs(hitboxJogador, hitboxBomba)) {
        b.podeAtravessar = false; // jogador saiu, agora é sólida
    }
}


            
            
        } else if (b.explosaoAtiva) {
            //DIREITA
            for(int i = 0; i <= b.alcancebomba; i++){
                if(mapa->layout[(int)(b.pos.y / 60)][(int)((b.pos.x + i * 60) / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x + i * 60, b.pos.y };
                DrawCircleV(temp, 25, RED);
                
            }
            //ESQUERDA
            for(int i = 0; i >= -b.alcancebomba; i--){
                if(mapa->layout[(int)(b.pos.y / 60)][(int)((b.pos.x + i * 60) / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x + i * 60, b.pos.y };
                DrawCircleV(temp, 25, RED);
            }
            //BAIXO
            for(int i = 0; i <= b.alcancebomba; i++){
                if(mapa->layout[(int)((b.pos.y + i  * 60) / 60)][(int)(b.pos.x  / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = {b.pos.x , b.pos.y + i * 60 };
                DrawCircleV(temp, 25, RED);
              
            }
            //CIMA
            for(int i = 0; i >= -b.alcancebomba; i--){
               if(mapa->layout[(int)((b.pos.y + i  * 60) / 60)][(int)(b.pos.x  / 60)] != 0) // Verifica se é parede sólida
                    break;
                Vector2 temp = { b.pos.x , b.pos.y + i * 60 };
                DrawCircleV(temp, 25, RED);
            }
            if (GetTime() - b.tempoExplosao > 0.5f) { 
                b.explosaoAtiva = false; 
            }

        }   
    }
}

void bomba::explodebomba(player* player) {
    for (auto& b : bombas) {
         if(!b.explodiu && (GetTime() - b.tempoCriacao > delaybomba) && !player->bombaRemota) {
            b.explodiu = true;
            player->numeroBombas++;
            b.tempoExplosao = GetTime();
            b.explosaoAtiva = true;
        }
    }
}

void bomba::explodemapa(player* player, mapa* mapa) {
    for (auto& b : bombas) {
        if (b.explodiu && b.explosaoAtiva) {
            //DIREITA
            for(int i = 0; i <= b.alcancebomba; i++){
                int y = (int)(b.pos.y / 60);
                int x = (int)((b.pos.x + i * 60) / 60);
                
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.x == 0) { // Parede quebrável
                    mapa->layoutDestruir[y][x] = 1;   // Destrói a primeira e para
                    b.encontrouParede.x = 1;
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
            }
            //ESQUERDA
            for(int i = 0; i >= -b.alcancebomba; i--){
                int y = (int)(b.pos.y / 60);
                int x = (int)((b.pos.x + i * 60) / 60);
                
                    if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.y == 0) { // Parede quebrável
                    mapa->layoutDestruir[y][x] = 1;   // Destrói a primeira e para
                    b.encontrouParede.y = 1;
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
            }
            //BAIXO
            for(int i = 0; i <= b.alcancebomba; i++){
                int y = (int)((b.pos.y + i * 60) / 60);
                int x = (int)(b.pos.x / 60);
                
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.z == 0) { // Parede quebrável
                    mapa->layoutDestruir[y][x] = 1;   // Destrói a primeira e para
                    b.encontrouParede.z = 1;
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
            }
            //CIMA
            for(int i = 0; i >= -b.alcancebomba; i--){
                int y = (int)((b.pos.y + i * 60) / 60);
                int x = (int)(b.pos.x / 60);
                
                if (mapa->layout[y][x] == 1) { // Parede sólida
                    break;
                }
                if (mapa->layout[y][x] == 2 && b.encontrouParede.w == 0) { // Parede quebrável
                    mapa->layoutDestruir[y][x] = 1;   // Destrói a primeira e para
                    b.encontrouParede.w = 1;
                    player->pontos += 5; // Adiciona pontos ao jogador
                    break;
                }
                mapa->layoutBomba[y][x] = 1; // Marca a bomba no mapa auxiliar
            }
        }
        if(b.explodiu && !b.explosaoAtiva){
            for(int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    if (mapa->layoutBomba[i][j] == 1) {
                        mapa->layoutBomba[i][j] = 0; // Limpa o mapa auxiliar de bombas
                    }
                }
            }
        }
    }
}

void bomba::limpaBombas() {
    // Remove bombas que já explodiram e não estão mais ativas
    bombas.erase(std::remove_if(bombas.begin(), bombas.end(), [](const BombaAtiva& b) {
        return b.explodiu && !b.explosaoAtiva;
    }), bombas.end());
}

void bomba::explosaoCadeia(mapa* mapa) {
    for (auto& b : bombas) {
        if(!b.explodiu && mapa->layoutBomba[(int)(b.pos.y / 60)][(int)(b.pos.x / 60)] == 1) {
            b.tempoCriacao = delaybomba; 
        }
    }
}

void bomba::morteplayer(player* player, mapa* mapa) {
    if(mapa->layoutBomba[(int)(player->poscentroplayer.y / 60)][(int)(player->poscentroplayer.x / 60)] == 1) {
        player->vivo = false; // Marca o player como morto
    }
}

bool temBombaNaPosicao(Vector2 tentativa, Vector2 posJogador) {
    Rectangle hitboxTentativa = { tentativa.x, tentativa.y + 57, 48, 15 };
    Rectangle hitboxAtual     = { posJogador.x, posJogador.y + 57, 48, 15 };

    for (const auto& b : bombas) {
        if (b.explodiu) continue;

        Rectangle hitboxBomba = getHitboxBomba(b.pos);

        if (CheckCollisionRecs(hitboxTentativa, hitboxBomba)) {
            if (b.podeAtravessar && CheckCollisionRecs(hitboxAtual, hitboxBomba)) {
                return false; // ainda dentro → pode sair
            }
            return true; // está fora → bloqueia
        }
    }

    return false;
}

void bomba::bombasMorte(player* player, mapa* mapa) {
    bombas.clear(); // Limpa todas as bombas ativas
}

void bomba::destroiMapa(bomba* bomba, mapa* mapa) {
    for(auto& b : bombas) {
        if (b.explodiu && !b.explosaoAtiva) {
            for(int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    if (mapa->layoutDestruir[i][j] == 1) {
                        mapa->layoutDestruir[i][j] = 0;
                        if(mapa->layout[i][j] == 2) { // Se for uma parede quebrável
                            mapa->layout[i][j] = 0; // Destrói a parede quebrável
                        }
                    }
                }
            }
        }
    }
}

void bomba::explosaoRemota(player* player, mapa* mapa){
    if (IsKeyPressed(KEY_E) && player->bombaRemota) {
        for (auto& b : bombas) {
            if (!b.explodiu) {
               b.explodiu = true;
                player->numeroBombas++;
                b.tempoExplosao = GetTime();
                b.explosaoAtiva = true;
            }
        }
    }
}


