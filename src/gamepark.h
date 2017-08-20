#ifndef GAMEPARK_H
#define GAMEPARK_H

#include <irrlicht.h>
#include <stdio.h>
#include <iostream>
#include "config/config.h"
#include "player.h"
#include "myeventreceiver.h"
#include "childsquarenode.h"
#include "fountainsquarenode.h"
#include "attractionsquarenode.h"

using namespace irr;

enum
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};



//========================================================================================

class GamePark
{
public:
    GamePark();
    ~GamePark();

    void exit();
    int run();

    void switchTerrainMaterial(video::E_MATERIAL_FLAG material);
    void switchTerrainDetailMap();
    void switchSkybox();
    void updateEnvironment(const core::stringw& str);

    template<typename T>
    void log(T string)
         {std::cout << string << std::flush << std::endl;}

    inline video::IVideoDriver *driver() const {return m_device->getVideoDriver();}
    inline scene::ISceneManager *smgr() const {return m_device->getSceneManager();}
    inline gui::IGUIEnvironment *env() const {return m_device->getGUIEnvironment();}
    inline IrrlichtDevice *device() const {return m_device;}






    scene::ICameraSceneNode*  camera = nullptr;
    scene::ICameraSceneNode*  camera2 = nullptr;

    scene::ITerrainSceneNode* terrain = nullptr;

    io::IReadFile *heightmap = nullptr;
    Config m_config;

    bool shadows = true;
    bool freefly = false;
    bool gameMode = false;

    bool walking = false;
    bool isFire = false;
    bool usl_exit = false;


    bool key_w = false;
    bool key_a = false;
    bool key_s = false;
    bool key_d = false;




    Player *player() const;

    scene::IAnimatedMeshSceneNode *movableNode() const;

private:
    IrrlichtDevice* m_device = nullptr;
    Player* m_player = nullptr;
    scene::ISceneNode* skybox = nullptr;
    scene::ISceneNode* skydome = nullptr;
    MyEventReceiver* receiver = nullptr;
    gui::IGUIStaticText* m_controlText = nullptr;
    gui::IGUIStaticText* m_fpsText = nullptr;
    const int m_forestSize = 5;
    scene::IMeshSceneNode* m_forest[5];
    FountainSquareNode* m_fountainSquareNode = nullptr;
    ChildSquareNode* m_childSquareNode = nullptr;
    AttractionSquareNode* m_attractionSquareNode = nullptr;


    scene::IAnimatedMeshSceneNode* m_movableNode = nullptr;
    unsigned short m_checkLodCounter;

    void forestLOD(core::vector3df pos);
    int initDriver();
    void initEnvironment();
    void initPlayer();
    int initWater();
    int initFountain();
    int initChildSquare();
    int initAttractionSquare();
    int initWorld();
    int initTerrain();
    int initSkybox();
    int initLight();
    int initReceiver();
    int initTestObj();
    int initForest();
    int initGrass();
    int initRoads();
    int initCurb();
    int initPlanes();
    int initEagle(core::vector3df center, float radius, float speed = 0.2);
    void setCollision(scene::IAnimatedMeshSceneNode* node,
                      Player* player);
    void setCollision(scene::IMeshSceneNode* node,
                      Player* player);
    video::ITexture* texture(const io::path &textureName);

};

#endif // GAMEPARK_H
