#pragma once

#include "CEntity.hpp"
#include <vector>

class CEvent;
class CGameScreen;
struct ALLEGRO_BITMAP;

enum {
    FACING_LEFT,
    FACING_RIGHT
};

class CPlayer : public CEntity {
    public:
        CPlayer(CGameScreen* gameScreen, CEvent* event, int x, int y);
		~CPlayer();
        void render(int cameraX, int cameraY) override;
        void update() override;
        void init();
        void loadImage();
        void move();
        void jump();
        unsigned char getFacing();

    private:
        CEvent* m_event;
        CGameScreen* m_gameScreen;
        ALLEGRO_BITMAP* m_image;
        float m_frame;
        float m_yVelocity;
        float m_xVelocity;
        unsigned char m_facing;
};
