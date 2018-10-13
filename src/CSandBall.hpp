#pragma once

#include "CEntity.hpp"

class CEntity;
class CGameScreen;
class CPlayer;

class CSandBall : public CEntity {
    public:
        CSandBall(CGameScreen* gameScreen, CPlayer* player);
        void render(int cameraX, int cameraY) override;
        void update() override;
        int getPosX() override;
        int getPosY() override;
        bool isColliding(CEntity* ent, int x, int y);

    private:
        float m_posX;
        float m_posY;
        float  m_xVelocity;
        float m_yVelocity;
        int m_ticksAlive;
        CGameScreen* m_gameScreen;
        CPlayer* m_player;
};
