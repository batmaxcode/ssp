#ifndef FOUNTAINSQUARENODE_H
#define FOUNTAINSQUARENODE_H

#include <irrlicht.h>
#include "player.h"
#include "abstractscenenode.h"

class FountainSquareNode : public AbstractSceneNode
{
public:
    FountainSquareNode(irr::IrrlichtDevice* device, Player* player);

    int load();

private:
    int initFountainNew();
    int initFountain();
    int initSquare();
    int initFlagpole();
    int initOpeningMonument();
    int initStoneBench();

    int createPlane(int x, int y,int z,int u,int v,int rx,int ry,int rz);
};

#endif // FOUNTAINSQUARENODE_H
