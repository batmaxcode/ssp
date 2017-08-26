#include "gamepark.h"
#include "myeventreceiver.h"
#include "config/inireader.h"
#include "RealisticWater.h"
#include "postprocessmotionblur.h"
#include "collision.h"
#include "common.h"
#include <irrKlang.h>
#include "TKGrassSceneNode.h"
#include "TKGrassSceneNode_ShaderCB.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#endif

using namespace irrklang;

GamePark::GamePark() :
    m_checkLodCounter(0)
{

    m_config.load("../../config/config.ini");

    initDriver();
    /*
     * Для начала добавим базовые элементы на сцену: окружение пользователя с текстом подсказок,
     * мир, игрока (камеру от первого лица)
    */
    initEnvironment();
    initPlayer();
    initWorld();
    initReceiver();
    initSounds();
}

GamePark::~GamePark()
{
    delete receiver;
    delete m_player;
    delete m_fountainSquareNode;
    delete m_childSquareNode;
}

void GamePark::exit()
{
    usl_exit = true;
}

int GamePark::initWorld()
{
    initTerrain();
//    initWater();
    initForest();
    initShrub();
    initScam();
//    initBench();
//    initGrass();
    initRoads();
    initCurb();
    initPlanes();
    initFountain();
    initChildSquare();
    initAttractionSquare();
    initSkybox();
    initLight();
    initTestObj();
    initGarbage();
    initChurch();
    initHotel();
    initEagle(core::vector3df(12000,2300,56000), 3900.0f, 0.08f);
    initEagle(core::vector3df(17000,2800,50000), 4200.0f, 0.06f);
    return 0;
}


int GamePark::initDriver()
{
    // создаем device c настройками взятыми из файла конифгурации,
    // при необходимости можно добавить больше параметров, проверьте
    // irr::SIrrlichtCreationParameters
    irr::SIrrlichtCreationParameters params = m_config.params();
    params.DriverType = irr::video::EDT_OPENGL;
    m_device = createDeviceEx(params);

    if (m_device == 0)
    {
        // не удалось создать device
        return 1;
    }

    // custom
    smgr()->setShadowColor(irr::video::SColor(150,0,0,0));		//shadow
    smgr()->setAmbientLight(video::SColorf(0.45,0.45,0.45,0.7)); // shadow color
    driver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
    if(m_config.fog() == true)
    {
        driver()->setFog(video::SColor(128,40,40,40), video::EFT_FOG_LINEAR, 250, 18000, .000f, true, false);
    }
    m_device->getCursorControl()->setVisible(false);


    return 0;
}

void GamePark::initEnvironment()
{
    int y = m_config.params().WindowSize.Height;
    // устанавливаем шрифт
    env()->getSkin()->setFont(env()->getFont("../../media/textures/fontlucida.png"));
    // добавляем вспомогательный текст
    m_controlText = env()->addStaticText(L"Use W,A,S,D to move\n"
                                         "Press 'Q' to change wireframe mode\n"
                                         "Press 'E' to toggle detail map\n"
                                         "Press 'R' to toggle skybox/skydome",
                                         core::rect<s32>(10,y-135,250,y-60),
                                         true, true, 0, -1, true);

    m_fpsText = env()->addStaticText(L"",
                                     core::rect<s32>(10,y-55,250,y-20),
                                     true, true, 0, -1, true);
}

void GamePark::initPlayer()
{
    m_player = new Player(device());
    smgr()->setActiveCamera(m_player->camera());

    m_player->setPosition(9160,535*2,58440);
//    m_player->setPosition(29160,535*2,50440); // озера
//    m_player->setPosition(59160,1035*2,58440); // берег у реки
//    m_player->setPosition(59160,1035*2,20440); // берег у залива
}

