#pragma once

#include "CEntity.hpp"
#include <allegro5/allegro.h>

class CGameScreen;

class CWaterBlob : public CEntity {
    public:
        CWaterBlob(CGameScreen* gameScreen, int x, int y);
        void render(int cameraX, int cameraY) override;
        void update() override;
        void move();
        void hurt(int damage) override;

    private:
        ALLEGRO_BITMAP* m_image;
        float m_frame;
        int m_centerX;
        int m_xVelocity;
        float m_yVelocity;
        CGameScreen* m_gameScreen;
        int m_radius;
        int m_hurtTime;
};
