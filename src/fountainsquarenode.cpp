#include "fountainsquarenode.h"
#include "collision.h"

using namespace irr;

FountainSquareNode::FountainSquareNode(irr::IrrlichtDevice* device, Player* player) :
    AbstractSceneNode(device, player)
{
}

int FountainSquareNode::load()
{
    initFountainNew();
    initSquare();
//    initFountain();
//    initFlagpole();
    initOpeningMonument();
//    initStoneBench();
    return 0;
}

scene::ISceneNode *FountainSquareNode::node()
{
    return m_node;
}

int FountainSquareNode::initFountainNew()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    mesh = getMesh("fountain.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(270.0f,270.0f,270.0f));
        node->setPosition(core::vector3df(9160,235*2,58440));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);

        node->getMaterial(0).setTexture(0, texture("fountain.jpg") );
        node->getMaterial(1).setTexture(0, texture("iron_gray.jpg") );
        node->getMaterial(2).setTexture(0, texture("camen4.jpg") );
        node->getMaterial(3).setTexture(0, texture("lenin.png"));
        node->getMaterial(3).setTexture(1, texture("grass_dirty.jpg"));
        node->getMaterial(3).getTextureMatrix(1).setTextureScale(10,10);
        node->getMaterial(3).MaterialType = video::EMT_DETAIL_MAP;
        node->getMaterial(4).setTexture(0, texture("camen.jpg"));
        node->getMaterial(4).setTexture(1, texture("grass_dirty.jpg"));
        node->getMaterial(4).getTextureMatrix(1).setTextureScale(10,10);
        node->getMaterial(4).MaterialType = video::EMT_DETAIL_MAP;
        node->getMaterial(5).setTexture(0, texture("plita-daleko.png"));
        node->getMaterial(5).setTexture(1, texture("plita-2.jpg"));
        node->getMaterial(5).MaterialType = video::EMT_DETAIL_MAP;
        node->getMaterial(5).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(6).setTexture(0, texture("iron.jpg") );

        Collision::setCollision(node,m_player,m_smgr);

        m_node = node;
    }
    return 0;
}

int FountainSquareNode::initFountain()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    mesh = getMesh("fountain.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(270.0f,270.0f,270.0f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(9160,235*2,58440));
        node->setRotation(core::vector3df(0,180,0));

        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

        //node->setMaterialFlag(video::EMF_GOURAUD_SHADING,false);
        //node->setMaterialFlag(video::EMT_S,false);
        node->setMaterialTexture(0, texture("fountain.jpg") );
        //node->setMaterialTexture( 1, texture("post_apok.jpg") );
        //node->setMaterialType(video::EMT_LIGHTMAP);

        node->getMaterial(0).NormalizeNormals = true;
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node,m_player,m_smgr);
    }
    // label
    mesh = getMesh("fountain_label.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(270.0f,270.0f,270.0f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(9160,235*2,58440));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture( 0, texture("iron.jpg") );
        node->getMaterial(0).NormalizeNormals = true;
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        //node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
    }
    return 0;
}

int FountainSquareNode::initSquare()
{
    scene::IMesh* mesh = getMesh("fountain_square.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(770.0f,770.0f,770.0f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(4990*2,180*2,29400*2));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture(0, texture("sand3.jpg") );
        node->setMaterialTexture(1, texture("shadow.jpg"));
        node->setMaterialType(video::EMT_LIGHTMAP);
        node->getMaterial(0).NormalizeNormals = true;
        node->getMaterial(0).TextureLayer[1].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(25,25);
        node->getMaterial(0).getTextureMatrix(1).setTextureScale(1.135,1.141);
        node->getMaterial(0).getTextureMatrix(1).setTextureTranslate(0.88,0.942);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node,m_player,m_smgr);
    }
    return 0;
}

