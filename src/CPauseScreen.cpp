#include "CEvent.hpp"
#include "CMainWindow.hpp"
#include "CPauseScreen.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

CPauseScreen::CPauseScreen(CMainWindow* mainWindow, CScreen* parent) : CScreen(mainWindow, parent) {
    this->m_options = new std::string[3];
    this->m_options[0] = "Resume game";
    this->m_options[1] = "About";
    this->m_options[2] = "Quit game";
    this->m_selectedOption = 0;
    this->m_font = al_load_ttf_font("8bitlim.ttf", 36, 0);
}

void CPauseScreen::render() {
    this->m_parent->render();

    al_draw_filled_rectangle(100, 50, 700, 550, al_map_rgba(0, 0, 0, 128));

    for (int a = 0; a < 3; a++) {
        al_draw_text(this->m_font, al_map_rgb(0, 0, 255), 120, a * 60 + 65, 0, this->m_options[a].c_str());
    }

    al_draw_line(
		115, this->m_selectedOption * 60 + 105, 600, this->m_selectedOption * 60 + 105, al_map_rgb(255, 0, 0), 5
	);
}

void CPauseScreen::update() {
    CEvent* event = this->m_mainWindow->getEvent();
    if (event->isKeyDownTimed(ALLEGRO_KEY_DOWN, 100)) {
        if (++this->m_selectedOption > 2) {
            this->m_selectedOption = 0;
        }
    }
    if (event->isKeyDownTimed(ALLEGRO_KEY_UP, 100)) {
        if (--this->m_selectedOption < 0) {
            this->m_selectedOption = 2;
        }
    }

    if (event->isKeyDown(ALLEGRO_KEY_ENTER)) {
        switch (this->m_selectedOption) {
            case 0:
                this->m_mainWindow->changeScreenTo(GAME_SCREEN);
				break;
            case 1:
                this->m_mainWindow->changeScreenTo(ABOUT_SCREEN);
				break;
            case 2:
                this->m_mainWindow->exit();
				break;
        }
    }
}
