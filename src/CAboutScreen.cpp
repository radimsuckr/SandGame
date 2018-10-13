#include "CAboutScreen.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

CAboutScreen::CAboutScreen(CMainWindow* mainWindow, CScreen* parent) : CScreen(mainWindow, parent) {
    this->m_lines = new std::string[5];
    this->m_lines[0] = "Sand Game";
    this->m_lines[1] = "Game made in 72hours.";
    this->m_lines[2] = "Control your sand elemental,";
    this->m_lines[3] = "with your keyboard.";
    this->m_lines[4] = "Author: Lukas Pohlreich";
    this->m_font = al_load_ttf_font("8bitlim.ttf", 36, 0);
}

void CAboutScreen::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int a = 0; a < 5; a++) {
        al_draw_text(
			this->m_font, al_map_rgb(255, 255, 255), 400, 64 * a, ALLEGRO_ALIGN_CENTRE, this->m_lines[a].c_str()
		);
    }
}

void CAboutScreen::update() {}
