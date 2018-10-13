#pragma once

#include "CScreen.hpp"
#include <allegro5/allegro_font.h>
#include <string>

class CMainWindow;

class CPauseScreen : public CScreen {
    public:
        CPauseScreen(CMainWindow* mainWindow, CScreen* parent);
        void render();
        void update();

    private:
        std::string* m_options;
        ALLEGRO_FONT* m_font;
        char m_selectedOption;
};
