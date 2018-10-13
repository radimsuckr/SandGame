#pragma once

#include "CScreen.hpp"
#include <list>

class CPlayer;
class CSpriteSheet;
class CEntity;
struct ALLEGRO_BITMAP;

struct Camera {
    int posX;
};

class CGameScreen : public CScreen {
    public:
        CGameScreen(CMainWindow* mainWindow, CScreen* parent);
        void render();
        void update();
        std::list<CEntity*>* getVisibleEntities();
        void initMap(char* filename);
        void addEntity(CEntity* entity);

    private:
        int m_rColor;
        CPlayer* m_player;
        Camera* m_cameraControl;
        std::list<CEntity*>* m_entities;
        CSpriteSheet* m_spriteSheet;
        ALLEGRO_BITMAP* m_background;
};
