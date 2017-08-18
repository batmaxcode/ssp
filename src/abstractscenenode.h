#ifndef ABSTRACTSCENENODE_H
#define ABSTRACTSCENENODE_H

#include <irrlicht.h>
#include "player.h"

class AbstractSceneNode
{
public:
    AbstractSceneNode(irr::IrrlichtDevice* device, Player* player);
    virtual ~AbstractSceneNode();

    virtual int load();
    inline bool fog() const {return m_fog;}
    inline void setFog(bool fog) {m_fog = fog;}

protected:
    irr::scene::ISceneManager* m_smgr;
    irr::video::IVideoDriver* m_driver;
    irr::IrrlichtDevice* m_device;
    Player* m_player;
    bool m_fog;
};

#endif // ABSTRACTSCENENODE_H
