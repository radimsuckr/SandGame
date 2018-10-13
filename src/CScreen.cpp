#include "CScreen.hpp"
#include <allegro5/allegro.h>

CScreen::CScreen(CMainWindow* const mainWindow, CScreen* parent) {
    m_mainWindow = mainWindow;
    m_parent = parent;
}

CScreen* CScreen::getParent() {
    return m_parent;
}
