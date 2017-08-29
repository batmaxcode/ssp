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
    initCarousel();
    initWheel();
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
        node->setScale(core::vector3df(45.0f,45.0f,45.0f)); //50.2
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(17760,350,45090)); //height 1500*2
        node->setRotation(core::vector3df(0,150,0));
        //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        //node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->getMaterial(0).setTexture( 0, texture("metal_rzav.jpg") );
        node->getMaterial(1).setTexture( 0, texture("iron_green.jpg") );
        node->getMaterial(2).setTexture( 0, texture("iron_gray.jpg") );
        node->getMaterial(3).setTexture( 0, texture("iron_gray.jpg") );
        node->getMaterial(4).setTexture( 0, texture("iron_blue.jpg") );
        node->getMaterial(5).setTexture( 0, texture("iron_yellow.jpg") );
        node->getMaterial(6).setTexture( 0, texture("iron.jpg") );
        node->getMaterial(7).setTexture( 0, texture("rotor.png") );
        node->getMaterial(8).setTexture( 0, texture("rotor.png") );
        node->getMaterial(11).setTexture( 0, texture("grid.png") );
log("-=-=-=-");
log(node->getMaterialCount());
//        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
//        node->getMaterial(0).getTextureMatrix(0).setTextureScale(30,30);
        node->getMaterial(11).MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
        node->getMaterial(11).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(11).getTextureMatrix(0).setTextureScale(3,3);



//        node->getMaterial(0).setTexture( 0, texture("metal_rzav.jpg") );
//        node->getMaterial(1).setTexture( 0, texture("iron_green.jpg") );
//        node->getMaterial(2).setTexture( 0, texture("iron_gray.jpg") );
//        node->getMaterial(3).setTexture( 0, texture("iron_gray.jpg") );
//        node->getMaterial(4).setTexture( 0, texture("iron_blue.jpg") );
//        node->getMaterial(5).setTexture( 0, texture("iron_yellow.jpg") );
//        node->getMaterial(6).setTexture( 0, texture("iron.jpg") );
//        node->getMaterial(7).setTexture( 0, texture("rotor.png") );
//        node->getMaterial(8).setTexture( 0, texture("rotor.png") );
//        node->getMaterial(9).setTexture( 0, texture("iron.jpg") );
//        node->getMaterial(10).setTexture( 0, texture("grid.png") );

//        node->getMaterial(11).setTexture( 0, texture("russia.png") );
//        node->getMaterial(12).setTexture( 0, texture("waterbump.png") );
//        node->getMaterial(13).setTexture( 0, texture("waterbump.png") );
//        node->getMaterial(14).setTexture( 0, texture("waterbump.png") );
//        node->getMaterial(15).setTexture( 0, texture("waterbump.png") );
//        node->getMaterial(16).setTexture( 0, texture("waterbump.png") );


        //node->addShadowVolumeSceneNode(0,-1,false,10000);
        //node->getMaterial(0).NormalizeNormals = true;
//        node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        //node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        Collision::setCollision(node, m_player, m_smgr);
    }
    return 0;
}

int AttractionSquareNode::initCarousel()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    // carousel
    mesh = getMesh("carousel.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(45.0f,45.0f,45.0f)); //50.2
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(20610,350,41610)); //height 1500*2
        //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        //node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->setMaterialTexture( 0, texture("carousel.png") );
//        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        //node->addShadowVolumeSceneNode(0,-1,false,10000);
        //node->getMaterial(0).NormalizeNormals = true;
//        node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        //node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);
    }
    // horses
    mesh = getMesh("carousel_horses.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(45.0f,45.0f,45.0f)); //50.2
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(20610,350,41610)); //height 1500*2
        //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        //node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->setMaterialTexture( 0, texture("carousel_horse_texture.png") );
//        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        //node->addShadowVolumeSceneNode(0,-1,false,10000);
        //node->getMaterial(0).NormalizeNormals = true;
//        node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        //node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node, m_player, m_smgr);
    }
    return 0;
}

int AttractionSquareNode::initWheel()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    mesh = getMesh("koleso.b3d");
    if (!mesh)
    {
       m_device->drop();
       return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
       node->setScale(core::vector3df(45.2f,45.2f,45.2f)); //50.2
       node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
       node->setPosition(core::vector3df(23480,1350*2,37580)); //height 1500*2
       node->setRotation(core::vector3df(0,65,0));
       //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
       //node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
       node->setMaterialTexture( 0, texture("metal_rzav.jpg") );
       node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
       //node->addShadowVolumeSceneNode(0,-1,false,10000);
       //node->getMaterial(0).NormalizeNormals = true;
       //node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
       //node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
       node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

    }
    return 0;
}
