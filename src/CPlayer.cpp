#include "CEvent.hpp"
#include "CGameScreen.hpp"
#include "CPlayer.hpp"
#include "CSandBall.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

CPlayer::CPlayer(CGameScreen* gameScreen, CEvent* event, int x, int y) : CEntity(x, y) {
    this->m_event = event;
    this->m_gameScreen = gameScreen;
    this->loadImage();
    this->m_frame = 0;
    this->m_yVelocity = 0;
    this->m_xVelocity = 0;
    this->m_facing = FACING_RIGHT;
}

CPlayer::~CPlayer() {
    al_destroy_bitmap(this->m_image);
}

void CPlayer::loadImage() {
    this->m_image = al_load_bitmap("res/player.png");

    if (this->m_image == nullptr) {
        std::cerr << "Can not load player image." << std::endl;
    }
}

void CPlayer::render(int cameraX, int cameraY) {
    int x = this->getPosX();
    int y = this->getPosY();

    ALLEGRO_BITMAP* subImage = al_create_sub_bitmap(this->m_image, static_cast<int>(this->m_frame) * 64, 0, 64, 64);
    al_draw_bitmap(subImage, x - cameraX, y - cameraY, 0);
}

void CPlayer::update() {
    this->move();
    this->jump();

    if (this->m_event->isKeyDownTimed(ALLEGRO_KEY_LCTRL, 250)) {
        this->m_gameScreen->addEntity(new CSandBall(this->m_gameScreen, this));
    }

    this->setPosX(this->getPosX() + this->m_xVelocity);
    this->setPosY(this->getPosY() + this->m_yVelocity);
    this->m_frame += 0.10;
    if (this->m_frame > 3) {
        this->m_frame = 0;
    }
}


void CPlayer::move() {
    if (this->m_event->isKeyDown(ALLEGRO_KEY_RIGHT)) {
        this->m_xVelocity = 5;
        this->m_facing = FACING_RIGHT;
    } else if (this->m_event->isKeyDown(ALLEGRO_KEY_LEFT)) {
        this->m_xVelocity = -5;
        this->m_facing = FACING_LEFT;
    } else {
        this->m_xVelocity = 0;
    }
    std::list<CEntity*>* ents = this->m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for(i = ents->begin(); i != ents->end(); i++) {
        if (!(*i)->canCollide()) {
            continue;
        }
        bool isColliding = this->isColliding((*i), this->getPosX() + this->m_xVelocity, this->getPosY());
        if (isColliding) {
            this->m_xVelocity = 0;
        }
    }
}

void CPlayer::jump() {
    if (this->m_yVelocity == 0 && this->m_event->isKeyDown(ALLEGRO_KEY_SPACE)) {
        this->m_yVelocity = -10;
    }

    this->m_yVelocity += 0.4;
    std::list<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for(i = ents->begin(); i != ents->end(); i++) {
        if (!(*i)->canCollide()) {
            continue;
        }
        bool isColliding = this->isColliding((*i), this->getPosX(), this->getPosY() + this->m_yVelocity);
        if (isColliding) {
            this->m_yVelocity = 0;
        }
    }
}

unsigned char CPlayer::getFacing() {
    return this->m_facing;
}