int GamePark::initWater()
{
    // создаение залива
//    const f32 width = 37120.0f;
//    const f32 height = 75120.0f;
//    RealisticWaterSceneNode* water = new RealisticWaterSceneNode(smgr(), width, height);
//    smgr()->getRootSceneNode()->addChild(water);
//    water->setPosition(core::vector3df(52160,35*2,34840));
//    water->setWaterColor(video::SColorf(0,0.5,0.5));
//    water->setWaveHeight(0.3f);
//    water->setWindForce(10.0f);


    // создание озер
    scene::IAnimatedMesh* mesh = smgr()->addHillPlaneMesh( "myHill",
        core::dimension2d<f32>(200,460),
        core::dimension2d<u32>(60,60), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(60,60));
    scene::ISceneNode* waternode;
    waternode = smgr()->addWaterSurfaceSceneNode(mesh->getMesh(0), 6.0f, 300.0f, 100.0f);
    waternode->setPosition(core::vector3df(35860,105*2,45900));
    waternode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    waternode->setMaterialTexture(0, texture("dirty2.jpg"));
    waternode->setMaterialTexture(1, texture("water_dirty.jpg"));

    waternode->getMaterial(0).getTextureMatrix(0).setTextureScale(0.5, 1);
    waternode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;
    //waternode->getMaterial(1).getTextureMatrix(1).setTextureScale(length/2, 1);
    //waternode->getMaterial(1).TextureLayer->TextureWrapU = video::ETC_REPEAT;

    waternode->setMaterialType(video::EMT_REFLECTION_2_LAYER);

    mesh->drop();
    //---------------------------------------------

    mesh = smgr()->addHillPlaneMesh( "myHill2",
        core::dimension2d<f32>(400,300),
        core::dimension2d<u32>(43,40), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(60,60));
    waternode = smgr()->addWaterSurfaceSceneNode(mesh->getMesh(0), 6.0f, 300.0f, 100.0f);
    waternode->setPosition(core::vector3df(51060,105*2,29800));
    waternode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    waternode->setMaterialTexture(0, texture("dirty2.jpg"));
    waternode->setMaterialTexture(1, texture("water_dirty.jpg"));

    waternode->getMaterial(0).getTextureMatrix(0).setTextureScale(1, 1);
    waternode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;

    waternode->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    m_movableNode = (scene::IAnimatedMeshSceneNode*)waternode;
    mesh->drop();

    //----------------------------------------------------
    // создвание залива (без шейдеров)

    mesh = smgr()->addHillPlaneMesh( "myHill3",
        core::dimension2d<f32>(500,800),
        core::dimension2d<u32>(90,80), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(60,60));
    waternode = smgr()->addWaterSurfaceSceneNode(mesh->getMesh(0), 6.0f, 300.0f, 100.0f);
    waternode->setPosition(core::vector3df(48600,95*2,29800));
    waternode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    waternode->setMaterialTexture(0, texture("dirty2.jpg"));
    waternode->setMaterialTexture(1, texture("water_dirty.jpg"));

    waternode->getMaterial(0).getTextureMatrix(0).setTextureScale(1, 1);
    waternode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;

    waternode->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    m_movableNode = (scene::IAnimatedMeshSceneNode*)waternode;
    mesh->drop();

    return 0;
}

int GamePark::initFountain()
{
    m_fountainSquareNode = new FountainSquareNode(device(), m_player);
    m_fountainSquareNode->setFog(m_config.fog());
    return m_fountainSquareNode->load();
}

int GamePark::initChildSquare()
{
    m_childSquareNode = new ChildSquareNode(device(), m_player);
    m_childSquareNode->setFog(m_config.fog());
    return m_childSquareNode->load();
}

int GamePark::initAttractionSquare()
{
    m_attractionSquareNode = new AttractionSquareNode(device(), m_player);
    m_attractionSquareNode->setFog(m_config.fog());
    return m_attractionSquareNode->load();
}

int GamePark::initChurch()
{
    m_churchSceneNode = new ChurchSceneNode(device(), m_player);
    m_churchSceneNode->setFog(m_config.fog());
    return m_churchSceneNode->load();
}

