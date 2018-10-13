#pragma once

class CMainWindow;

class CScreen {
    public:
        CScreen(CMainWindow* mainWindow, CScreen* parent);
        CScreen* getParent();
        virtual void render() = 0;
        virtual void update() = 0;

    protected:
        CScreen* m_parent;
        CMainWindow* m_mainWindow;
};
