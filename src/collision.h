#ifndef COLLISION_H
#define COLLISION_H

#include <irrlicht.h>
#include "player.h"



class Collision
{
public:
    Collision();

    static void setCollision(irr::scene::IAnimatedMeshSceneNode *node, Player *player,
                             irr::scene::ISceneManager* smgr)
    {
        irr::scene::IMeshSceneNode* sceneNode;
        sceneNode = (irr::scene::IMeshSceneNode*)node;
        setCollision(sceneNode, player, smgr);
    }

    static void setCollision(irr::scene::IMeshSceneNode *node, Player *player,
                             irr::scene::ISceneManager* smgr)
    {
        irr::scene::ITriangleSelector* selector = smgr->createOctreeTriangleSelector(node->getMesh(),node,128);
        node->setTriangleSelector(selector);
        irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector,
            player->camera(),player->ellipsoid(),
            irr::core::vector3df(0,0,0),irr::core::vector3df(0,-100,0));
        selector->drop();
        player->camera()->addAnimator(anim);
        anim->drop();
    }
};



#endif // COLLISION_H