int GamePark::initHotel()
{
    m_hotelSceneNode = new HotelSceneNode(device(), m_player);
    m_hotelSceneNode->setFog(m_config.fog());
    return m_hotelSceneNode->load();
}

int GamePark::initTerrain()
{
    // добавление ландшафта
    terrain = smgr()->addTerrainSceneNode(
                    "../../media/textures/park-ter-5.png",
                    0,					// parent node
                    -1,					// node id
                    core::vector3df(0.f, 0.f, 0.f),		// position
                    core::vector3df(0.f, 0.f, 0.f),		// rotation
                    core::vector3df(60.0f, 3.0f, 60.0f),	// scale
                    video::SColor ( 255, 255, 255, 255 ),	// vertexColor
                    6,					// maxLOD
                    scene::ETPS_17,				// patchSize
                    3					// smoothFactor
                    );
    terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0, texture("park-textura-5.png"));
    terrain->setMaterialTexture(1, texture("grass_dirty.jpg"));
    terrain->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
    terrain->scaleTexture(1.0f, 390.0f);
    if(m_config.fog() == true)
    {
        terrain->setMaterialFlag(video::EMF_FOG_ENABLE, true);
    }

    if(m_config.freeFly() == false)
    {
        // создаем trangle selector для ландшафта
        scene::ITriangleSelector* selector
            = smgr()->createTerrainTriangleSelector(terrain, 0);
        terrain->setTriangleSelector(selector);

        // создаем аниматор столкновений с селектором и прикрепляем его к игроку
        scene::ISceneNodeAnimator* anim = smgr()->createCollisionResponseAnimator(
            selector, m_player->camera(), m_player->ellipsoid(),
            core::vector3df(0,-8,0),
            core::vector3df(0, -100,0));
        selector->drop();
        m_player->camera()->addAnimator(anim);
        anim->drop();
    }

    /* Если вам нужен доступ к данным ландшафта, вы также можете сделать это
     *  напрямую с помощью следующего фрагмента кода.
    */
    scene::CDynamicMeshBuffer* buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
    terrain->getMeshBufferForLOD(*buffer, 0);
    //video::S3DVertex2TCoords* data = (video::S3DVertex2TCoords*)buffer->getVertexBuffer().getData();
    // Работайте с данными или получите IndexBuffer с аналогичным вызовом.
    buffer->drop(); // При завершении снова сбрасываем буфер

    return 0;
}

int GamePark::initSkybox()
{
    /*
     * Чтобы пользователь мог переключаться между обычным и каркасным режимами,
     * мы создаем экземпляр приемника событий сверху и позволяем Irrlicht знать
     * об этом. Кроме того, мы добавляем skybox, который мы уже использовали
     * во многих примерах Irrlicht, и skydome, который показан взаимоисключающим
     *  с skybox, нажав «S».
    */

    // создание skybox и skydome
    driver()->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

    skybox=smgr()->addSkyBoxSceneNode(texture("irrlicht2_up.jpg"),
                                      texture("irrlicht2_dn.jpg"),
                                      texture("irrlicht2_lf.jpg"),
                                      texture("irrlicht2_rt.jpg"),
                                      texture("irrlicht2_ft.jpg"),
                                      texture("irrlicht2_bk.jpg"));
    skydome=smgr()->addSkyDomeSceneNode(texture("skydome.jpg"),16,8,0.95f,2.0f);
    skybox->setVisible(true);
    skydome->setVisible(false);

    driver()->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    return 0;
}

int GamePark::initLight()
{
    // Добавляем свет, чтобы невыбранные ноды не были полностью черными.
    scene::ILightSceneNode * light = smgr()->addLightSceneNode(0, core::vector3df(10700*2,2585*2,32600*2),
        video::SColorf(0.8f,0.8f,0.8f,1.0f), 20000.0f);
    light->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    light->setID(ID_IsNotPickable);
    return 0;
}

int GamePark::initReceiver()
{
    // создаем event receiver
    receiver = new MyEventReceiver(this);
    m_device->setEventReceiver(receiver);
    return 0;
}

