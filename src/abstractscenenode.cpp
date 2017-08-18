#include "abstractscenenode.h"
#include "collision.h"

using namespace irr;

AbstractSceneNode::AbstractSceneNode(irr::IrrlichtDevice* device, Player* player) :
    m_smgr(device->getSceneManager()),
    m_driver(device->getVideoDriver()),
    m_device(device),
    m_player(player),
    m_fog(false)
{
}

AbstractSceneNode::~AbstractSceneNode()
{

}

int AbstractSceneNode::load()
{
    return 0;
}