int FountainSquareNode::initFlagpole()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    // flagstaff
    mesh = getMesh("flagstaff.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(270.0f,270.0f,270.0f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(9160,235*2,58440));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture( 0, texture("iron_gray.jpg") );
        node->getMaterial(0).NormalizeNormals = true;
        node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
    }
    // flags
    scene::IAnimatedMesh* animatedMesh;
    scene::ISceneNode* flagnode;
    animatedMesh = getMesh("flag.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    flagnode = m_smgr->addWaterSurfaceSceneNode(animatedMesh->getMesh(0), 3.0f, 600.0f, 3.0f);
    if (flagnode)
    {
        flagnode->setScale(core::vector3df(17.0f,17.0f,17.0f));
        flagnode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        flagnode->setPosition(core::vector3df(12640,1055*2,57550));
        flagnode->setRotation(core::vector3df(0,180,0));
        flagnode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        flagnode->setMaterialTexture( 0, texture("russia.png") );
        flagnode->getMaterial(0).NormalizeNormals = true;
        flagnode->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        flagnode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    }
    mesh = getMesh("flag2.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    flagnode = m_smgr->addWaterSurfaceSceneNode(animatedMesh->getMesh(0), 1.0f, 600.0f, 3.0f);
    if (flagnode)
    {
        flagnode->setScale(core::vector3df(17.0f,17.0f,17.0f));
        flagnode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        flagnode->setPosition(core::vector3df(12890,1155*2,57550));
        flagnode->setRotation(core::vector3df(0,180,0));
        flagnode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        flagnode->setMaterialTexture( 0, texture("saintp.png") );
        flagnode->getMaterial(0).NormalizeNormals = true;
        flagnode->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        flagnode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    }
    return 0;
}

int FountainSquareNode::initOpeningMonument()
{
//    scene::IMesh* mesh;
//    scene::IMeshSceneNode* node;
//    // stairs
//    mesh = getMesh("monument_stairs.b3d");
//    if (!mesh)
//    {
//        m_device->drop();
//        return 1;
//    }
//    node = m_smgr->addMeshSceneNode( mesh );
//    if (node)
//    {
//        node->setScale(core::vector3df(45.0f,45.0f,45.0f));
//        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
//        node->setPosition(core::vector3df(8800*2,200*2,29800*2));
//        node->setMaterialTexture( 0, texture("camen.jpg") );
//        node->setMaterialTexture( 1, texture("grass_dirty.jpg"));
//        node->getMaterial(0).getTextureMatrix(1).setTextureScale(10,10);
//        node->setMaterialType(video::EMT_DETAIL_MAP);
//        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
//        Collision::setCollision(node,m_player,m_smgr);
//    }
    createPlane(8680*2,180*2,29800*2,13.6,10,0,0,5);
    createPlane(9335*2,285*2,29800*2,13.6,23,0,0,0);
    createPlane(9997*2,285*2,29800*2,25,30,0,0,0);
    // monument
//    mesh = getMesh("monument.b3d");
//    if (!mesh)
//    {
//        m_device->drop();
//        return 1;
//    }
//    node = m_smgr->addMeshSceneNode( mesh );
//    if (node)
//    {
//        node->setScale(core::vector3df(45.0f,45.0f,45.0f));
//        node->setRotation(core::vector3df(0,90,0));
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
//        node->setPosition(core::vector3df(20040,600,59600));
//        node->getMaterial(0).setTexture(0, texture("lenin.png"));
//        node->getMaterial(0).setTexture(1, texture("grass_dirty.jpg"));
//        node->getMaterial(0).getTextureMatrix(1).setTextureScale(10,10);
//        node->getMaterial(0).MaterialType = video::EMT_DETAIL_MAP;
//        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
//        Collision::setCollision(node,m_player,m_smgr);
//    }

    return 0;
}

int FountainSquareNode::initStoneBench()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    mesh = getMesh("stone_bench.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = m_smgr->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(770.0f,770.0f,770.0f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(4990*2,180*2,29400*2));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialTexture( 0, texture("camen4.jpg") );

        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        //cube->getMaterial(0).getTextureMatrix(0).setTextureScale(u/3, v/3);
        //cube->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;
        //cube->getMaterial(0).TextureLayer->TextureWrapV = video::ETC_REPEAT;
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);
        Collision::setCollision(node,m_player,m_smgr);

    }

    mesh->drop();
    return 0;
}

int FountainSquareNode::createPlane(int x, int y,int z,int u,int v,
                                    int rx=0,int ry=0,int rz=0)
{
    scene::ISceneNode* cube = m_smgr->addCubeSceneNode(50.0f);

    cube->setPosition(core::vector3df(x,y,z));
    cube->setMaterialTexture(0, texture("road_stone.jpg"));
    cube->setMaterialTexture(1, texture("grass_dirty.jpg"));
    cube->setMaterialType(video::EMT_DETAIL_MAP);
    cube->setScale(core::vector3df(v,1.0f,u));
    cube->setRotation(core::vector3df(rx,ry,rz));
    cube->getMaterial(0).getTextureMatrix(0).setTextureScale(u/3, v/3);
    cube->getMaterial(0).getTextureMatrix(1).setTextureScale(3,3);
    cube->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;
    cube->getMaterial(0).TextureLayer->TextureWrapV = video::ETC_REPEAT;
    cube->setMaterialFlag(video::EMF_FOG_ENABLE, m_fog);

    return 0;
}