int GamePark::initTestObj()
{
//    scene::IAnimatedMesh* mesh = m_device->getSceneManager()->getMesh(Common::modelsPath()+"wolf.x");
//    if (!mesh)
//    {
//        m_device->drop();
//    }
//    scene::IAnimatedMeshSceneNode* node = m_device->getSceneManager()->addAnimatedMeshSceneNode(mesh );
//    if (node)
//    {
//        //animnode->setScale(core::vector3df(30.0f,30.0f,30.0f));
//        node->setScale(core::vector3df(300.0f,300.0f,300.0f));
////        if(shadows)
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
//        //node->setPosition(core::vector3df(27,-40,20));
//        node->setPosition(m_player->camera()->getPosition());
//        //animnode->setPosition(core::vector3df(9170,610*2,60540));
//        node->setRotation(core::vector3df(0,180,0));
//        //node->addShadowVolumeSceneNode();
////        m_node->setMaterialTexture( 0, m_device->getVideoDriver()->getTexture("../../media/textures/ak12.png") );
//        node->setAnimationSpeed(10.f);
//        node->setFrameLoop(0,17);
////        setCollision(node, m_player);

//    }
    return 0;
}

int GamePark::initForest()
{
    core::vector3df pos[m_forestSize];
    pos[0] = core::vector3df(20000,260*2,59360);
    pos[1] = core::vector3df(43630,260*2,49760);
    pos[2] = core::vector3df(15060,260*2,33010);
    pos[3] = core::vector3df(46400,260*2,26800);
    pos[4] = core::vector3df(46400,260*2,26800);
    core::vector3df scale = core::vector3df(70.0f,70.0f,70.0f);

    for(int i=0;i<m_forestSize;i++)
    {
        core::stringc postfix = core::stringc(i+1)+".b3d";
        core::stringc postfixLow = core::stringc(i+1)+"_low.b3d";
        scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"forest_"+postfix);
        if (!mesh)
        {
            m_device->drop();
            return 1;
        }
        scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
        if (node)
        {
            node->setScale(scale);
            node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
            node->setPosition(pos[i]);
            node->setRotation(core::vector3df(0,180,0));
            node->setMaterialTexture( 0, texture("tree.jpg") );
            node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
            if(m_config.fog() == true)
            {
                node->setMaterialFlag(video::EMF_FOG_ENABLE, true);
            }
        }
//        setCollision(node, m_player);
        m_forest[i] = node;

        mesh = smgr()->getMesh(Common::modelsPath()+"forest_"+postfixLow);
        if (!mesh)
        {
            m_device->drop();
            return 1;
        }
        node = smgr()->addMeshSceneNode( mesh );
        if (node)
        {
            node->setScale(scale);
            node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
            node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
            node->setPosition(pos[i]);
            node->setRotation(core::vector3df(0,180,0));
            node->setMaterialTexture( 0, texture("tree_spherical_1_2.png") );

        }
        mesh->drop();
    }
    return 0;
}

int GamePark::initShrub()
{
    scene::IMesh* mesh;
    scene::IMeshSceneNode* node;
    mesh = smgr()->getMesh(Common::modelsPath()+"shrub_1.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(3.2f,3.2f,3.2f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setPosition(core::vector3df(28540,0,60340));
        node->setRotation(core::vector3df(0,180,0));
        //node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->setMaterialTexture( 0, texture("textura_kust_2.png") );
        //node->getMaterial(0).NormalizeNormals = true;
        node->getMaterial(0).TextureLayer[0].BilinearFilter = true;
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());
        //node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);

    }
    return 0;
}

