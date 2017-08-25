#include "churchscenenode.h"
#include "collision.h"

using namespace irr;

ChurchSceneNode::ChurchSceneNode(irr::IrrlichtDevice* device, Player* player) :
    AbstractSceneNode(device, player)
{
    pos = core::vector3df(8390, 408, 40760);
    scale = core::vector3df(450.0f,450.0f,450.0f);
}

int ChurchSceneNode::load()
{
    initWall();
    initRoof();
    initSkeleton();
    initBase();
    initDoors();
    initWindows();
    initDoorFrame();
    initDecor();
    initBell();
    return 0;
}

int ChurchSceneNode::initWall()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_wall.b3d");
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
        node->setMaterialTexture( 0, texture("church_wall.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initRoof()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_roof.b3d");
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
        node->setMaterialTexture( 0, texture("church_roof.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initSkeleton()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_skeleton.b3d");
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
        node->setMaterialTexture( 0, texture("church_skeleton.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initBase()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_base.b3d");
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
        node->setMaterialTexture( 0, texture("church_base.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initDoors()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_doors.b3d");
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
        node->setMaterialTexture( 0, texture("church_doors.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initWindows()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_windows.b3d");
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
        node->setMaterialTexture( 0, texture("church_windows.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initDoorFrame()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_doorFrame.b3d");
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
        node->setMaterialTexture( 0, texture("church_doorFrame.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initDecor()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_decor.b3d");
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
        node->setMaterialTexture( 0, texture("church_decor.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int ChurchSceneNode::initBell()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("church_bell.b3d");
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
        node->setMaterialTexture( 0, texture("church_bell.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}
