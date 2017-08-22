#ifndef ATTRACTIONSQUARENODE_H
#define ATTRACTIONSQUARENODE_H

#include <irrlicht.h>
#include "player.h"
#include "abstractscenenode.h"

class AttractionSquareNode : public AbstractSceneNode
{
public:
    AttractionSquareNode(irr::IrrlichtDevice* device, Player* player);

    int load();

private:
    int initTrack();
    int initCarousel();
    int initWheel();
};

#endif // ATTRACTIONSQUARENODE_H
