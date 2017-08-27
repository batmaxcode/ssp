#ifndef HOTELSCENENODE_H
#define HOTELSCENENODE_H

#include <irrlicht.h>
#include "player.h"
#include "abstractscenenode.h"

class HotelSceneNode : public AbstractSceneNode
{
public:
    HotelSceneNode(irr::IrrlichtDevice* device, Player* player);

    int load();

private:
    int initBrick();
    int initDarkBrick();
    int initWindows();
    int initBeton();
    int initDoors();
    int initHotel();

    irr::core::vector3df pos;
    irr::core::vector3df scale;
    irr::core::vector3df rot;
};

#endif // HOTELSCENENODE_H
