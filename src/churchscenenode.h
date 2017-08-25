#ifndef CHURCHSCENENODE_H
#define CHURCHSCENENODE_H

#include <irrlicht.h>
#include "player.h"
#include "abstractscenenode.h"

class ChurchSceneNode : public AbstractSceneNode
{
public:
    ChurchSceneNode(irr::IrrlichtDevice* device, Player* player);

    int load();

private:
    int initWall();
    int initRoof();
    int initSkeleton();
    int initBase();
    int initDoors();
    int initWindows();
    int initDoorFrame();
    int initDecor();
    int initBell();

    irr::core::vector3df pos;
    irr::core::vector3df scale;
};

#endif // CHURCHSCENENODE_H
