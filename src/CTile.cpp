#include "CSpriteSheet.hpp"
#include "CTile.hpp"
#include <allegro5/allegro.h>

CTile::CTile(ALLEGRO_BITMAP* bitmap, int x, int y) : CEntity(x, y) {
    this->m_image = bitmap;
}

void CTile::render(int cameraX, int cameraY) {
    al_draw_bitmap(
		this->m_image, static_cast<float>(this->getPosX()) - cameraX, static_cast<float>(this->getPosY()) - cameraY, 0
	);
}

void CTile::update() {}
