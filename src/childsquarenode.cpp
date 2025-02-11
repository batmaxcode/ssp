#include "childsquarenode.h"
#include "collision.h"

using namespace irr;

ChildSquareNode::ChildSquareNode(irr::IrrlichtDevice* device, Player* player) :
    AbstractSceneNode(device, player)
{
}

int ChildSquareNode::load()
{
    initSquare();
    initFortNew();
//    initFort();
//    initBridge();
    initAnimals();
    return 0;
}

int ChildSquareNode::initAnimals()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    core::vector3df pos;
    core::vector3df scale;

    // croco
    pos = core::vector3df(9590, 340, 48760);
    scale = core::vector3df(75.0f,75.0f,75.0f);
    mesh = getMesh("animals.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(scale);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(pos);
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialTexture( 0, texture("rock_dirty.jpg") );
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(20,20);

        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChildSquareNode::initFortNew()
{
    scene::IMesh* mesh = getMesh("child_square_fort_new.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(252.0f,252.0f,252.0f));
        node->setPosition(core::vector3df(9840, 320, 48670));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        log("+++");
        log(node->getMaterialCount());
        node->getMaterial(0).setTexture(0,texture("brick.jpg") );
        node->getMaterial(1).setTexture(0,texture("brick.jpg") );
        node->getMaterial(2).setTexture(0,texture("fort_stone.jpg") );
        node->getMaterial(3).setTexture(0,texture("bridge.jpg") );
        node->getMaterial(4).setTexture(0,texture("rock_dirty.jpg") );
        node->getMaterial(5).setTexture(0,texture("hotel_darkBrick.jpg") );
    }
//    Collision::setCollision(node, m_player, m_smgr);
    return 0;
}

int ChildSquareNode::initFort()
{
    // stone
    scene::IMesh* mesh = getMesh("child_square_fort_stone.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(252.0f,252.0f,252.0f));
        node->setPosition(core::vector3df(9840, 320, 48670));

        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture( 0, texture("fort_stone.jpg") );
//        node->setMaterialType(video::EMT_LIGHTMAP);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->getMaterial(0).NormalizeNormals = true;
//        node->getMaterial(0).TextureLayer[1].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(20,20);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

    }
    Collision::setCollision(node, m_player, m_smgr);

    // brick
    mesh = getMesh("child_square_fort_brick.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(252.0f,252.0f,252.0f));
        node->setPosition(core::vector3df(9840, 320, 48670));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture( 0, texture("brick.jpg") );
//        node->setMaterialType(video::EMT_LIGHTMAP);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->getMaterial(0).NormalizeNormals = true;
//        node->getMaterial(0).TextureLayer[1].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(6,6);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

    }
    Collision::setCollision(node, m_player, m_smgr);
    return 0;
}

int ChildSquareNode::initSquare()
{
    scene::IMesh* mesh = getMesh("child_square.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(252.0f,252.0f,252.0f));
        node->setPosition(core::vector3df(9840, 330, 48670));

        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);

        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture(0, texture("sand3.jpg") );
        node->setMaterialTexture(1, texture("child_square_shadow.jpg"));
        node->setMaterialType(video::EMT_LIGHTMAP);
        node->getMaterial(0).NormalizeNormals = true;
        node->getMaterial(0).TextureLayer[1].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(20,20);
//        node->getMaterial(0).getTextureMatrix(1).setTextureScale(3.9,3.9);
//        node->getMaterial(0).getTextureMatrix(1).setTextureTranslate(0,0);
        //cube->getMaterial(0).getTextureMatrix(0).setTextureScale(u/3, v/3);
        //cube->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;
        //cube->getMaterial(0).TextureLayer->TextureWrapV = video::ETC_REPEAT;
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

    }
    Collision::setCollision(node, m_player, m_smgr);
    return 0;
}

int ChildSquareNode::initBridge()
{
    // stone
    scene::IMesh* mesh = getMesh("child_square_fort_bridge.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(252.0f,252.0f,252.0f));
        node->setPosition(core::vector3df(9840, 320, 48670));

        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture( 0, texture("bridge.jpg") );
//        node->setMaterialType(video::EMT_LIGHTMAP);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->getMaterial(0).NormalizeNormals = true;
//        node->getMaterial(0).TextureLayer[1].AnisotropicFilter = 16;
//        node->getMaterial(0).getTextureMatrix(0).setTextureScale(20,20);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

    }
    Collision::setCollision(node, m_player, m_smgr);
    return 0;
}