int GamePark::initScam()
{
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"scam_1_2.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(147.0f,147.0f,147.0f));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(13060,140,58320));
        node->setMaterialTexture( 0, texture("scam.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());

    }
    setCollision(node,m_player);
    mesh->drop();
    return 0;
}

int GamePark::initBench()
{
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"bench.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(51.0f,51.0f,51.0f));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(14070,389,56270));
        node->setMaterialTexture( 0, texture("bench.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());

    }
    setCollision(node,m_player);
    mesh->drop();
    return 0;
}

int GamePark::initGrass()
{
    core::vector3df scale = core::vector3df(60.0f,60.0f,60.0f);
    core::vector3df pos(35460,135*2,42440);
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"grass_big.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(scale);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->setPosition(pos);
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialTexture( 0, texture("grass/grass.png") );
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());
        m_movableNode = (scene::IAnimatedMeshSceneNode*)node;
    }
    mesh->drop();



    //

    grassGen(14090.0f, 260.0f, 46060.0f, 1, 1, 12);

    return 0;
}

int GamePark::initRoads()
{
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"road.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(123.4f,123.4f,123.4f));
        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(9730*2,150*2,26555*2));
        node->setMaterialTexture( 0, texture("asphalt.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(200,200);
        //node->setMaterialType(video::EMT_DETAIL_MAP);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());

    }
    setCollision(node,m_player);
    mesh->drop();
    return 0;
}

int GamePark::initCurb()
{
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"curb.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(123.4f,123.4f,123.4f));
        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(9730*2,150*2,26555*2));
        //node->addShadowVolumeSceneNode(0,-1,false,5000.0f);
        node->setMaterialTexture( 0, texture("curb2.jpg") );
//        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(80,80);
        node->getMaterial(1).getTextureMatrix(0).setTextureScale(40,40);
        node->getMaterial(2).getTextureMatrix(0).setTextureScale(40,40);
        //node->setMaterialType(video::EMT_DETAIL_MAP);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());

//        node->setMaterialTexture(1, texture("grass_dirty.jpg"));
//        node->getMaterial(0).getTextureMatrix(1).setTextureScale(100,100);
//        node->setMaterialType(video::EMT_DETAIL_MAP);

//        node->getMaterial(0).getTextureMatrix(0).setTextureScale(200, 200);

    }
//    setCollision(node,m_player);
    mesh->drop();
    return 0;
}

int GamePark::initGarbage()
{
    core::vector3df pos(14790.0f, 459.0f, 46960.0f);
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"garbage_ground.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(86.0f,86.0f,86.0f));
        node->setRotation(core::vector3df(0,180,0));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(pos);
        //node->addShadowVolumeSceneNode(0,-1,false,5000.0f);
        node->setMaterialTexture( 0, texture("garbage_ground.png") );
//        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
//        node->getMaterial(0).getTextureMatrix(0).setTextureScale(80,80);
//        node->getMaterial(1).getTextureMatrix(0).setTextureScale(40,40);
//        node->getMaterial(2).getTextureMatrix(0).setTextureScale(40,40);
        //node->setMaterialType(video::EMT_DETAIL_MAP);
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());


//        node->setMaterialTexture(1, texture("grass_dirty.jpg"));
//        node->getMaterial(0).getTextureMatrix(1).setTextureScale(100,100);
//        node->setMaterialType(video::EMT_DETAIL_MAP);

//        node->getMaterial(0).getTextureMatrix(0).setTextureScale(200, 200);

    }
    setCollision(node,m_player);
    mesh->drop();



    mesh = smgr()->getMesh(Common::modelsPath()+"garbage.b3d");
        if (!mesh)
        {
            m_device->drop();
            return 1;
        }
        node = smgr()->addMeshSceneNode( mesh );
        if (node)
        {
            node->setScale(core::vector3df(86.0f,86.0f,86.0f));
            node->setRotation(core::vector3df(0,180,0));
            node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
            node->setPosition(pos);
            //node->addShadowVolumeSceneNode(0,-1,false,5000.0f);
            node->setMaterialTexture( 0, texture("garbage_brick.jpg") );
    //        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
    //        node->getMaterial(0).getTextureMatrix(0).setTextureScale(80,80);
    //        node->getMaterial(1).getTextureMatrix(0).setTextureScale(40,40);
    //        node->getMaterial(2).getTextureMatrix(0).setTextureScale(40,40);
            //node->setMaterialType(video::EMT_DETAIL_MAP);
            node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
            node->setMaterialFlag(video::EMF_FOG_ENABLE, m_config.fog());


    //        node->setMaterialTexture(1, texture("grass_dirty.jpg"));
    //        node->getMaterial(0).getTextureMatrix(1).setTextureScale(100,100);
    //        node->setMaterialType(video::EMT_DETAIL_MAP);

    //        node->getMaterial(0).getTextureMatrix(0).setTextureScale(200, 200);

        }


    return 0;
}

