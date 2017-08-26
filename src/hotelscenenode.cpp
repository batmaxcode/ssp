#include "hotelscenenode.h"
#include "collision.h"

using namespace irr;

HotelSceneNode::HotelSceneNode(irr::IrrlichtDevice* device, Player* player) :
    AbstractSceneNode(device, player)
{
    pos = core::vector3df(7880, 1200, 38760);
    scale = core::vector3df(195.0f,195.0f,195.0f);
    rot = core::vector3df(0,-90,0);
}

int HotelSceneNode::load()
{
    initBrick();
    initDarkBrick();
    initWindows();
    initBeton();
    initDoors();
    return 0;
}

int HotelSceneNode::initBrick()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("hotel_brick.b3d");
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
        node->setRotation(rot);
        node->setMaterialTexture( 0, texture("hotel_brick.jpg") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);

        mesh->drop();
    }

    return 0;
}

int HotelSceneNode::initDarkBrick()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("hotel_darkBrick.b3d");
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
        node->setRotation(rot);
        node->setMaterialTexture( 0, texture("hotel_darkBrick.jpg") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

        mesh->drop();
    }

    return 0;
}

int HotelSceneNode::initWindows()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("hotel_windows.b3d");
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
        node->setRotation(rot);
        node->setMaterialTexture( 0, texture("hotel_windows.tga") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

        mesh->drop();
    }

    return 0;
}

int HotelSceneNode::initBeton()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("hotel_beton.b3d");
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
        node->setRotation(rot);
        node->setMaterialTexture( 0, texture("hotel_beton.jpg") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

        mesh->drop();
    }

    return 0;
}

int HotelSceneNode::initDoors()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("hotel_doors.b3d");
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
        node->setRotation(rot);
        node->setMaterialTexture( 0, texture("hotel_doors.jpg") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

        mesh->drop();
    }

    return 0;
}
