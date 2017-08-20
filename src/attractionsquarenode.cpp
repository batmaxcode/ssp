#include "attractionsquarenode.h"
#include "collision.h"

using namespace irr;

AttractionSquareNode::AttractionSquareNode(irr::IrrlichtDevice* device, Player* player) :
    AbstractSceneNode(device, player)
{

}

int AttractionSquareNode::load()
{
    initTrack();
    return 0;
}

int AttractionSquareNode::initTrack()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    mesh = getMesh("track.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(43.0f,43.0f,43.0f)); //50.2
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(19960,650,45560)); //height 1500*2
        node->setRotation(core::vector3df(180,300,0));
        //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        //node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->setMaterialTexture( 0, texture("metal_rzav.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(20,20);
        //node->addShadowVolumeSceneNode(0,-1,false,10000);
        //node->getMaterial(0).NormalizeNormals = true;
        //node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        //node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        Collision::setCollision(node, m_player, m_smgr);
    }
    return 0;
}
