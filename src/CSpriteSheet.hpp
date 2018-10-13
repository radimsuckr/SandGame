#pragma once

#include <allegro5/allegro.h>

class CSpriteSheet {
    public:
        explicit CSpriteSheet(char* filename);
        ALLEGRO_BITMAP* getSprite(int x, int y);

    private:
        ALLEGRO_BITMAP* m_spriteSheet;
};