int GamePark::initPlanes()
{
    scene::IMesh* mesh = smgr()->getMesh(Common::modelsPath()+"main_plane.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(45.0f,45.0f,45.0f));
        node->setRotation(core::vector3df(0,90,0));
        if(!shadows)
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(7950*2,150*2,29850*2));
        node->setMaterialTexture( 0, texture("plita-daleko.png") );
        node->setMaterialTexture( 1, texture("plita-2.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;

        node->setMaterialType(video::EMT_DETAIL_MAP);

        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);

    }
    setCollision(node,m_player);
    return 0;
}

int GamePark::initSounds()
{
    // start the sound engine with default parameters
    m_soundEngine = createIrrKlangDevice();

    if (!m_soundEngine)
    {
        printf("Could not startup engine\n");
        return 1; // error starting up the engine
    }

    // To play a sound, we only to call play2D(). The second parameter
    // tells the engine to play it looped.

    // play some sound stream, looped
    m_soundEngine->play2D("../../media/sounds/nature.ogg", true);
    m_player->setSoundEngine(m_soundEngine);


    vec3df pos(32300.0f, 380.0f, 56080.0f);

    ISound* music = m_soundEngine->play3D("../../media/sounds/lake_waves.ogg",
                                   pos, true, false, true);
    if (music)
    {
       music->setMinDistance(300.0f);
       music->setVolume(1.0f);
    }

    return 0;
}

int GamePark::initEagle(core::vector3df center, float radius, float speed)
{
    scene::IAnimatedMesh* mesh;
    scene::IAnimatedMeshSceneNode* eagleNode;
    mesh = smgr()->getMesh(Common::modelsPath()+"eagle.md2");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    eagleNode = smgr()->addAnimatedMeshSceneNode( mesh );
    if (eagleNode)
    {

        eagleNode->setScale(core::vector3df(5.0f,5.0f,5.0f));
        eagleNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        eagleNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        eagleNode->setPosition(center);
        eagleNode->setRotation(core::vector3df(0,-90,0));
        eagleNode->setFrameLoop(0,15);
        eagleNode->setAnimationSpeed(12);

        scene::ISceneNodeAnimator* anim = 0;
        anim = smgr()->createFlyCircleAnimator(center, radius,
                                               (2*core::PI/1000.0f)*speed);
        eagleNode->addAnimator(anim);

        anim = smgr()->createRotationAnimator(core::vector3df(0,(3.6)*speed,0));
        eagleNode->addAnimator(anim);
        eagleNode->setName("eagle");
        anim->drop();

        eagleNode->setMaterialTexture( 0, texture("eagle.jpg") );
        //eagleNode->setMaterialType(video::EMT_DETAIL_MAP);

    }
    return 0;
}

void GamePark::setCollision(scene::IAnimatedMeshSceneNode *node, Player *player)
{
    Collision::setCollision(node, player, smgr());
}

void GamePark::setCollision(scene::IMeshSceneNode *node, Player *player)
{
    Collision::setCollision(node, player, smgr());
}

ITexture *GamePark::texture(const io::path &filename)
{
    return driver()->getTexture(core::stringc("../../media/textures/")+filename);
}

void GamePark::switchTerrainMaterial(video::E_MATERIAL_FLAG material)
{
    switch (material) {
        case video::EMF_WIREFRAME:
            terrain->setMaterialFlag(video::EMF_WIREFRAME, !terrain->getMaterial(0).Wireframe);
            terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
        break;
        case video::EMF_POINTCLOUD:
            terrain->setMaterialFlag(video::EMF_POINTCLOUD, !terrain->getMaterial(0).PointCloud);
            terrain->setMaterialFlag(video::EMF_WIREFRAME, false);
        break;
        default:
        break;
    }
}

