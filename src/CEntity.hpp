#pragma once

class CEntity {
    public:
        CEntity();
        CEntity(int x, int y);
        virtual int getPosX();
        void setPosX(int x);
        virtual int getPosY();
        void setPosY(int y);
        virtual void render(int cameraX, int cameraY) = 0;
        virtual void update() = 0;
        bool isColliding(CEntity* entity, int x, int y);
        bool isReadyToRemove();
        bool canCollide();
        virtual void hurt(int damage);

    protected:
        bool m_shouldRemove;
        bool m_canCollide;
        int m_health;

    private:
        int m_posX;
        int m_posY;
};
