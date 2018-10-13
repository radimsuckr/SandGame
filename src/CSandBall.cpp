#include "CGameScreen.hpp"
#include "CPlayer.hpp"
#include "CSandBall.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

CSandBall::CSandBall(CGameScreen* gameScreen, CPlayer* player) {
    this->m_posX = player->getPosX() + (player->getFacing() == FACING_RIGHT ? 64 : 0);
    this->m_posY = player->getPosY() + 32;
    this->m_xVelocity = player->getFacing() == FACING_RIGHT ? 5 : -5;
    this->m_yVelocity = 0.03;
    this->m_ticksAlive = 0;
    this->m_canCollide = false;
    this->m_gameScreen = gameScreen;
    this->m_player = player;
}

void CSandBall::render(int cameraX, int cameraY) {
    al_draw_filled_circle(this->getPosX() - cameraX, this->getPosY() - cameraY, 5, al_map_rgb(150, 131, 87));
}

void CSandBall::update() {
    this->m_posX += this->m_xVelocity;
    this->m_posY += this->m_yVelocity;
    this->m_yVelocity += 0.02;

    std::list<CEntity*>* ents = this->m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for (i = ents->begin(); i != ents->end(); i++) {
        if ((*i) == this || (*i) == this->m_player) {
			continue;
		}
        bool isColliding = this->isColliding((*i), this->getPosX() + this->m_xVelocity, this->getPosY());
        if (isColliding) {
            (*i)->hurt(5);
            this->m_shouldRemove = true;
        }
    }

    if (++this->m_ticksAlive > 60 * 2) {
        this->m_shouldRemove = true;
    }
}

int CSandBall::getPosX() {
    return static_cast<int>(this->m_posX);
}

int CSandBall::getPosY() {
    return static_cast<int>(this->m_posY);
}

bool CSandBall::isColliding(CEntity* ent, int x, int y) {
    int playerX = x - 2.5;
    int playerY = y - 2.5;
    int entityX = ent->getPosX();
    int entityY = ent->getPosY();

    return (playerX < (entityX + 64) && playerY < (entityY + 64) && (playerX + 5) > entityX && (playerY + 5) > entityY);
}
