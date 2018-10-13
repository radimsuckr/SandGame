#include "CEvent.hpp"
#include "CMainWindow.hpp"
#include <allegro5/allegro.h>
#include <iostream>

CEvent::CEvent(CMainWindow* mainWindow) {
    this->m_eventQueue = al_create_event_queue();
    this->m_mainWindow = mainWindow;
    this->m_keys = new Key[ALLEGRO_KEY_MAX];

    for (int a = 0; a < ALLEGRO_KEY_MAX; a++) {
        this->m_keys[a].isDown = false;
        this->m_keys[a].lastTime = 0;
    }
}

ALLEGRO_EVENT_QUEUE* CEvent::getEventQueue() {
    return this->m_eventQueue;
}

void CEvent::processEvents() {
    ALLEGRO_EVENT* event = new ALLEGRO_EVENT;
    al_get_next_event(this->m_eventQueue, event);
    switch (event->type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            this->m_mainWindow->exit();
			break;
        case ALLEGRO_EVENT_KEY_DOWN:
            this->toggleKey(event->keyboard.keycode, true);
			break;
        case ALLEGRO_EVENT_KEY_UP:
            this->toggleKey(event->keyboard.keycode, false);
			break;
    }
}

void CEvent::toggleKey(int keyCode, bool isDown) {
    this->m_keys[keyCode].isDown = isDown;
}

bool CEvent::isKeyDown(int keyCode) {
    return this->m_keys[keyCode].isDown;
}

bool CEvent::isKeyDownTimed(int keyCode, int msTime) {
    if ((this->m_mainWindow->getMiliseconds() - this->m_keys[keyCode].lastTime) > msTime &&
		this->m_keys[keyCode].isDown) {
        this->m_keys[keyCode].lastTime = this->m_mainWindow->getMiliseconds();
        return true;
    } 

    return false;
}