void GamePark::switchTerrainDetailMap()
{
    video::E_MATERIAL_TYPE materialType = video::EMT_SOLID;
    if(terrain->getMaterial(0).MaterialType == video::EMT_SOLID)
    {
        materialType = video::EMT_DETAIL_MAP;
    }
    terrain->getMaterial(0).MaterialType = materialType;
}

void GamePark::switchSkybox()
{
    skybox->setVisible(!skybox->isVisible());
    skydome->setVisible(!skydome->isVisible());
}

void GamePark::updateEnvironment(const core::stringw& str)
{
    m_fpsText->setText(str.c_str());
}

Player *GamePark::player() const
{
    return m_player;
}

scene::IAnimatedMeshSceneNode *GamePark::movableNode() const
{
    return m_movableNode;
}

void GamePark::forestLOD(core::vector3df pos)
{
    int frame = 12;

    if(m_checkLodCounter == frame)
    {
        float dist;
        for(int i=0;i<m_forestSize;i++)
        {
            dist = m_forest[i]->getPosition().getDistanceFrom(pos);
            if(dist < 25000 && !m_forest[i]->isVisible()){
                m_forest[i]->setVisible(true);
            }
            else if(dist > 25000 && m_forest[i]->isVisible()){
                m_forest[i]->setVisible(false);
            }
        }
    }
    //-----------------------------------
    if(m_checkLodCounter < frame)
    {
        m_checkLodCounter++;
    }
    else
    {
        m_checkLodCounter = 0;
    }

}

void GamePark::grassGen(f32 x,f32 y,f32 z, f32 u, f32 v, f32 s)
{
    TKGrassShaderCallBack* grassShaderCB=new TKGrassShaderCallBack();

    s32 materialGrass=m_device->getVideoDriver()->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles(
        "../../shaders/grass/grass.vert", "vertexMain", video::EVST_VS_1_1,
        "../../shaders/grass/grass.frag", "pixelMain", video::EPST_PS_1_1,
        grassShaderCB, video::EMT_TRANSPARENT_ALPHA_CHANNEL);

    int xDiff = s*6;
    int yDiff = s*6;
    for(int i=0;i<u;i=i+s*8)
    for(int j=0;j<v;j=j+s*8)
    {
        TKGrassSceneNode* temp=new TKGrassSceneNode(smgr()->getRootSceneNode(),smgr(),-1,materialGrass,7000);
        temp->setPosition(vector3df(i+(rand()%xDiff)+x,y+50+(rand()%yDiff),j+(rand()%xDiff)+z));
        temp->setScale(core::vector3df(s,s+1,s));
    }


}

