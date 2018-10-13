#include "CScreen.hpp"
#include <allegro5/allegro.h>

CScreen::CScreen(CMainWindow* mainWindow, CScreen* parent) {
    this->m_mainWindow = mainWindow;
    this->m_parent = parent;
}

CScreen* CScreen::getParent() {
    return this->m_parent;
}
