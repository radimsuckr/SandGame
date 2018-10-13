#pragma once

#include "CScreen.hpp"
#include <string>

struct ALLEGRO_FONT;

class CAboutScreen : public CScreen {
    public:
        CAboutScreen(CMainWindow* mainWindow);
        void render();
        void update();

    private:
        std::string* m_lines;
        ALLEGRO_FONT* m_font;

};
