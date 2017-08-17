#ifndef CHILDSQUARENODE_H
#define CHILDSQUARENODE_H

#include <irrlicht.h>
#include "player.h"

class ChildSquareNode
{
public:
    ChildSquareNode(irr::IrrlichtDevice* device, Player* player);

    int load();
    inline bool fog() const {return m_fog;}
    inline void setFog(bool fog) {m_fog = fog;}

private:
    irr::scene::ISceneManager* m_smgr;
    irr::video::IVideoDriver* m_driver;
    irr::IrrlichtDevice* m_device;
    Player* m_player;
    bool m_fog;

    int initAnimals();
    int initFort();
    int initSquare();
    int initBridge();
};

#endif // CHILDSQUARENODE_H
