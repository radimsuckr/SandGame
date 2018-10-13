#include "CEntity.hpp"

CEntity::CEntity(int x, int y) {
    this->m_posX = x;
    this->m_posY = y;
    this->m_shouldRemove = false;
    this->m_canCollide = true;
	this->m_health = 0;
}

CEntity::CEntity() {
    this->m_posX = 0;
    this->m_posY = 0;
    this->m_shouldRemove = false;
    this->m_canCollide = true;
	this->m_health = 0;
}

int CEntity::getPosX() {
    return this->m_posX;
}   

void CEntity::setPosX(int x) {
    this->m_posX = x;
}

int CEntity::getPosY() {
    return this->m_posY;
}

void CEntity::setPosY(int y) {
    this->m_posY = y;
}

bool CEntity::isColliding(CEntity* entity, int x, int y) {
    int playerX = x;
    int playerY = y;
    int entityX = entity->getPosX();
    int entityY = entity->getPosY();

    return (playerX < (entityX + 64) && playerY < (entityY + 64) && (playerX + 64) > entityX && (playerY + 64) > entityY);
}

bool CEntity::isReadyToRemove() {
    return this->m_shouldRemove;
}

bool CEntity::canCollide() {
    return this->m_canCollide;
}

void CEntity::hurt(int damage) {
    this->m_health -= damage;

    if (this->m_health <= 0) {
        this->m_shouldRemove = true;
    }   
}
