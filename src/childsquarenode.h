#ifndef CHILDSQUARENODE_H
#define CHILDSQUARENODE_H

#include <irrlicht.h>
#include "player.h"
#include "abstractscenenode.h"

class ChildSquareNode : public AbstractSceneNode
{
public:
    ChildSquareNode(irr::IrrlichtDevice* device, Player* player);

    int load();

private:
    int initAnimals();
    int initFort();
    int initSquare();
    int initBridge();
};

#endif // CHILDSQUARENODE_H
