#include "CGameScreen.hpp"
#include "CWaterBlob.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>

CWaterBlob::CWaterBlob(CGameScreen* gameScreen, int x, int y) : CEntity(x, y) {
    this->m_image = al_load_bitmap("res/waterblob.png");
    this->m_frame = 0;
    this->m_centerX = x;
    this->m_xVelocity = 3;
    this->m_yVelocity = 0;
    this->m_gameScreen = gameScreen;
    this->m_radius = 25;
    this->m_shouldRemove = false;
    this->m_canCollide = false;
    this->m_health = 10;
    this->m_hurtTime = 0;
}

void CWaterBlob::render(int cameraX, int cameraY) {
    ALLEGRO_BITMAP* frameImage = al_create_sub_bitmap(this->m_image, static_cast<int>(this->m_frame) * 64, 0, 64, 64);
    al_draw_bitmap(frameImage, this->getPosX() - cameraX, this->getPosY() - cameraY, 0);
    int x = this->getPosX();
    int y = this->getPosY();
    if (this->m_hurtTime > 0) {
        al_draw_filled_rectangle(
			x - cameraX, y - cameraY, x + 64 - cameraX, y + 64 - cameraY, al_map_rgba(255, 0, 0, 80)
		);
        this->m_hurtTime--;
    }
}

void CWaterBlob::update() {
    this->move();
    this->m_frame += 0.08;
    if (this->m_frame > 3) {
        this->m_frame = 0;
    }
}

void CWaterBlob::move() {
    if (!(this->getPosX() < this->m_radius + this->m_centerX && this->getPosX() > this->m_radius - this->m_centerX)) {
        this->m_xVelocity *= -1;
    }
    std::list<CEntity*>* ents = this->m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for(i = ents->begin(); i != ents->end(); i++) {
        if ((*i) == this) {
			continue;
		}
        bool isColliding = this->isColliding((*i), this->getPosX() + this->m_xVelocity, this->getPosY());
        if (isColliding) {
            this->m_xVelocity *= -1;
        }
    }
    this->setPosX(this->getPosX() + this->m_xVelocity);

    this->m_yVelocity += 0.4;
    std::list<CEntity*>::iterator ii;
    for(ii = ents->begin(); ii != ents->end(); ii++) {
        if (!(*ii)->canCollide()) {
            continue;
        }
        bool isColliding = this->isColliding((*ii), this->getPosX(), this->getPosY() + this->m_yVelocity);
        if (isColliding) {
            this->m_yVelocity = 0;
        }
    }
    this->setPosY(this->getPosY() + this->m_yVelocity);
}

void CWaterBlob::hurt(int damage) {
    CEntity::hurt(damage);
    this->m_hurtTime = 30;
}
