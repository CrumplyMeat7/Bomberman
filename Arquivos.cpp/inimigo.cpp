#include "Classes.hpp"

struct InimigoAtivo {
    Vector2 pos;
    Vector2 poscentroinimigo; // Posição central do inimigo
    float velocidade;
    int tipoInimigo; 
    bool achouParede = true; // Indica se o inimigo encontrou uma parede
    int direcao; // Direção do inimigo (0=baixo, 1=esquerda, 2=direita, 3=cima)
};

std::vector<InimigoAtivo> inimigos;


void inimigo::spawnInimigo(mapa * mapa) {
    inimigos.clear(); // Limpa a lista de inimigos antes de spawnar novos
    int i = GetRandomValue(4,7);
    for(int j = 0; j < i; j++) {
        InimigoAtivo novoInimigo;
        do{
            novoInimigo.pos = {GetRandomValue(0, 14) * 60 + 30, GetRandomValue(0, 14) * 60 + 30}; // Posição aleatória no grid
        } while (mapa->layout[(int)(novoInimigo.pos.y / mapa->tamanhoBloco)][(int)(novoInimigo.pos.x / mapa->tamanhoBloco)] != 0); // Garante que a posição não seja um bloco sólido ou parede quebrável
        novoInimigo.velocidade = 1.0f; // Velocidade do inimigo
        novoInimigo.tipoInimigo = 2;
        inimigos.push_back(novoInimigo);
    }
}

void inimigo::updatecentroInimigo(inimigo * inimigo) {
    for(auto& inimigo : inimigos) {
        // Atualiza a posição central do inimigo
        inimigo.poscentroinimigo = {(float)(((int)(inimigo.pos.x + 25) / 60) * 60 + 30), (float)(((int)(inimigo.pos.y + 60) / 60) * 60 + 30)};
    }
}
void inimigo::desenhaInimigo() {
    for (const auto& inimigo : inimigos) {
        DrawCircleV(inimigo.pos, 20, DARKBLUE); // Desenha o inimigo 
    }
}


void inimigo::moveInimigo(player * player, mapa * mapa) {
    for (auto& inimigo : inimigos) {
        if(inimigo.tipoInimigo == 0){
            if (inimigo.pos.x < player->poscentroplayer.x) {
                if (mapa->layout[(int)(inimigo.pos.y / mapa->tamanhoBloco)][(int)(inimigo.pos.x / mapa->tamanhoBloco) + 1] == 0) {
                    inimigo.pos.x += inimigo.velocidade;
                }
                inimigo.pos.x += inimigo.velocidade;
            } else if (inimigo.pos.x > player->poscentroplayer.x) {
                if (mapa->layout[(int)(inimigo.pos.y / mapa->tamanhoBloco)][(int)(inimigo.pos.x / mapa->tamanhoBloco) - 1] == 0) {
                    inimigo.pos.x -= inimigo.velocidade;
                }
            }
            
            if (inimigo.pos.y < player->poscentroplayer.y) {
                if (mapa->layout[(int)(inimigo.pos.y / mapa->tamanhoBloco) + 1][(int)(inimigo.pos.x / mapa->tamanhoBloco)] == 0) {
                    inimigo.pos.y += inimigo.velocidade;
                }
            } else if (inimigo.pos.y > player->poscentroplayer.y) {
                if (mapa->layout[(int)(inimigo.pos.y / mapa->tamanhoBloco) - 1][(int)(inimigo.pos.x / mapa->tamanhoBloco)] == 0) {
                    inimigo.pos.y -= inimigo.velocidade;
                }
            }
        }
        if (inimigo.tipoInimigo == 1) {
            
        }
    }
}

void inimigo::morteinimigo(inimigo * inimigo, mapa* mapa) {
    for (auto it = inimigos.begin(); it != inimigos.end(); ) {
        if (mapa->layoutBomba[(int)(it->poscentroinimigo.y / 60)][(int)(it->poscentroinimigo.x / 60)] == 1) {
            // Inimigo morto
            //player->pontos += 100; // Adiciona pontos ao jogador
            it = inimigos.erase(it); // Remove o inimigo da lista e atualiza o iterator
        } else {
            ++it;
        }
    } 
}