int GamePark::run()
{

    /*
    That's it, draw everything.
    */

//    int lastFPS = -1;

    scene::IBillboardSceneNode * bill;
    // Добавляем билборд, который будет подсвечивать место
    // пересечения луча и объекта в который он уперся
    bill = smgr()->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, texture("particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d< f32 >(20.0f, 20.0f));
    // дадим билборду ID для объектов которые не реагируют на столкновения.
    bill->setID(ID_IsNotPickable);
    scene::ISceneCollisionManager*  collMan;
//    video::SMaterial material;



//// Для размытия
//    /**Important stuff, Rendering textures setup.*/
//        video::ITexture* mainTarget = driver()->addRenderTargetTexture(m_config.params().WindowSize,"mainTarget");
//        video::ITexture* rtt0;
//        video::ITexture* temp;

//    //These colors are needed to modify the colors of the RTT in order for them to mix adequately
//    //Using a shader, the mix is done within the shader code, but we are using just the
//    //fixed pipeline this time, so, we need some extra stuff. Normally, postprocessing is not
//    //this extended.
//        rtt0 = driver()->addRenderTargetTexture(m_config.params().WindowSize,"rtt0");
//        temp = driver()->addRenderTargetTexture(m_config.params().WindowSize,"temp");//Mantiene temporalmente un resultado.

//        CScreenQuadSceneNode* screenQuad = new CScreenQuadSceneNode(smgr()->getRootSceneNode(),smgr(),10);
//        screenQuad->getMaterial(0).setTexture(0,mainTarget);
//        screenQuad->getMaterial(0).setTexture(1,rtt0);





    while(m_device->run())
    if (m_device->isWindowActive())
    {
        driver()->beginScene(true, true, 0 );

        forestLOD(m_player->camera()->getPosition());

        smgr()->drawAll();
//// Для размытия
//        screenQuad->draw(driver(), rtt0, temp, m_config.params().WindowSize.Width,
//                         m_config.params().WindowSize.Height, mainTarget);
        env()->drawAll();

//log("--");
//log(m_player->camera()->getPosition().X);
//log(m_player->camera()->getPosition().Y);
//log(m_player->camera()->getPosition().Z);
        m_soundEngine->setListenerPosition(m_player->camera()->getPosition(),
                                           m_player->camera()->getTarget());

        collMan = smgr()->getSceneCollisionManager();

        core::line3d<f32> ray;
        ray.start = m_player->camera()->getPosition();
        ray.end = ray.start + (m_player->camera()->getTarget() - ray.start).normalize() * 100000.0f;

        // переменная под хранение точки пересещения
        core::vector3df intersection;
        // переменная под хранение треугольника с которым пересекся луч
        core::triangle3df hitTriangle;

        scene::ISceneNode * selectedSceneNode =
        collMan->getSceneNodeAndCollisionPointFromRay(
        ray,
        intersection, // точка столкновения
        hitTriangle, // полигон(треугольник) в котором
        // точка столкновения
        IDFlag_IsPickable, // определять столкновения только для
        //нод с идентификатором IDFlag_IsPickable
        0); // проверять относительно всей
        // сцены (оставляем значение по умолчанию)

        // Если луч столкнулся с чем нибудь,
        // перемещаем указку(билборд) в точку столкновения
        // и рисуем треугольник в котором она находится




        if(selectedSceneNode && m_player->animationFire())
        {
            bill->setPosition(intersection);
            m_movableNode = (scene::IAnimatedMeshSceneNode*)selectedSceneNode;
//            log( selectedSceneNode->getName() );
            //usl_slow_exit = false;

            // мы должны сбросить трансформации перед отрисовкой.
            //driver->setTransform(video::ETS_WORLD, core::matrix4());
            //driver->setMaterial(material);
            //driver->draw3DTriangle(hitTriangle, video::SColor(0,255,0,0));
        }

        // ---------




        if(usl_exit)break;

        if(m_player->node()->getFrameNr() > 31 && m_player->node()->getFrameNr() < 35) m_player->fire()->setVisible(true);
        if(m_player->node()->getFrameNr() > 35 || m_player->node()->getFrameNr() < 30) m_player->fire()->setVisible(false);




        driver()->endScene();

        // display frames per second in window title
        int fps = driver()->getFPS();
        int count = driver()->getPrimitiveCountDrawn();
//        if (lastFPS != fps)
        if(m_checkFpsCounter > 12)
        {
            m_checkFpsCounter = 0;
            core::stringw str = L"Driver [";
            str += driver()->getName();
            str += "] FPS:";
            str += fps;
            // Also print terrain height of current camera position
            // We can use camera position because terrain is located at coordinate origin
            str += " Height: ";
            str += terrain->getHeight(m_player->camera()->getAbsolutePosition().X,
                    m_player->camera()->getAbsolutePosition().Z);
            str += " Triangle: ";
            str += count;

//            m_device->setWindowCaption(str.c_str());
//            lastFPS = fps;

            updateEnvironment(str);
        }
        m_checkFpsCounter++;

    }

    m_device->drop();

    return 0;
}


