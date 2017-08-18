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
    inline irr::video::ITexture* texture(const irr::io::path &filename)
           {return m_driver->getTexture(irr::core::stringc("../../media/textures/")+filename);}
    inline irr::scene::IAnimatedMesh* getMesh(const irr::io::path &filename)
           {return m_smgr->getMesh(irr::core::stringc("../../media/models/")+filename);}

protected:
    irr::scene::ISceneManager* m_smgr;
    irr::video::IVideoDriver* m_driver;
    irr::IrrlichtDevice* m_device;
    Player* m_player;
    bool m_fog;
};

#endif // ABSTRACTSCENENODE_H
