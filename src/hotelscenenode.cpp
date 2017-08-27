#include "hotelscenenode.h"
#include "collision.h"

using namespace irr;

HotelSceneNode::HotelSceneNode(irr::IrrlichtDevice* device, Player* player) :
    AbstractSceneNode(device, player)
{
    pos = core::vector3df(7880.0f, 1200.0f, 38760.0f);
    scale = core::vector3df(195.0f,195.0f,195.0f);
    rot = core::vector3df(0.0f,-90.0f,0.0f);
}

int HotelSceneNode::load()
{
//    initBrick();
//    initDarkBrick();
//    initWindows();
//    initBeton();
//    initDoors();
    initHotel();
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

int HotelSceneNode::initHotel()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;

    mesh = getMesh("hotel.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(scale);
        node->setPosition(pos);
        node->setRotation(rot);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

        log("---");
        log(node->getMaterialCount());
        node->getMaterial(0).setTexture( 0, texture("hotel_doors.jpg") );
        node->getMaterial(1).setTexture( 0, texture("hotel_brick.jpg") );
        node->getMaterial(2).setTexture( 0, texture("hotel_brick.jpg") );
        node->getMaterial(3).setTexture( 0, texture("hotel_brick.jpg") );
        node->getMaterial(4).setTexture( 0, texture("hotel_wood.jpg") );
        node->getMaterial(5).setTexture( 0, texture("hotel_wood.jpg") );
        node->getMaterial(6).setTexture( 0, texture("hotel_beton.jpg") );
        node->getMaterial(7).setTexture( 0, texture("hotel_doors.jpg") );
        node->getMaterial(8).setTexture( 0, texture("hotel_doors.jpg") );
        node->getMaterial(9).setTexture( 0, texture("hotel_windows.tga") );
        node->getMaterial(10).setTexture( 0, texture("hotel_darkBrick.jpg") );
        node->getMaterial(11).setTexture( 0, texture("hotel_brick.jpg") );
        node->getMaterial(12).setTexture( 0, texture("hotel_windows_2.jpg") );


        mesh->drop();
    }

    return 0;
}
