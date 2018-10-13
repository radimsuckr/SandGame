#include "CGameScreen.hpp"
#include "CMainWindow.hpp"
#include "CPlayer.hpp"
#include "CSpriteSheet.hpp"
#include "CTile.hpp"
#include "CWaterBlob.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

CGameScreen::CGameScreen(CMainWindow* const mainWindow, CScreen* parent)  : CScreen(mainWindow, parent) {
    this->m_rColor = 0;
    this->m_player = new CPlayer(this, m_mainWindow->getEvent(), 700, 0);
    this->m_cameraControl = new Camera;
    this->m_cameraControl->posX = m_player->getPosX() - 32;
    this->m_spriteSheet = new CSpriteSheet("res/spritesheet.png");
    this->m_entities = new std::list<CEntity*>();
    this->initMap("res/level01.map");
    this->m_background = al_load_bitmap("res/background.png");
}

void CGameScreen::initMap(char* filename) {
    std::ifstream mapFile(filename);

    if (mapFile.is_open()) {
        int rowCounter = 0;

        while (mapFile.good()) {
            std::string row;
            getline(mapFile, row);

            for (size_t a = 0; a < row.size(); a++) {
                char entityChar = row.at(a);

                switch (entityChar) {
                    case 'S':
                        this->m_entities->push_back(
							new CTile(m_spriteSheet->getSprite(64 * (a % 3), 0), a * 64, rowCounter * 64)
						);
						break;
                    case 'C':
                        this->m_entities->push_back(new CTile(m_spriteSheet->getSprite(0, 64), a * 64, rowCounter * 64));
						break;
                    case 'B':
                        this->m_entities->push_back(new CWaterBlob(this, a * 64, rowCounter * 64));
						break;
					default:
						break;
                }
            }
            rowCounter++;
        }
        mapFile.close();
    } else {
        std::cerr << "Can not open map file." << std::endl;
    }
}

void CGameScreen::render() {
    int counter = ceil(this->m_cameraControl->posX / 4.0 / 800);
    al_draw_bitmap(m_background, 800 * (counter - 1) - this->m_cameraControl->posX / 4.0, 0, 0);
    al_draw_bitmap(m_background, 800 * counter - this->m_cameraControl->posX / 4.0, 0, 0);
    al_draw_bitmap(m_background, 800 * (counter + 1) - this->m_cameraControl->posX / 4.0, 0, 0);
    m_player->render(m_cameraControl->posX, 0);
    std::list<CEntity*>::iterator i;
    for(i = m_entities->begin(); i != m_entities->end(); i++) {
        (*i)->render(m_cameraControl->posX, 0);
    }
}   

void CGameScreen::update() {
    std::list<CEntity*>::iterator i;
    auto removedEntities = new std::vector<CEntity*>();
    for (i = m_entities->begin(); i != m_entities->end(); i++) {
        if ((*i)->isReadyToRemove()) {
            removedEntities->push_back((*i));
            continue;
        }
        (*i)->update();
    }

    for (int a = 0; a < removedEntities->size(); a++) {
        this->m_entities->remove(removedEntities->at(a));
    }
    this->m_player->update();
    this->m_cameraControl->posX = this->m_player->getPosX() + 32 - 400;
}

std::list<CEntity*>* CGameScreen::getVisibleEntities() {
    return m_entities;
}

void CGameScreen::addEntity(CEntity* entity) {
    m_entities->push_back(entity);
}
