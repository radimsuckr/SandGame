#include "CSpriteSheet.hpp"
#include <iostream>

CSpriteSheet::CSpriteSheet(const char* filename) {
    this->m_spriteSheet = al_load_bitmap(filename);
    if (m_spriteSheet == nullptr) {
        std::cerr << "Can not load sprite sheet (" << filename << ")." << std::endl;
    }
}

ALLEGRO_BITMAP* CSpriteSheet::getSprite(int x, int y) {
    ALLEGRO_BITMAP* bitmap = al_create_sub_bitmap(this->m_spriteSheet, x, y, 64, 64);

    return bitmap;
}
