#pragma once

#include "CEntity.hpp"

struct ALLEGRO_BITMAP;

enum {
    SAND_TILE
};

class CTile : public CEntity {
    public:
        CTile(ALLEGRO_BITMAP* bitmap, int x, int y);
        void render(int cameraX, int cameraY);
        void update();

    private:
        ALLEGRO_BITMAP* m_image;    
};
